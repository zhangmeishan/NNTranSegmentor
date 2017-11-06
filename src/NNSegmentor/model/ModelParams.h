#ifndef SRC_ModelParams_H_
#define SRC_ModelParams_H_
#include "HyperParams.h"

// Each model consists of two parts, building neural graph and defining output losses.
class ModelParams {
  public:
    //neural parameters
    Alphabet embeded_words; // words
    LookupTable word_table; // should be initialized outside
    Alphabet embeded_chars; // chars
    LookupTable char_table; // should be initialized outside

    LSTM1Params char_left_lstm; //left lstm
    LSTM1Params char_right_lstm; //right lstm

    LSTM1Params word_lstm;

    UniParams state_represent;

    UniParams sep_score;
    UniParams app_score;

  public:
    bool initial(HyperParams& opts) {
        // some model parameters should be initialized outside
        //neural features
        char_left_lstm.initial(opts.char_lstm_dim, opts.char_dim); //left lstm
        char_right_lstm.initial(opts.char_lstm_dim, opts.char_dim); //right lstm

        word_lstm.initial(opts.word_lstm_dim, opts.word_dim);

        state_represent.initial(opts.state_hidden_dim, opts.state_feat_dim, true);

        sep_score.initial(1, opts.state_hidden_dim, false);
        app_score.initial(1, opts.state_hidden_dim, false);

        sep_score.W.val.random(0.01);
        app_score.W.val.random(0.01);
        return true;
    }


    void exportModelParams(ModelUpdate& ada) {
        //neural features
        word_table.exportAdaParams(ada);
        char_table.exportAdaParams(ada);

        char_left_lstm.exportAdaParams(ada);
        char_right_lstm.exportAdaParams(ada);

        word_lstm.exportAdaParams(ada);

        state_represent.exportAdaParams(ada);

        sep_score.exportAdaParams(ada);
        app_score.exportAdaParams(ada);

    }


    // will add it later
    void saveModel() {

    }

    void loadModel(const string& inFile) {

    }

};

#endif /* SRC_ModelParams_H_ */