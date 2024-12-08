#pragma once
#include "stdafx.h"
#include "IT.h"

namespace FST
{
	struct RELATION
	{
		char symbol;
		short nnode;
		RELATION(
			char c = 0x00,
			short ns = 0
		);
	};

	struct NODE
	{
		short n_relation;
		RELATION* relations;
		NODE();
		NODE(short n, RELATION rel, ...);
	};

	struct FST
	{
		unsigned char* chain;
		short position;
		short nstates;
		NODE* nodes;
		short* rstates;
		FST(unsigned char* s, short ns, NODE n, ...);
	};

	bool execute(FST& fst);
	bool step(FST& fst, short*& rstates);
	void GetLexem(LT::LexTable& lextable, IT::IDTable& idtable, In::IN in);
	char FiniteAutomats(unsigned char* word);
	bool check_int(unsigned char* word);
	void Analyser(LT::LexTable lex_table);
	bool SAnaliser(unsigned char* line);

}