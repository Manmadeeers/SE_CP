
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
			if (current.IDType == L && current.IDDataType == ID.IDDataType) {
				if (id_type == INT) {
					if (current.value.vint == ID.value.vint) {
						return true;
					}
				}
				else {
					if (current.value.vstr.str == ID.value.vstr.str) {
						return true;
					}
				}
			}
		}
		return false;
	}

	void DeleteIdTable(IDTable& idtable) {
		idtable.table = nullptr;
		delete[] idtable.table;
		idtable.size = 0;
	}

};
