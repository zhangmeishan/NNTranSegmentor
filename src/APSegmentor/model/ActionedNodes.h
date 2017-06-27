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

struct ActionedNodes {

	//append feature parameters
	APC2Node  app_1C_C0;
	APC2Node  app_1Wc0_C0;
	APC3Node  app_2CT_1CT_CT0;

	//separate feature parameters
	APC2Node  sep_1C_C0;
	APC2Node  sep_1Wc0_C0;
	APC3Node  sep_2CT_1CT_CT0;
	APC1Node  sep_1W;
	APC2Node  sep_1WD_1WL;
	APC1Node  sep_1WSingle;
	APC2Node  sep_1W_C0;
	APC2Node  sep_2W_1W;
	APC2Node  sep_2Wc0_1W;
	APC2Node  sep_2Wcn_1W;
	APC2Node  sep_2Wc0_1Wc0;
	APC2Node  sep_2Wcn_1Wcn;
	APC2Node  sep_2W_1WL;
	APC2Node  sep_2WL_1W;
	APC2Node  sep_2W_1Wcn;
	APC2Node  sep_1Wc0_1WL;
	APC2Node  sep_1Wcn_1WL;
	vector<APC2Node>  sep_1Wci_1Wcn;

	vector<PAddNode> outputs;

public:
	inline void initial(ModelParams& params, HyperParams& hyparams, AlignedMemoryPool* mem){
		app_1C_C0.setParam(&params.app_1C_C0);
		app_1Wc0_C0.setParam(&params.app_1Wc0_C0);
		app_2CT_1CT_CT0.setParam(&params.app_2CT_1CT_CT0);

		sep_1C_C0.setParam(&params.sep_1C_C0);
		sep_1Wc0_C0.setParam(&params.sep_1Wc0_C0);
		sep_2CT_1CT_CT0.setParam(&params.sep_2CT_1CT_CT0);
		sep_1W.setParam(&params.sep_1W);
		sep_1WD_1WL.setParam(&params.sep_1WD_1WL);
		sep_1WSingle.setParam(&params.sep_1WSingle);
		sep_1W_C0.setParam(&params.sep_1W_C0);
		sep_2W_1W.setParam(&params.sep_2W_1W);
		sep_2Wc0_1W.setParam(&params.sep_2Wc0_1W);
		sep_2Wcn_1W.setParam(&params.sep_2Wcn_1W);
		sep_2Wc0_1Wc0.setParam(&params.sep_2Wc0_1Wc0);
		sep_2Wcn_1Wcn.setParam(&params.sep_2Wcn_1Wcn);
		sep_2W_1WL.setParam(&params.sep_2W_1WL);
		sep_2WL_1W.setParam(&params.sep_2WL_1W);
		sep_2W_1Wcn.setParam(&params.sep_2W_1Wcn);
		sep_1Wc0_1WL.setParam(&params.sep_1Wc0_1WL);
		sep_1Wcn_1WL.setParam(&params.sep_1Wcn_1WL);
		sep_1Wci_1Wcn.resize(hyparams.maxlength);
		for (int idx = 0; idx < sep_1Wci_1Wcn.size(); idx++){
			sep_1Wci_1Wcn[idx].setParam(&params.sep_1Wci_1Wcn);
		}

		//allocate node memories
		app_1C_C0.init(1, -1, mem);
		app_1Wc0_C0.init(1, -1, mem);
		app_2CT_1CT_CT0.init(1, -1, mem);

		sep_1C_C0.init(1, -1, mem);
		sep_1Wc0_C0.init(1, -1, mem);
		sep_2CT_1CT_CT0.init(1, -1, mem);
		sep_1W.init(1, -1, mem);
		sep_1WD_1WL.init(1, -1, mem);
		sep_1WSingle.init(1, -1, mem);
		sep_1W_C0.init(1, -1, mem);
		sep_2W_1W.init(1, -1, mem);
		sep_2Wc0_1W.init(1, -1, mem);
		sep_2Wcn_1W.init(1, -1, mem);
		sep_2Wc0_1Wc0.init(1, -1, mem);
		sep_2Wcn_1Wcn.init(1, -1, mem);
		sep_2W_1WL.init(1, -1, mem);
		sep_2WL_1W.init(1, -1, mem);
		sep_2W_1Wcn.init(1, -1, mem);
		sep_1Wc0_1WL.init(1, -1, mem);
		sep_1Wcn_1WL.init(1, -1, mem);

		for (int idx = 0; idx < sep_1Wci_1Wcn.size(); idx++) {
			sep_1Wci_1Wcn[idx].init(1, -1, mem);
		}

		outputs.resize(hyparams.action_num);
		for (int idx = 0; idx < hyparams.action_num; idx++) {
			outputs[idx].init(1, -1, mem);
		}

	}


public:
	inline void forward(Graph* cg, const vector<CAction>& actions, const AtomFeatures& atomFeat, PNode prevStateNode){
		vector<PNode> sumNodes;
		CAction ac;
		int ac_num;
		ac_num = actions.size();
		for (int idx = 0; idx < ac_num; idx++){
			ac.set(actions[idx]);
			sumNodes.clear();
			if (ac.isAppend()){
				app_1C_C0.forward(cg, atomFeat.sid_1C, atomFeat.sid_C0);
				if (app_1C_C0.executed)sumNodes.push_back(&app_1C_C0);

				app_1Wc0_C0.forward(cg, atomFeat.sid_1Wc0, atomFeat.sid_C0);
				if (app_1Wc0_C0.executed)sumNodes.push_back(&app_1Wc0_C0);

				app_2CT_1CT_CT0.forward(cg, atomFeat.sid_2CT, atomFeat.sid_1CT, atomFeat.sid_CT0);
				if (app_2CT_1CT_CT0.executed)sumNodes.push_back(&app_2CT_1CT_CT0);
			}
			else{
				sep_1C_C0.forward(cg, atomFeat.sid_1C, atomFeat.sid_C0);
				if (sep_1C_C0.executed)sumNodes.push_back(&sep_1C_C0);

				sep_1Wc0_C0.forward(cg, atomFeat.sid_1Wc0, atomFeat.sid_C0);
				if (sep_1Wc0_C0.executed)sumNodes.push_back(&sep_1Wc0_C0);

				sep_2CT_1CT_CT0.forward(cg, atomFeat.sid_2CT, atomFeat.sid_1CT, atomFeat.sid_CT0);
				if (sep_2CT_1CT_CT0.executed)sumNodes.push_back(&sep_2CT_1CT_CT0);

				sep_1W.forward(cg, atomFeat.sid_1W);
				if (sep_1W.executed)sumNodes.push_back(&sep_1W);

				sep_1WD_1WL.forward(cg, atomFeat.sid_1WD, atomFeat.sid_1WL);
				if (sep_1WD_1WL.executed)sumNodes.push_back(&sep_1WD_1WL);

				if (atomFeat.sid_1WL == 1){
					sep_1WSingle.forward(cg, atomFeat.sid_1W);
					if (sep_1WSingle.executed)sumNodes.push_back(&sep_1WSingle);
				}

				sep_1W_C0.forward(cg, atomFeat.sid_1W, atomFeat.sid_C0);
				if (sep_1W_C0.executed)sumNodes.push_back(&sep_1W_C0);

				sep_2W_1W.forward(cg, atomFeat.sid_2W, atomFeat.sid_1W);
				if (sep_2W_1W.executed)sumNodes.push_back(&sep_2W_1W);

				sep_2Wc0_1W.forward(cg, atomFeat.sid_2Wc0, atomFeat.sid_1W);
				if (sep_2Wc0_1W.executed)sumNodes.push_back(&sep_2Wc0_1W);

				sep_2Wcn_1W.forward(cg, atomFeat.sid_2Wcn, atomFeat.sid_1W);
				if (sep_2Wcn_1W.executed)sumNodes.push_back(&sep_2Wcn_1W);

				sep_2Wc0_1Wc0.forward(cg, atomFeat.sid_2Wc0, atomFeat.sid_1Wc0);
				if (sep_2Wc0_1Wc0.executed)sumNodes.push_back(&sep_2Wc0_1Wc0);

				sep_2Wcn_1Wcn.forward(cg, atomFeat.sid_2Wcn, atomFeat.sid_1C);
				if (sep_2Wcn_1Wcn.executed)sumNodes.push_back(&sep_2Wcn_1Wcn);

				sep_2W_1WL.forward(cg, atomFeat.sid_2W, atomFeat.sid_1WL);
				if (sep_2W_1WL.executed)sumNodes.push_back(&sep_2W_1WL);

				sep_2WL_1W.forward(cg, atomFeat.sid_2WL, atomFeat.sid_1W);
				if (sep_2WL_1W.executed)sumNodes.push_back(&sep_2WL_1W);

				sep_2W_1Wcn.forward(cg, atomFeat.sid_2W, atomFeat.sid_1C);
				if (sep_2W_1Wcn.executed)sumNodes.push_back(&sep_2W_1Wcn);

				sep_1Wc0_1WL.forward(cg, atomFeat.sid_1Wc0, atomFeat.sid_1WL);
				if (sep_1Wc0_1WL.executed)sumNodes.push_back(&sep_1Wc0_1WL);

				sep_1Wcn_1WL.forward(cg, atomFeat.sid_1C, atomFeat.sid_1WL);
				if (sep_1Wcn_1WL.executed)sumNodes.push_back(&sep_1Wcn_1WL);

				for (int idx = 0; idx < atomFeat.sid_1Wci.size(); idx++){
					sep_1Wci_1Wcn[idx].forward(cg, atomFeat.sid_1Wci[idx], atomFeat.sid_1C);
					if (sep_1Wci_1Wcn[idx].executed)sumNodes.push_back(&(sep_1Wci_1Wcn[idx]));
				}
			}

			if (prevStateNode != NULL){
				sumNodes.push_back(prevStateNode);
			}

			outputs[idx].forward(cg, sumNodes);
		}
	}

};

#endif /* SRC_ActionedNodes_H_ */
