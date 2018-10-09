#ifndef SRC_BeamGraph_H_
#define SRC_BeamGraph_H_

#include "ModelParams.h"
#include "State.h"

// Each model consists of two parts, building neural graph and defining output losses.
// This framework wastes memory
class BeamGraphBuilder {
  public:
    // node instances
    CStateItem start;
    vector<vector<CStateItem> > states;
    vector<vector<COutput> > outputs;

    vector<CStateItem*> lastStates;
    CStateItem* pGenerator;
    CStateItem* pGoldGenerator;
    int step, offset;
    vector<vector<CAction> > actions; // actions to apply for a candidate
    CScoredState scored_action; // used rank actions
    COutput output;
    bool correct_action_scored;
    bool correct_in_beam;
    CAction answer, action;
    Metric eval;
    vector<COutput> per_step_output;
    NRHeap<CScoredState, CScoredState_Compare> beam;
    bool is_finish;

  private:
    ModelParams *pModel;
    HyperParams *pOpts;

    // node pointers
  public:
    BeamGraphBuilder() {
        clear();
    }

    ~BeamGraphBuilder() {
        clear();
    }

  public:
    //allocate enough nodes
    inline void initial(ModelParams &model, HyperParams &opts) {
        std::cout << "state size: " << sizeof(CStateItem) << std::endl;
        std::cout << "action node size: " << sizeof(ActionedNodes) << std::endl;
        states.resize(opts.maxlength + 1);

        for (int idx = 0; idx < states.size(); idx++) {
            states[idx].resize(opts.beam);
            for (int idy = 0; idy < states[idx].size(); idy++) {
                states[idx][idy].initial(model, opts);
            }
        }
        start.clear();
        start.initial(model, opts);

        pModel = &model;
        pOpts = &opts;
    }

    inline void clear() {
        //beams.clear();
        clearVec(outputs);
        states.clear();
        pModel = NULL;
        pOpts = NULL;
    }



  public:
    inline void decode_prepare(Graph* pcg, const std::vector<std::string>* pCharacters) {
        clearVec(outputs);
        //second step, build graph

        beam.resize(pOpts->beam);
        actions.resize(pOpts->beam);

        lastStates.clear();
        start.setInput(pCharacters);
        lastStates.push_back(&start);
        pGoldGenerator = pcg->train ? &start : NULL;
        step = 0;
        is_finish = false;
    }

    inline void decode_forward(Graph* pcg, const std::vector<std::string>* pCharacters) {
        if (!is_finish) {
            for (int idx = 0; idx < lastStates.size(); idx++) {
                pGenerator = lastStates[idx];
                pGenerator->prepare(pOpts);
            }

            for (int idx = 0; idx < lastStates.size(); idx++) {
                pGenerator = lastStates[idx];
                pGenerator->getCandidateActions(actions[idx]);
                pGenerator->computeNextScore(pcg, actions[idx]);
            }
        }
    }

    inline void decode_apply_action(Graph* pcg, const std::vector<std::string>* pCharacters, const vector<CAction>* goldAC = NULL) {
        // training apply gold oralce, predicting apply predict oralce
        if (!is_finish) {
            answer.clear();
            per_step_output.clear();
            correct_action_scored = false;
            if (pcg->train) answer = (*goldAC)[step];
            beam.clear();

            for (int idx = 0; idx < lastStates.size(); idx++) {
                pGenerator = lastStates[idx];
                scored_action.item = pGenerator;
                for (int idy = 0; idy < actions[idx].size(); ++idy) {
                    scored_action.ac.set(actions[idx][idy]); //TODO:
                    if (pGenerator->_bGold && actions[idx][idy] == answer) {
                        scored_action.bGold = true;
                        correct_action_scored = true;
                        output.bGold = true;
                    } else {
                        scored_action.bGold = false;
                        output.bGold = false;
                    }
                    if (pcg->train && actions[idx][idy] != answer)pGenerator->_nextscores.outputs[idy].val[0] += pOpts->delta;
                    scored_action.score = pGenerator->_nextscores.outputs[idy].val[0];
                    scored_action.position = idy;
                    output.in = &(pGenerator->_nextscores.outputs[idy]);
                    beam.add_elem(scored_action);
                    per_step_output.push_back(output);
                }
            }

            outputs.push_back(per_step_output);

            // FIXME:
            if (pcg->train && !correct_action_scored) { //training
                std::cout << "error during training, gold-standard action is filtered: " << step << std::endl;
                //for (int idx = 0; idx < inst.size(); idx++) {
                //		std::cout << inst.words[idx] << "\t" << inst.tags[idx] << "\t" << inst.result.heads[idx] << "\t" << inst.result.labels[idx] << endl;
                //}
                //std::cout << std::endl;
                std::cout << answer.str() << std::endl;
                for (int idx = 0; idx < lastStates.size(); idx++) {
                    pGenerator = lastStates[idx];
                    //std::cout << pGenerator->str(pOpts) << std::endl;
                    if (pGenerator->_bGold) {
                        pGenerator->getCandidateActions(actions[idx]);
                        for (int idy = 0; idy < actions[idx].size(); ++idy) {
                            std::cout << actions[idx][idy].str() << " ";
                        }
                        std::cout << std::endl;
                    }
                }
                return;
            }

            offset = beam.elemsize();
            if (offset == 0) { // judge correctiveness
                std::cout << "error, reach no output here, please find why" << std::endl;
                for (int idx = 0; idx < pCharacters->size(); idx++) {
                    std::cout << (*pCharacters)[idx] << std::endl;
                }
                std::cout << "" << std::endl;
                return;
            }

            beam.sort_elem();
            for (int idx = 0; idx < offset; idx++) {
                pGenerator = beam[idx].item;
                action.set(beam[idx].ac);
                pGenerator->move(&(states[step][idx]), action, pGoldGenerator, answer);
                states[step][idx]._score = &(pGenerator->_nextscores.outputs[beam[idx].position]);
            }


            if (states[step][0].IsTerminated()) {
                is_finish = true;
            } else {
                //for next step
                lastStates.clear();
                correct_in_beam = false;
                pGoldGenerator = NULL;
                for (int idx = 0; idx < offset; idx++) {
                    lastStates.push_back(&(states[step][idx]));
                    if (lastStates[idx]->_bGold) {
                        correct_in_beam = true;
                        pGoldGenerator = lastStates[idx];
                    }
                }

                if (pcg->train && !correct_in_beam) {
                    is_finish = true;
                }
            }

            step++;
        }
    }

};

#endif /* SRC_BeamGraph_H_ */