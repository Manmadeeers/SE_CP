#pragma once
#include "stdafx.h"
#define ID_MAXSIZE 5
#define IT_MAXSIZE 4096
#define INT_DEFAULT 0x00000000
#define STR_DEFAULT 0x00
#define NULL_INDEX 0xffffffff
#define STR_MAXSIZE 255

namespace IT {
	enum DATATYPES { UNT = 1, SYM = 2 ,BOO = 3};
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4 };
	struct Entry {
		int first_line_ID;//link to the lexem table
		char* id;
		DATATYPES IDDataType;
		IDTYPE IDType;
		union {
			char* unt_val;
			char* bool_val;
			char sym_val;
		}value;
		char* scope;
	};

	struct IDTable {
		int literal_count;
		int maxsize;
		int size;
		Entry* table;
	};
	IDTable Create(int size);
	void AddToIDTable(IDTable& idtable, Entry entry);
	Entry GetEntry(IDTable& idtable, int str_num);
	int IsId(IDTable& idtable, char id[ID_MAXSIZE]);
	void PrintIdTable(IDTable IDTable);
	void DeleteIdTable(IDTable& idtable);
	bool CheckLiteralPresense(IDTable idtable, Entry ID);
	bool checkIDorFuncPresense(IDTable table, Entry id);
}