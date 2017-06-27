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
	SparseC2Node  app_1C_C0;
	SparseC2Node  app_1Wc0_C0;
	SparseC3Node  app_2CT_1CT_CT0;

	//separate feature parameters
	SparseC2Node  sep_1C_C0;
	SparseC2Node  sep_1Wc0_C0;
	SparseC3Node  sep_2CT_1CT_CT0;
	SparseC1Node  sep_1W;
	SparseC2Node  sep_1WD_1WL;
	SparseC1Node  sep_1WSingle;
	SparseC2Node  sep_1W_C0;
	SparseC2Node  sep_2W_1W;
	SparseC2Node  sep_2Wc0_1W;
	SparseC2Node  sep_2Wcn_1W;
	SparseC2Node  sep_2Wc0_1Wc0;
	SparseC2Node  sep_2Wcn_1Wcn;
	SparseC2Node  sep_2W_1WL;
	SparseC2Node  sep_2WL_1W;
	SparseC2Node  sep_2W_1Wcn;
	SparseC2Node  sep_1Wc0_1WL;
	SparseC2Node  sep_1Wcn_1WL;
	vector<SparseC2Node>  sep_1Wci_1Wcn;
	
    LookupNode last_word_input;
    IncLSTM1Builder word_lstm;
    ConcatNode word_state_concat;
    UniNode word_state_hidden;

    PSubNode char_span_repsent_left;
    PSubNode char_span_repsent_right;
    ConcatNode char_state_concat;
    UniNode char_state_hidden;

    UniNode app_state_represent;
    BiNode sep_state_represent;

    LinearNode app_score;
    LinearNode sep_score;	

	vector<PAddNode> outputs;

    BucketNode bucket_char, bucket_word;
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


        //neural features
        last_word_input.setParam(&(params.word_table));
        last_word_input.init(hyparams.word_dim, hyparams.dropProb, mem);
        word_lstm.init(&(params.word_lstm), hyparams.dropProb, mem); //already allocated here
        word_state_concat.init(hyparams.word_feat_dim, -1, mem);
        word_state_hidden.setParam(&(params.word_state_hidden));
        word_state_hidden.init(hyparams.word_state_dim, hyparams.dropProb, mem);

        char_span_repsent_left.init(hyparams.char_lstm_dim, -1, mem);
        char_span_repsent_right.init(hyparams.char_lstm_dim, -1, mem);
        char_state_concat.init(hyparams.char_feat_dim, -1, mem);
        char_state_hidden.setParam(&params.char_state_hidden);
        char_state_hidden.init(hyparams.char_state_dim, hyparams.dropProb, mem);

        app_state_represent.setParam(&params.app_state_represent);
        app_state_represent.init(hyparams.app_dim, hyparams.dropProb, mem);
        sep_state_represent.setParam(&params.sep_state_represent);
        sep_state_represent.init(hyparams.sep_dim, hyparams.dropProb, mem);


        app_score.setParam(&(params.app_score));
        app_score.init(1, -1, mem);
        sep_score.setParam(&(params.sep_score));
        sep_score.init(1, -1, mem);
		
		outputs.resize(hyparams.action_num);
		for (int idx = 0; idx < hyparams.action_num; idx++) {
			outputs[idx].init(1, -1, mem);
		}
		
		bucket_char.init(hyparams.char_lstm_dim, -1, mem);
        bucket_word.init(hyparams.word_lstm_dim, -1, mem);
	}


public:
	inline void forward(Graph* cg, const vector<CAction>& actions, const AtomFeatures& atomFeat, PNode prevStateNode){
		vector<PNode> sumNodes;
		CAction ac;
		int ac_num;
		ac_num = actions.size();
		
        bucket_char.forward(cg, 0);
        bucket_word.forward(cg, 0);
        PNode pseudo_char = &(bucket_char);
        PNode pseudo_word = &(bucket_word);



        vector<PNode> wordNodes;
        last_word_input.forward(cg, atomFeat.str_1W);
        word_lstm.forward(cg, &last_word_input, atomFeat.p_word_lstm);
        wordNodes.push_back(&word_lstm._hidden);
        if (word_lstm._nSize > 1) {
            wordNodes.push_back(&word_lstm._pPrev->_hidden);
        }
        else {
            wordNodes.push_back(pseudo_word);
        }
        word_state_concat.forward(cg, wordNodes);
        word_state_hidden.forward(cg, &word_state_concat);


        //
        vector<PNode> charNodes;
        int char_posi = atomFeat.next_position;
        PNode char_node_left_curr = (char_posi  < atomFeat.char_size) ? &(atomFeat.p_char_left_lstm->_hiddens[char_posi]) : pseudo_char;
        PNode char_node_left_next1 = (char_posi + 1  < atomFeat.char_size) ? &(atomFeat.p_char_left_lstm->_hiddens[char_posi + 1]) : pseudo_char;
        PNode char_node_left_next2 = (char_posi + 2  < atomFeat.char_size) ? &(atomFeat.p_char_left_lstm->_hiddens[char_posi + 2]) : pseudo_char;
        PNode char_node_left_prev1 = (char_posi > 0) ? &(atomFeat.p_char_left_lstm->_hiddens[char_posi - 1]) : pseudo_char;
        PNode char_node_left_prev2 = (char_posi > 1) ? &(atomFeat.p_char_left_lstm->_hiddens[char_posi - 2]) : pseudo_char;

        PNode char_node_right_curr = (char_posi  < atomFeat.char_size) ? &(atomFeat.p_char_right_lstm->_hiddens[char_posi]) : pseudo_char;
        PNode char_node_right_next1 = (char_posi + 1  < atomFeat.char_size) ? &(atomFeat.p_char_right_lstm->_hiddens[char_posi + 1]) : pseudo_char;
        PNode char_node_right_next2 = (char_posi + 2  < atomFeat.char_size) ? &(atomFeat.p_char_right_lstm->_hiddens[char_posi + 2]) : pseudo_char;
        PNode char_node_right_prev1 = (char_posi > 0) ? &(atomFeat.p_char_right_lstm->_hiddens[char_posi - 1]) : pseudo_char;
        PNode char_node_right_prev2 = (char_posi > 1) ? &(atomFeat.p_char_right_lstm->_hiddens[char_posi - 2]) : pseudo_char;

        charNodes.push_back(char_node_left_curr);
        charNodes.push_back(char_node_left_next1);
        charNodes.push_back(char_node_left_next2);
        charNodes.push_back(char_node_left_prev1);
        charNodes.push_back(char_node_left_prev2);

        charNodes.push_back(char_node_right_curr);
        charNodes.push_back(char_node_right_next1);
        charNodes.push_back(char_node_right_next2);
        charNodes.push_back(char_node_right_prev1);
        charNodes.push_back(char_node_right_prev2);

        PNode char_lstm_left_start = atomFeat.word_start > 0 ? &(atomFeat.p_char_left_lstm->_hiddens[atomFeat.word_start - 1]) : pseudo_char;
        PNode char_lstm_left_end = char_node_left_prev1;

        PNode char_lstm_right_start = atomFeat.word_start >= 0 ? &(atomFeat.p_char_right_lstm->_hiddens[atomFeat.word_start]) : pseudo_char;
        PNode char_lstm_right_end = char_node_right_curr;

        char_span_repsent_left.forward(cg, char_lstm_left_end, char_lstm_left_start);
        charNodes.push_back(&char_span_repsent_left);
        char_span_repsent_right.forward(cg, char_lstm_right_start, char_lstm_right_end);
        charNodes.push_back(&char_span_repsent_right);

        char_state_concat.forward(cg, charNodes);
        char_state_hidden.forward(cg, &char_state_concat);

        app_state_represent.forward(cg, &char_state_hidden);
        sep_state_represent.forward(cg, &char_state_hidden, &word_state_hidden);
				
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
			
         if (ac.isAppend()) {
                app_score.forward(cg, &app_state_represent);
                sumNodes.push_back(&app_score);
            }
            else if (ac.isSeparate() || ac.isFinish()) {
                sep_score.forward(cg, &sep_state_represent);
                sumNodes.push_back(&sep_score);
            }
            else {
                std::cout << "error action here" << std::endl;
            }			

			outputs[idx].forward(cg, sumNodes);
		}
	}

};

#endif /* SRC_ActionedNodes_H_ */
