#pragma once
#include "stdafx.h"
#define LEXEM_FIXSIZE 1
#define LT_MAXSIZE 4096
#define LT_NULLINDEX 0xffffffff
#define LEX_DATATYPE 't'
#define LEX_ID 'i'
#define LEX_LITERAL 'l'
#define LEX_FUNCTION 'f'
#define LEX_CREATE 'c'
#define LEX_RETURN 'r'
#define LEX_WRITE 'p'
#define LEX_WRITELINE 'P'
#define LEX_MAIN 'm'
#define LEX_MATH 'v'
#define LEX_RIGHT_MOVE 'R'
#define LEX_LEFT_MOVE 'L'
#define LEX_LOOP 'u'
#define LEX_UNDEF 'U'
#define STR_END 'E'
#define LEX_EQUALS '='

namespace LT {
	struct Entry
	{
		char lexem;
		int src_str_num;
		int index;
	};

	struct LexTable {
		int maxsize;//lexem table capacity(less then LT_MAXSIZE)
		int size;//current lexem table size
		Entry* table;
	};
	LexTable Create(int size);
	void AddToLexTable(LexTable& LexTable, Entry entry);
	Entry GetEntry(LexTable& LexTable, int str_num);
	void DeleteLexTable(LexTable& LexTable);
};