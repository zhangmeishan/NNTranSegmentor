#ifndef SRC_ModelParams_H_
#define SRC_ModelParams_H_
#include "HyperParams.h"

// Each model consists of two parts, building neural graph and defining output losses.
class ModelParams {
  public:
    Alphabet sparsefeats;
    APParams  sep_app_feats;

  public:
    bool initial(HyperParams& opts) {
        sep_app_feats.initial(&sparsefeats, 1, opts.base);
        return true;
    }

    void exportModelParams(ModelUpdate& ada) {
        sep_app_feats.exportAdaParams(ada);
    }

    // will add it later
    void saveModel() {

    }

    void loadModel(const string& inFile) {

    }

};

#endif /* SRC_ModelParams_H_ */