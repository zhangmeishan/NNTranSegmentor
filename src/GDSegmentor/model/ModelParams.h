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
  Alphabet embeded_chartypes; // chars
  LookupTable chartype_table; // should be initialized outside	
  Alphabet embeded_bichars; // bichars
  LookupTable bichar_table; // should be initialized outside

  UniParams char_tanh_conv; // hidden
  LSTM1Params char_left_lstm; //left lstm
  LSTM1Params char_right_lstm; //right lstm
  UniParams char_state_hidden;

  LSTM1Params word_lstm;
  UniParams word_state_hidden;

  UniParams app_state_represent;
  BiParams sep_state_represent;

  UniParams sep_score;
  UniParams app_score;

  //should be initialized outside
  Alphabet words; // words
  Alphabet chars; // chars
  Alphabet charTypes; // char type



public:
  bool initial(HyperParams& opts, AlignedMemoryPool* mem) {
    // some model parameters should be initialized outside
    if (words.size() <= 0 || chars.size() <= 0) {
      return false;
    }
    //neural features
    char_tanh_conv.initial(opts.char_hidden_dim, opts.char_represent_dim, true, mem);
    char_left_lstm.initial(opts.char_lstm_dim, opts.char_hidden_dim, mem); //left lstm
    char_right_lstm.initial(opts.char_lstm_dim, opts.char_hidden_dim, mem); //right lstm
    char_state_hidden.initial(opts.char_state_dim, opts.char_feat_dim, true, mem);

    word_lstm.initial(opts.word_lstm_dim, opts.word_dim, mem);
    word_state_hidden.initial(opts.word_state_dim, opts.word_feat_dim, true, mem);

    app_state_represent.initial(opts.app_dim, opts.char_state_dim, true, mem);
    sep_state_represent.initial(opts.sep_dim, opts.char_state_dim, opts.word_state_dim, true, mem);

    sep_score.initial(1, opts.sep_dim, false, mem);
    app_score.initial(1, opts.app_dim, false, mem);

    sep_score.W.val.random(0.01);
    app_score.W.val.random(0.01);
    return true;
  }


  void exportModelParams(ModelUpdate& ada) {
    //neural features
    word_table.exportAdaParams(ada);
    char_table.exportAdaParams(ada);
    chartype_table.exportAdaParams(ada);
    bichar_table.exportAdaParams(ada);

    char_tanh_conv.exportAdaParams(ada);
    char_left_lstm.exportAdaParams(ada);
    char_right_lstm.exportAdaParams(ada);
    char_state_hidden.exportAdaParams(ada);

    word_lstm.exportAdaParams(ada);
    word_state_hidden.exportAdaParams(ada);

    app_state_represent.exportAdaParams(ada);
    sep_state_represent.exportAdaParams(ada);

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