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

    vector<APNode> sparse_features;
    vector<PAddNode> outputs;

    ~ActionedNodes() {
        outputs.clear();
    }

  public:
    inline void initial(ModelParams& params, HyperParams& hyparams) {
        outputs.resize(hyparams.action_num);
        sparse_features.resize(hyparams.action_num);
        for (int idx = 0; idx < hyparams.action_num; idx++) {
            sparse_features[idx].setParam(&params.sep_app_feats);
            sparse_features[idx].init(1, -1);
            outputs[idx].init(1, -1);
        }

    }


  public:
    inline void forward(Graph* cg, const vector<CAction>& actions, const AtomFeatures& atomFeat, PNode prevStateNode) {
        vector<PNode> sumNodes;
        vector<string> strFeats;
        string strFeat = "";
        CAction ac;
        int ac_num;
        ac_num = actions.size();
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
            sumNodes.push_back(&sparse_features[idx]);

            if (prevStateNode != NULL) {
                sumNodes.push_back(prevStateNode);
            }

            outputs[idx].forward(cg, sumNodes);
        }
    }

};

#endif /* SRC_ActionedNodes_H_ */
