//#include "stdafx.h"
#include "Semantic.h"

namespace SA {

	void ParseForKeyWords(IT::IDTable table) {

		for (int i = 0; i < table.size; i++) {
			IT::Entry current = table.table[i];
			if (strcmp(current.id,"Return")==0|| strcmp(current.id, "main") == 0 || strcmp(current.id, "writeline") == 0
				|| strcmp(current.id, "write") == 0 || strcmp(current.id, "Create") == 0|| strcmp(current.id, "Function")==0|| strcmp(current.id, "Until")) {
				throw ERROR_THROW_IN(700, current.first_line_ID, -1, (unsigned char*)"");
			}
			if (current.IDType == IT::F) {
				char* curr_func_id = current.id;
				for (int j = 0; j < table.size; j++) {
					if (table.table[j].IDType == IT::F) {
						if (strcmp(table.table[j].id, curr_func_id)) {
							throw ERROR_THROW_IN(701, current.first_line_ID, 0, (unsigned char*)"");
						}
					}
				}
			}
			if (current.IDType == IT::V) {
				char* curr_id = current.id;
				for (int k = 0; k < table.size; k++) {
					if (table.table[k].IDDataType == IT::V) {
						if (strcmp(table.table[k].id, curr_id) == 0) {
							throw ERROR_THROW_IN(702, current.first_line_ID, -1, (unsigned char*)"");
						}
					}
				}
			}


		}
	}


	void CheckTypes(IT::IDTable itable,LT::LexTable ltable) {
		
	
		for (int i = 0; i < ltable.size; i++) {
			LT::Entry current = ltable.table[i];
			if (current.lexem == LEX_CREATE) {
				 int itable_pos= current.src_str_num;
				 IT::Entry lit;
				 IT::Entry ident;
				 int control = 0;
				for (int j = 0; j < itable.size; j++) {
					if (itable.table[j].first_line_ID == itable_pos && itable.table[j].IDType == IT::L) {
						lit = itable.table[j];
						control++;
					}
					else if (itable.table[j].first_line_ID == itable_pos && itable.table[j].IDType == IT::V) {
						ident = itable.table[j];
						control++;
					}
					if (control == 2) {
						break;
					}

				}
				if (control == 2) {
					if (lit.IDDataType != ident.IDDataType) {
						throw ERROR_THROW_IN(708, itable_pos, 0, (unsigned char*)ident.id);
					}
				}
				

			}
			else if (current.lexem == LEX_ID) {
				if (ltable.table[i + 1].lexem == LEX_RIGHT_MOVE || ltable.table[i + 1].lexem == LEX_LEFT_MOVE) {
					int itable_pos = current.src_str_num;
					for (int j = 0; j < itable.size; j++) {
						if (itable.table[j].first_line_ID == itable_pos) {
							if (itable.table[j].IDDataType != IT::UNT) {
								throw ERROR_THROW_IN(705, itable_pos, 0, (unsigned char*)"");
							}
						}
					}
				}
			}
		}

	}

	void ProceedSemanticAnalysis(LT::LexTable ltable, IT::IDTable itable) {

		//ParseForKeyWords(itable);
		CheckTypes(itable,ltable);
	}
}