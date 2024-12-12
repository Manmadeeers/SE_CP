
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

	void DeleteIdTable(IDTable& idtable) {
		//delete[]idtable.lits;
		delete[]idtable.table;

	}

};
