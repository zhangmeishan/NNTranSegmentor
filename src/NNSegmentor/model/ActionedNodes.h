/*
* Feature.h
*
*  Created on: Aug 25, 2016
*      Author: mszhang
*/

#ifndef SRC_ActionedNodes_H_
#define SRC_ActionedNodes_H_

#include "ModelParams.h"
#include "AtomFeatures.h"
#include "Action.h"

struct ActionedNodes {
    LookupNode last_word_input;
    IncLSTM1Builder word_lstm;

    ConcatNode state_concat;
    UniNode state_represent;

    LinearNode app_score;
    LinearNode sep_score;
    vector<PAddNode> outputs;

    BucketNode bucket_char, bucket_word;

    HyperParams *opt;

  public:
    ~ActionedNodes() {
    }
  public:
    inline void initial(ModelParams& params, HyperParams& hyparams) {
        last_word_input.setParam(&(params.word_table));
        last_word_input.init(hyparams.word_dim, hyparams.dropProb);
        word_lstm.init(&(params.word_lstm), hyparams.dropProb); //already allocated here


        state_concat.init(hyparams.state_feat_dim, -1);

        state_represent.setParam(&params.state_represent);
        state_represent.init(hyparams.state_hidden_dim, -1);

        app_score.setParam(&(params.app_score));
        app_score.init(1, -1);
        sep_score.setParam(&(params.sep_score));
        sep_score.init(1, -1);

        outputs.resize(hyparams.action_num);

        //neural features
        for (int idx = 0; idx < hyparams.action_num; idx++) {
            outputs[idx].init(1, -1);
        }

        opt = &hyparams;

        bucket_char.init(hyparams.char_lstm_dim, -1);
        bucket_word.init(hyparams.word_lstm_dim, -1);

    }


  public:
    inline void forward(Graph* cg, const vector<CAction>& actions, AtomFeatures& atomFeat, PNode prevStateNode) {
        vector<PNode> sumNodes;
        CAction ac;
        int ac_num;
        ac_num = actions.size();

        bucket_char.forward(cg, 0);
        bucket_word.forward(cg, 0);
        PNode pseudo_char = &(bucket_char);
        PNode pseudo_word = &(bucket_word);


        //chars
        int char_posi = atomFeat.next_position;
        PNode char_node_left_curr = (char_posi  < atomFeat.char_size) ? &(atomFeat.p_char_left_lstm->_hiddens[char_posi]) : pseudo_char;
        //PNode char_node_left_next1 = (char_posi + 1  < atomFeat.char_size) ? &(atomFeat.p_char_left_lstm->_hiddens[char_posi + 1]) : pseudo_char;
        //PNode char_node_left_next2 = (char_posi + 2  < atomFeat.char_size) ? &(atomFeat.p_char_left_lstm->_hiddens[char_posi + 2]) : pseudo_char;
        //PNode char_node_left_prev1 = (char_posi > 0) ? &(atomFeat.p_char_left_lstm->_hiddens[char_posi - 1]) : pseudo_char;
        //PNode char_node_left_prev2 = (char_posi > 1) ? &(atomFeat.p_char_left_lstm->_hiddens[char_posi - 2]) : pseudo_char;

        PNode char_node_right_curr = (char_posi  < atomFeat.char_size) ? &(atomFeat.p_char_right_lstm->_hiddens[char_posi]) : pseudo_char;
        //PNode char_node_right_next1 = (char_posi + 1  < atomFeat.char_size) ? &(atomFeat.p_char_right_lstm->_hiddens[char_posi + 1]) : pseudo_char;
        //PNode char_node_right_next2 = (char_posi + 2  < atomFeat.char_size) ? &(atomFeat.p_char_right_lstm->_hiddens[char_posi + 2]) : pseudo_char;
        //PNode char_node_right_prev1 = (char_posi > 0) ? &(atomFeat.p_char_right_lstm->_hiddens[char_posi - 1]) : pseudo_char;
        //PNode char_node_right_prev2 = (char_posi > 1) ? &(atomFeat.p_char_right_lstm->_hiddens[char_posi - 2]) : pseudo_char;


        last_word_input.forward(cg, atomFeat.str_1W);
        word_lstm.forward(cg, &last_word_input, atomFeat.p_word_lstm);


        vector<PNode> state_components;
        state_components.push_back(&word_lstm._hidden);
        //
        state_components.push_back(char_node_left_curr);
        //state_components.push_back(char_node_left_next1);
        //state_components.push_back(char_node_left_next2);
        //state_components.push_back(char_node_left_prev1);
        //state_components.push_back(char_node_left_prev2);

        state_components.push_back(char_node_right_curr);
        //state_components.push_back(char_node_right_next1);
        //state_components.push_back(char_node_right_next2);
        //state_components.push_back(char_node_right_prev1);
        //state_components.push_back(char_node_right_prev2);

        state_concat.forward(cg, state_components);
        state_represent.forward(cg, &state_concat);

        for (int idx = 0; idx < ac_num; idx++) {
            ac.set(actions[idx]);

            sumNodes.clear();

            if (ac.isAppend()) {
                app_score.forward(cg, &state_represent);
                sumNodes.push_back(&app_score);
            } else if (ac.isSeparate() || ac.isFinish()) {
                sep_score.forward(cg, &state_represent);
                sumNodes.push_back(&sep_score);
            } else {
                std::cout << "error action here" << std::endl;
            }

            if (prevStateNode != NULL) {
                sumNodes.push_back(prevStateNode);
            }

            outputs[idx].forward(cg, sumNodes);
        }
    }

};

#endif /* SRC_ActionedNodes_H_ */
