
#include "stdafx.h"

namespace IT {
	IDTable Create(int size) {
		if (size > IT_MAXSIZE) {
			throw ERROR_THROW(68);
		}
		IDTable newIDTable;
		newIDTable.size = 0;
		newIDTable.table = new Entry[size];
		newIDTable.maxsize = ID_MAXSIZE;
		newIDTable.literal_count = 0;
		return newIDTable;
	}

	void AddToIDTable(IDTable& idtable, Entry entry) {
		idtable.table[idtable.size] = entry;
		idtable.size++;
	}

	Entry GetEntry(IDTable& idtable, int str_num) {
		if (str_num >= ID_MAXSIZE || str_num < 0) {
			throw ERROR_THROW(67);
		}
		Entry IDTableElem = idtable.table[str_num];
		return IDTableElem;
	}

	int IsId(IDTable& idtable, char id[ID_MAXSIZE]) {
		for (int i = 0; i < idtable.size; i++) {
			if (idtable.table[i].id == id) {
				return i;
			}
		}
		return NULL_INDEX;
	}
	bool CheckLiteralPresense(IDTable idtable, Entry ID) {
		DATATYPES id_type = ID.IDDataType;
		
		for (int i = 0; i < idtable.size; i++) {
			Entry current = idtable.table[i];
			
			if (id_type == UNT&&current.IDDataType==UNT&&current.IDType==IT::L) {
				int iterator = 0;
				bool equal = true;
				while (ID.value.unt_val[iterator] != '\0') {
					if (ID.value.unt_val[iterator] != current.value.unt_val[iterator]) {
						equal = false;
						break;
					}
					iterator++;
				}
				if (equal) {
					return true;
				}
				else {
					continue;
				}
			}
			else if(id_type==SYM&&current.IDDataType==SYM&&current.IDType == IT::L) {
				if (current.value.sym_val == ID.value.sym_val) {
					return true;
				}
			}
			else if (id_type == BOO && current.IDDataType == BOO&& current.IDType == IT::L) {
				if (current.value.bool_val == ID.value.bool_val) {
					return true;
				}
			}
		}
		return false;
	}

	bool checkIDorFuncPresense(IDTable table, Entry id) {

		for (int i = 0; i < table.size; i++) {
			Entry current = table.table[i];
			if (id.IDType==IT::F) {
				if (current.IDType == IT::F) {
					if (strcmp(id.id, current.id) == 0) {
						return true;
					}
				}
			
			}
			else if (id.IDType == IT::V) {
				if (current.IDType == IT::V || current.IDType == IT::P) {
					if (current.scope == id.scope) {
						if (strcmp(id.id, current.id) == 0) {
							return true;
						}
					}
				}
			}
		}
		return false;

	}

	void PrintIdTable(IDTable IDTable) {
		cout << "<-----Identifier table----->" << endl;
		cout << "Identifier data types: " << "1 - UNT   2 - SYM   3 - BOOL" << endl;
		cout << "Identifier types: " << "1-Variable   2-Function   3-Parametres   4-Literal(sym, unt or bool)" << endl << endl;


		cout << " ¹" << '\t' << "Identifier" << '\t' << '\t' << "Data type" << '\t' << '\t' << "Identifier type" << "\t\t" << "Scope" << endl;
		for (int i = 0; i < IDTable.size; i++) {
			IT::Entry current = IDTable.table[i];
			if (current.first_line_ID <= 9) {
				if (current.IDType == IT::L) {
					if (current.IDDataType == IT::UNT) {
						cout << "0" << current.first_line_ID << "\t" << current.id << "\t\t" << current.IDDataType << "\t\t\t" << current.IDType << " ( " << current.value.unt_val << " ) " << "\t\t" << current.scope << endl;
					}
					else if (current.IDDataType == IT::BOO) {
						cout << "0" << current.first_line_ID << "\t" << current.id << "\t\t" << current.IDDataType << "\t\t\t" << current.IDType << " ( " << current.value.bool_val << " ) " << "\t\t" << current.scope << endl;
					}

					else {
						cout << "0" << current.first_line_ID << "\t" << current.id << "\t\t" << current.IDDataType << "\t\t\t" << current.IDType << " ( " << current.value.sym_val << " )" << "\t\t\t" << current.scope << endl;
					}

				}
				else {
					cout << "0" << current.first_line_ID << "\t" << current.id << "\t\t\t" << current.IDDataType << "\t\t\t" << current.IDType << "\t\t\t" << current.scope << endl;
				}

			}
			else {
				if (current.IDType == IT::L) {
					if (current.IDDataType == IT::UNT) {
						cout << current.first_line_ID << "\t" << current.id << "\t\t" << current.IDDataType << "\t\t\t" << current.IDType << " ( " << current.value.unt_val << " )" << "\t\t" << current.scope << endl;
					}
					else if (current.IDDataType == IT::BOO) {
						cout << current.first_line_ID << "\t" << current.id << "\t\t" << current.IDDataType << "\t\t\t" << current.IDType << " ( " << current.value.bool_val << " )" << "\t\t" << current.scope << endl;
					}

					else {
						cout << current.first_line_ID << "\t" << current.id << "\t\t" << current.IDDataType << "\t\t\t" << current.IDType << " ( " << current.value.sym_val << " )" << "\t\t\t" << current.scope << endl;
					}

				}
				else {
					cout << current.first_line_ID << "\t" << current.id << "\t\t\t" << current.IDDataType << "\t\t\t" << current.IDType << "\t\t\t" << current.scope << endl;
				}
			}

		}
	}

	void DeleteIdTable(IDTable& idtable) {
		//delete[]idtable.lits;
		delete[]idtable.table;

	}

};
