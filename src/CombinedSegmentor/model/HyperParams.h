#ifndef SRC_HyperParams_H_
#define SRC_HyperParams_H_

#include "N3LDG.h"
#include "Options.h"

using namespace nr;
using namespace std;

struct HyperParams {
    //required
    int beam;
    int maxlength;
    int action_num;
    dtype delta;
    int batch;
    unordered_set<string> dicts;  // dictionary in order to extract iv/oov features.
    int base;


    dtype nnRegular; // for optimization
    dtype adaAlpha;  // for optimization
    dtype adaEps; // for optimization
    dtype dropProb;

    int char_dim;
    int char_lstm_dim;
    bool char_tune;

    int word_dim;
    int word_lstm_dim;
    bool word_tune;

    int state_feat_dim;
    int state_hidden_dim;

  public:
    HyperParams() {
        maxlength = max_sentence_clength + 1;
        bAssigned = false;
    }

  public:
    void setRequared(Options& opt) {
        //please specify dictionary outside
        //please sepcify char_dim, word_dim and action_dim outside.
        beam = opt.beam;
        delta = opt.delta;
        bAssigned = true;

        nnRegular = opt.regParameter;
        adaAlpha = opt.adaAlpha;
        adaEps = opt.adaEps;
        dropProb = opt.dropProb;
        batch = opt.batchSize;
        base = opt.base;

        char_dim = opt.charEmbSize;
        char_lstm_dim = opt.charRNNHiddenSize;
        char_tune = opt.charEmbFineTune;

        word_dim = opt.wordEmbSize;
        word_lstm_dim = opt.wordRNNHiddenSize;
        word_tune = opt.wordEmbFineTune;

        state_feat_dim = 2 * char_lstm_dim + word_lstm_dim;
        state_hidden_dim = opt.sepHiddenSize;
    }

    void clear() {
        bAssigned = false;
    }

    bool bValid() {
        return bAssigned;
    }


  public:

    void print() {
        std::cout << "show hyper parameters" << std::endl;
        std::cout << "maxlength = " << maxlength << std::endl;
        std::cout << "beam = " << beam << std::endl;
        std::cout << "delta = " << delta << std::endl;
        std::cout << "action_num = " << action_num << std::endl;
        std::cout << "nnRegular = " << nnRegular << std::endl;
        std::cout << "adaAlpha = " << adaAlpha << std::endl;
        std::cout << "adaEps = " << adaEps << std::endl;
        std::cout << "dropProb = " << dropProb << std::endl;
        std::cout << "base = " << base << std::endl;
        std::cout << "batch = " << batch << std::endl;

        std::cout << "char_dim = " << char_dim << std::endl;
        std::cout << "char_tune = " << char_tune << std::endl;
        std::cout << "char_lstm_dim = " << char_lstm_dim << std::endl;

        std::cout << "word_dim = " << word_dim << std::endl;
        std::cout << "word_lstm_dim = " << word_lstm_dim << std::endl;
        std::cout << "word_tune = " << word_tune << std::endl;

        std::cout << "state_feat_dim = " << state_feat_dim << std::endl;
        std::cout << "state_hidden_dim = " << state_hidden_dim << std::endl;

        std::cout << std::endl;
    }

  private:
    bool bAssigned;
};


#endif /* SRC_HyperParams_H_ */