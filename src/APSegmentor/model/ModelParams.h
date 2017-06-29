#ifndef SRC_ModelParams_H_
#define SRC_ModelParams_H_
#include "HyperParams.h"

// Each model consists of two parts, building neural graph and defining output losses.
class ModelParams{

public:
	//should be initialized outside
	Alphabet words; // words
	Alphabet chars; // chars
	Alphabet charTypes; // char type



	//feature templates
	//append feature parameters
	APC2Params  app_1C_C0;
	APC2Params  app_1Wc0_C0;
	APC3Params  app_2CT_1CT_CT0;

	//separate feature parameters
	APC2Params  sep_1C_C0;
	APC2Params  sep_1Wc0_C0;
	APC3Params  sep_2CT_1CT_CT0;
	APC1Params  sep_1W;
	APC2Params  sep_1WD_1WL;
	APC1Params  sep_1WSingle;
	APC2Params  sep_1W_C0;
	APC2Params  sep_2W_1W;
	APC2Params  sep_2Wc0_1W;
	APC2Params  sep_2Wcn_1W;
	APC2Params  sep_2Wc0_1Wc0;
	APC2Params  sep_2Wcn_1Wcn;
	APC2Params  sep_2W_1WL;
	APC2Params  sep_2WL_1W;
	APC2Params  sep_2W_1Wcn;
	APC2Params  sep_1Wc0_1WL;
	APC2Params  sep_1Wcn_1WL;
	APC2Params  sep_1Wci_1Wcn;


public:
	bool initial(HyperParams& opts){
		// some model parameters should be initialized outside
		if (words.size() <= 0 || chars.size() <= 0){
			return false;
		}
		app_1C_C0.initial();
		app_1Wc0_C0.initial();
		app_2CT_1CT_CT0.initial();

		sep_1C_C0.initial();
		sep_1Wc0_C0.initial();
		sep_2CT_1CT_CT0.initial();
		sep_1W.initial();
		sep_1WD_1WL.initial();
		sep_1WSingle.initial();
		sep_1W_C0.initial();
		sep_2W_1W.initial();
		sep_2Wc0_1W.initial();
		sep_2Wcn_1W.initial();
		sep_2Wc0_1Wc0.initial();
		sep_2Wcn_1Wcn.initial();
		sep_2W_1WL.initial();
		sep_2WL_1W.initial();
		sep_2W_1Wcn.initial();
		sep_1Wc0_1WL.initial();
		sep_1Wcn_1WL.initial();
		sep_1Wci_1Wcn.initial();

		return true;
	}


	void exportModelParams(ModelUpdate& ada){
		app_1C_C0.exportAdaParams(ada);
		app_1Wc0_C0.exportAdaParams(ada);
		app_2CT_1CT_CT0.exportAdaParams(ada);

		sep_1C_C0.exportAdaParams(ada);
		sep_1Wc0_C0.exportAdaParams(ada);
		sep_2CT_1CT_CT0.exportAdaParams(ada);
		sep_1W.exportAdaParams(ada);
		sep_1WD_1WL.exportAdaParams(ada);
		sep_1WSingle.exportAdaParams(ada);
		sep_1W_C0.exportAdaParams(ada);
		sep_2W_1W.exportAdaParams(ada);
		sep_2Wc0_1W.exportAdaParams(ada);
		sep_2Wcn_1W.exportAdaParams(ada);
		sep_2Wc0_1Wc0.exportAdaParams(ada);
		sep_2Wcn_1Wcn.exportAdaParams(ada);
		sep_2W_1WL.exportAdaParams(ada);
		sep_2WL_1W.exportAdaParams(ada);
		sep_2W_1Wcn.exportAdaParams(ada);
		sep_1Wc0_1WL.exportAdaParams(ada);
		sep_1Wcn_1WL.exportAdaParams(ada);
		sep_1Wci_1Wcn.exportAdaParams(ada);
	}


	inline void setFixed(){
		app_1C_C0.setFixed();
		app_1Wc0_C0.setFixed();
		app_2CT_1CT_CT0.setFixed();

		sep_1C_C0.setFixed();
		sep_1Wc0_C0.setFixed();
		sep_2CT_1CT_CT0.setFixed();
		sep_1W.setFixed();
		sep_1WD_1WL.setFixed();
		sep_1WSingle.setFixed();
		sep_1W_C0.setFixed();
		sep_2W_1W.setFixed();
		sep_2Wc0_1W.setFixed();
		sep_2Wcn_1W.setFixed();
		sep_2Wc0_1Wc0.setFixed();
		sep_2Wcn_1Wcn.setFixed();
		sep_2W_1WL.setFixed();
		sep_2WL_1W.setFixed();
		sep_2W_1Wcn.setFixed();
		sep_1Wc0_1WL.setFixed();
		sep_1Wcn_1WL.setFixed();
		sep_1Wci_1Wcn.setFixed();
	}

	// will add it later
	void saveModel(){

	}

	void loadModel(const string& inFile){

	}

};

#endif /* SRC_ModelParams_H_ */