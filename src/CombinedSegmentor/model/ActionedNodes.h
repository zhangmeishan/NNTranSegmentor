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
    vector<SparseNode> sparse_features;
    vector<ScaleNode> scale_features;

    LookupNode last_word_input;
    IncLSTM1Builder word_lstm;

    ConcatNode state_concat;
    UniNode state_represent;

    LinearNode app_score;
    LinearNode sep_score;
    ScaleNode scale_app_score;
    ScaleNode scale_sep_score;
    vector<PAddNode> outputs;

    BucketNode bucket_char, bucket_word;

    HyperParams *opt;

  public:
    ~ActionedNodes() {
    }
  public:
    inline void initial(ModelParams& params, HyperParams& hyparams) {
        //neural features
        last_word_input.setParam(&(params.word_table));
        last_word_input.init(hyparams.word_dim, hyparams.dropProb);
        word_lstm.init(&(params.word_lstm), hyparams.dropProb); //already allocated here


        state_concat.init(hyparams.state_feat_dim, -1);

        state_represent.setParam(&params.state_represent);
        state_represent.init(hyparams.state_hidden_dim, -1);

        app_score.setParam(&(params.app_score));
        app_score.init(1, -1);
        scale_app_score.init(1, -1);
        sep_score.setParam(&(params.sep_score));
        sep_score.init(1, -1);
        scale_sep_score.init(1, -1);

        outputs.resize(hyparams.action_num);
        sparse_features.resize(hyparams.action_num);
        scale_features.resize(hyparams.action_num);
        //neural features
        for (int idx = 0; idx < hyparams.action_num; idx++) {
            sparse_features[idx].setParam(&params.sep_app_feats);
            sparse_features[idx].init(1, -1);
            scale_features[idx].init(1, -1);
            outputs[idx].init(1, -1);
        }

        opt = &hyparams;

        bucket_char.init(hyparams.char_lstm_dim, -1);
        bucket_word.init(hyparams.word_lstm_dim, -1);

    }


  public:
    inline void forward(Graph* cg, const vector<CAction>& actions, AtomFeatures& atomFeat, PNode prevStateNode) {
        vector<PNode> sumNodes;
        vector<string> strFeats;
        string strFeat = "";
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
            strFeats.clear();
            if (ac.isAppend()) {
                strFeat = "F01" + seperateKey + atomFeat.str_1C + seperateKey + atomFeat.str_C0;
                strFeats.push_back(strFeat);

                strFeat = "F02" + seperateKey + atomFeat.str_1Wc0 + seperateKey + atomFeat.str_C0;
                strFeats.push_back(strFeat);

                strFeat = "F03" + seperateKey + atomFeat.str_2CT + atomFeat.str_1CT + atomFeat.str_CT0;
                strFeats.push_back(strFeat);
            } else {
                strFeat = "F101" + seperateKey + atomFeat.str_1C + seperateKey + atomFeat.str_C0;
                strFeats.push_back(strFeat);

                strFeat = "F102" + seperateKey + atomFeat.str_1Wc0 + seperateKey + atomFeat.str_C0;
                strFeats.push_back(strFeat);

                strFeat = "F103" + seperateKey + atomFeat.str_2CT + atomFeat.str_1CT + atomFeat.str_CT0;
                strFeats.push_back(strFeat);

                strFeat = "F104" + seperateKey + atomFeat.str_1W;
                strFeats.push_back(strFeat);

                if (atomFeat.sid_1WL == 1) {
                    strFeat = "F105" + seperateKey + atomFeat.str_1W;
                    strFeats.push_back(strFeat);
                }

                strFeat = "F106" + seperateKey + atomFeat.str_2W + seperateKey + atomFeat.str_1W;
                strFeats.push_back(strFeat);

                strFeat = "F107" + seperateKey + atomFeat.str_1W + seperateKey + atomFeat.str_C0;
                strFeats.push_back(strFeat);

                strFeat = "F108" + seperateKey + atomFeat.str_1W + seperateKey + atomFeat.str_1WL;
                strFeats.push_back(strFeat);

                strFeat = "F109" + seperateKey + atomFeat.str_2Wc0 + seperateKey + atomFeat.str_1W;
                strFeats.push_back(strFeat);

                strFeat = "F110" + seperateKey + atomFeat.str_2Wcn + seperateKey + atomFeat.str_1W;
                strFeats.push_back(strFeat);

                strFeat = "F111" + seperateKey + atomFeat.str_1Wc0 + seperateKey + atomFeat.str_1C;
                strFeats.push_back(strFeat);

                strFeat = "F112" + seperateKey + atomFeat.str_2WL + seperateKey + atomFeat.str_1W;
                strFeats.push_back(strFeat);

                strFeat = "F113" + seperateKey + atomFeat.str_2W + seperateKey + atomFeat.str_1WL;
                strFeats.push_back(strFeat);

                strFeat = "F114" + seperateKey + atomFeat.str_2W + seperateKey + atomFeat.str_1C;
                strFeats.push_back(strFeat);

                for (int idy = 0; idy < atomFeat.str_1Wci.size(); idy++) {
                    strFeat = "F115" + seperateKey + atomFeat.str_1C + seperateKey + atomFeat.str_1Wci[idy];
                    strFeats.push_back(strFeat);
                }

                strFeat = "F116" + seperateKey + atomFeat.str_2Wc0 + seperateKey + atomFeat.str_1Wc0;
                strFeats.push_back(strFeat);

                strFeat = "F117" + seperateKey + atomFeat.str_2Wcn + seperateKey + atomFeat.str_1C;
                strFeats.push_back(strFeat);

                strFeat = "F118" + seperateKey + atomFeat.str_1WL + seperateKey + atomFeat.str_1C;
                strFeats.push_back(strFeat);

                strFeat = "F119" + seperateKey + atomFeat.str_1WL + seperateKey + atomFeat.str_1Wc0;
                strFeats.push_back(strFeat);

                strFeat = "F120" + seperateKey + atomFeat.str_1WD + seperateKey + atomFeat.str_1WL;
                strFeats.push_back(strFeat);
            }

            sparse_features[idx].forward(cg, strFeats);
            scale_features[idx].forward(cg, &(sparse_features[idx]), opt->scale);
            sumNodes.push_back(&scale_features[idx]);


            if (ac.isAppend()) {
                app_score.forward(cg, &state_represent);
                scale_app_score.forward(cg, &app_score, (1 - opt->scale));
                sumNodes.push_back(&scale_app_score);
            } else if (ac.isSeparate() || ac.isFinish()) {
                sep_score.forward(cg, &state_represent);
                scale_sep_score.forward(cg, &sep_score, (1 - opt->scale));
                sumNodes.push_back(&scale_sep_score);
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
