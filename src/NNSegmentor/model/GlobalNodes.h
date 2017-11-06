/*
 * Feature.h
 *
 *  Created on: Aug 25, 2016
 *      Author: mszhang
 */

#ifndef SRC_GlobalNodes_H_
#define SRC_GlobalNodes_H_

#include "ModelParams.h"

struct GlobalNodes {
    vector<LookupNode> char_inputs;
    LSTM1Builder char_left_lstm;
    LSTM1Builder char_right_lstm;

  public:
    inline void resize(int max_sentence_length) {
        char_inputs.resize(max_sentence_length);
        char_left_lstm.resize(max_sentence_length);
        char_right_lstm.resize(max_sentence_length);
    }

  public:
    inline void initial(ModelParams& params, HyperParams& hyparams) {
        int length = char_inputs.size();
        for (int idx = 0; idx < length; idx++) {
            char_inputs[idx].setParam(&params.char_table);
        }

        char_left_lstm.init(&params.char_left_lstm, hyparams.dropProb, true);
        char_right_lstm.init(&params.char_right_lstm, hyparams.dropProb, false);

        for (int idx = 0; idx < length; idx++) {
            char_inputs[idx].init(hyparams.char_dim, hyparams.dropProb);
        }
    }


  public:
    inline void forward(Graph* cg, const std::vector<std::string>* pCharacters) {
        int char_size = pCharacters->size();
        string unichar;
        for (int idx = 0; idx < char_size; idx++) {
            unichar = (*pCharacters)[idx];
            char_inputs[idx].forward(cg, unichar);
        }

        char_left_lstm.forward(cg, getPNodes(char_inputs, char_size));
        char_right_lstm.forward(cg, getPNodes(char_inputs, char_size));
    }

};

#endif /* SRC_GlobalNodes_H_ */
