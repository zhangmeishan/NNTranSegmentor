/*
 * AtomFeatures.h
 *
 *  Created on: Aug 25, 2016
 *      Author: mszhang
 */

#ifndef SRC_AtomFeatures_H_
#define SRC_AtomFeatures_H_
#include "ModelParams.h"
struct AtomFeatures {
  public:
    string str_C0;
    string str_1C;  //equals str_1Wcn
    string str_2C;

    string str_CT0;
    string str_1CT;  //equals str_1Wcn
    string str_2CT;

    string str_1W;
    string str_1Wc0;
    vector<string> str_1Wci;

    string str_2W;
    string str_2Wc0;
    string str_2Wcn;

    string str_1WD;

    string str_1WL;
    string str_2WL;

  public:
    int sid_1WL;

    ~AtomFeatures() {
        clear();
    }
  public:
    void clear() {
        str_C0 = "";
        str_1C = "";
        str_2C = "";

        str_CT0 = "";
        str_1CT = "";
        str_2CT = "";

        str_1W = "";
        str_1Wc0 = "";
        str_1Wci.clear();

        str_2W = "";
        str_2Wc0 = "";
        str_2Wcn = "";

        str_1WD = "";
        str_1WL = "";
        str_2WL = "";

        sid_1WL = -1;
    }

  public:

    void collectFeatures(vector<string>& strFeats, const CAction&ac) {
        string strFeat = "";
        if (ac.isAppend()) {
            strFeat = "F01" + seperateKey + str_1C + seperateKey + str_C0;
            strFeats.push_back(strFeat);

            strFeat = "F02" + seperateKey + str_1Wc0 + seperateKey + str_C0;
            strFeats.push_back(strFeat);

            strFeat = "F03" + seperateKey + str_2CT + str_1CT + str_CT0;
            strFeats.push_back(strFeat);
        } else {
            strFeat = "F101" + seperateKey + str_1C + seperateKey + str_C0;
            strFeats.push_back(strFeat);

            strFeat = "F102" + seperateKey + str_1Wc0 + seperateKey + str_C0;
            strFeats.push_back(strFeat);

            strFeat = "F103" + seperateKey + str_2CT + str_1CT + str_CT0;
            strFeats.push_back(strFeat);

            strFeat = "F104" + seperateKey + str_1W;
            strFeats.push_back(strFeat);

            if (sid_1WL == 1) {
                strFeat = "F105" + seperateKey + str_1W;
                strFeats.push_back(strFeat);
            }

            strFeat = "F106" + seperateKey + str_2W + seperateKey + str_1W;
            strFeats.push_back(strFeat);

            strFeat = "F107" + seperateKey + str_1W + seperateKey + str_C0;
            strFeats.push_back(strFeat);

            strFeat = "F108" + seperateKey + str_1W + seperateKey + str_1WL;
            strFeats.push_back(strFeat);

            strFeat = "F109" + seperateKey + str_2Wc0 + seperateKey + str_1W;
            strFeats.push_back(strFeat);

            strFeat = "F110" + seperateKey + str_2Wcn + seperateKey + str_1W;
            strFeats.push_back(strFeat);

            strFeat = "F111" + seperateKey + str_1Wc0 + seperateKey + str_1C;
            strFeats.push_back(strFeat);

            strFeat = "F112" + seperateKey + str_2WL + seperateKey + str_1W;
            strFeats.push_back(strFeat);

            strFeat = "F113" + seperateKey + str_2W + seperateKey + str_1WL;
            strFeats.push_back(strFeat);

            strFeat = "F114" + seperateKey + str_2W + seperateKey + str_1C;
            strFeats.push_back(strFeat);

            for (int idy = 0; idy < str_1Wci.size(); idy++) {
                strFeat = "F115" + seperateKey + str_1C + seperateKey + str_1Wci[idy];
                strFeats.push_back(strFeat);
            }

            strFeat = "F116" + seperateKey + str_2Wc0 + seperateKey + str_1Wc0;
            strFeats.push_back(strFeat);

            strFeat = "F117" + seperateKey + str_2Wcn + seperateKey + str_1C;
            strFeats.push_back(strFeat);

            strFeat = "F118" + seperateKey + str_1WL + seperateKey + str_1C;
            strFeats.push_back(strFeat);

            strFeat = "F119" + seperateKey + str_1WL + seperateKey + str_1Wc0;
            strFeats.push_back(strFeat);

            strFeat = "F120" + seperateKey + str_1WD + seperateKey + str_1WL;
            strFeats.push_back(strFeat);
        }
    }

};

#endif /* SRC_AtomFeatures_H_ */
