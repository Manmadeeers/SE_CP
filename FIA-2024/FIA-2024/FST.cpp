#include "stdafx.h"

#define QUOTE '\''



namespace FST
{

	RELATION::RELATION(char c, short nn)
	{
		symbol = c;
		nnode = nn;
	}
	NODE::NODE()
	{
		n_relation = 0;
		RELATION* relations = NULL;
	}
	NODE::NODE(short n, RELATION rel, ...)
	{
		n_relation = n;
		RELATION* p = &rel;
		relations = new RELATION[n];
		for (int i = 0; i < n; i++)
		{
			relations[i] = p[i];
		}
	}
	FST::FST(unsigned char* s, short ns, NODE n, ...)
	{
		chain = s;
		nstates = ns;
		nodes = new NODE[ns];
		NODE* p = &n;
		for (int i = 0; i < ns; i++)
		{
			nodes[i] = p[i];
		}
		rstates = new short[nstates];
		memset(rstates, 0xff, sizeof(short) * nstates);
		rstates[0] = 0;
		position = -1;
	}

	bool step(FST& fst, short*& rstates)
	{
		bool rc = false;
		std::swap(rstates, fst.rstates);
		for (short i = 0; i < fst.nstates; i++)
		{
			if (rstates[i] == fst.position)
				for (short j = 0; j < fst.nodes[i].n_relation; j++)
				{
					if (fst.nodes[i].relations[j].symbol == fst.chain[fst.position])
					{
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					}
				}
		}
		return rc;
	}

	bool execute(FST& fst)
	{
		short* rstates = new short[fst.nstates];
		memset(rstates, 0xff, sizeof(short) * fst.nstates);
		short lstring = strlen((const char*)fst.chain);
		bool rc = true;
		for (short i = 0; i < lstring && rc; i++)
		{
			fst.position++;
			rc = step(fst, rstates);
		}
		delete[] rstates;
		return(rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
	}



	char FiniteAutomats(unsigned char* word) {

		if (word[0] == ' ' || word[0] == '\0' || word[0] == '|') {
			return LEX_SKIP;
		}
		if (word[0] == '/' && word[1] == '/') {
			ERROR_THROW(90);
		}

		if (word[0] == '>' && word[1] == '>') {
			return LEX_RIGHT_MOVE;
		}
		if (word[0] == '<' && word[1] == '<') {
			return LEX_LEFT_MOVE;
		}
		char special[] = { '(',')','{','}',';',',','<','>'};
		char signs[] = { '+','-','/','*' };
		if ((char*)word == (char*)STR_END) {
			return STR_END;
		}
		const int spec_size = 13;
		const int sign_size = 4;

		for (int j = 0; j < spec_size; j++) {
			if (word[0] == special[j]) {
				return special[j];
			}
		}

		for (int k = 0; k < sign_size; k++) {
			if (word[0] == signs[k]) {
				return signs[k];
			}
		}
		FST equals_au(
			word,
			3,
			NODE(1, RELATION('=', 1)),
			NODE(1, RELATION('=', 2)),
			NODE()
		);

		if (execute(equals_au)) {
			return LEX_DEQUALS;
		}


		if (word[0] == '=') {
			return LEX_EQUALS;
		}
	

		FST loop_au(
			word,
			6,
			NODE(1, RELATION('u',1)),
			NODE(1,RELATION('n',2)),
			NODE(1,RELATION('t',3)),
			NODE(1,RELATION('i',4)),
			NODE(1,RELATION('l',5)),
			NODE()
		);

		if (execute(loop_au)) {
			return LEX_LOOP;
		}

		FST unt_au(
			word,
			4,
			NODE(1, RELATION('u', 1)),
			NODE(1, RELATION('n', 2)),
			NODE(1, RELATION('t', 3)),
			NODE()
		);
		if (execute(unt_au)) {
			return LEX_DATATYPE;
		}

		FST sym_au(
			word,
			4,
			NODE(1, RELATION('s', 1)),
			NODE(1, RELATION('y', 2)),
			NODE(1, RELATION('m', 3)),
			NODE()
		);
		if (execute(sym_au)) {
			return LEX_DATATYPE;
		}

		FST bol_au(
			word,
			5,
			NODE(1, RELATION('b', 1)),
			NODE(1, RELATION('o', 2)),
			NODE(1, RELATION('o', 3)),
			NODE(1, RELATION('l', 4)),
			NODE()
		);

		if (execute(bol_au)) {
			return LEX_DATATYPE;
		}


		FST function_au(
			word,
			9,
			NODE(1, RELATION('f', 1)),
			NODE(1, RELATION('u', 2)),
			NODE(1, RELATION('n', 3)),
			NODE(1, RELATION('c', 4)),
			NODE(1, RELATION('t', 5)),
			NODE(1, RELATION('i', 6)),
			NODE(1, RELATION('o', 7)),
			NODE(1, RELATION('n', 8)),
			NODE()
		);

		if (execute(function_au)) {
			return LEX_FUNCTION;
		}

		FST create_au(
			word,
			7,
			NODE(1, RELATION('c', 1)),
			NODE(1, RELATION('r', 2)),
			NODE(1, RELATION('e', 3)),
			NODE(1, RELATION('a', 4)),
			NODE(1, RELATION('t', 5)),
			NODE(1, RELATION('e', 6)),
			NODE()
		);

		if (execute(create_au)) {
			return LEX_CREATE;
		}

		FST return_au(
			word,
			7,
			NODE(1, RELATION('r', 1)),
			NODE(1, RELATION('e', 2)),
			NODE(1, RELATION('t', 3)),
			NODE(1, RELATION('u', 4)),
			NODE(1, RELATION('r', 5)),
			NODE(1, RELATION('n', 6)),
			NODE()
		);

		if (execute(return_au)) {
			return LEX_RETURN;
		}

		FST write_au(
			word,
			6,
			NODE(1, RELATION('W', 1)),
			NODE(1, RELATION('r', 2)),
			NODE(1, RELATION('i', 3)),
			NODE(1, RELATION('t', 4)),
			NODE(1, RELATION('e', 5)),
			NODE()
		);

		if (execute(write_au)) {
			return LEX_WRITE;
		}

		FST writeline_au(
			word,
			10,
			NODE(1, RELATION('W', 1)),
			NODE(1, RELATION('r', 2)),
			NODE(1, RELATION('i', 3)),
			NODE(1, RELATION('t', 4)),
			NODE(1, RELATION('e', 5)),
			NODE(1, RELATION('L', 6)),
			NODE(1, RELATION('i', 7)),
			NODE(1, RELATION('n', 8)),
			NODE(1, RELATION('e', 9)),
			NODE()
		);

		if (execute(writeline_au)) {
			return LEX_WRITELINE;
		}
		FST main_au(
			word,
			5,
			NODE(1, RELATION('M', 1)),
			NODE(1, RELATION('a', 2)),
			NODE(1, RELATION('i', 3)),
			NODE(1, RELATION('n', 4)),
			NODE()
		);

		if (execute(main_au)) {
			return LEX_MAIN;
		}
		FST unt_literal_au(
			word,
			5,
			NODE(1, RELATION('0', 1)),
			NODE(1, RELATION('x', 2)),
			NODE(16,
				RELATION('0', 3), RELATION('1', 3),
				RELATION('2', 3), RELATION('3', 3),
				RELATION('4', 3), RELATION('5', 3),
				RELATION('6', 3), RELATION('7', 3),
				RELATION('8', 3), RELATION('9', 3),

				RELATION('A', 3), RELATION('B', 3),
				RELATION('C', 3), RELATION('D', 3),
				RELATION('E', 3), RELATION('F', 3)
			),
			NODE(16,
				RELATION('0', 4), RELATION('1', 4),
				RELATION('2', 4), RELATION('3', 4),
				RELATION('4', 4), RELATION('5', 4),
				RELATION('6', 4), RELATION('7', 4),
				RELATION('8', 4), RELATION('9', 4),

				RELATION('A', 4), RELATION('B', 4),
				RELATION('C', 4), RELATION('D', 4),
				RELATION('E', 4), RELATION('F', 4)
				),
			NODE()
		);
		if (execute(unt_literal_au)) {
			return LEX_LITERAL;
		}

		FST sym_literal_au(
			word,
			4,
			NODE(1, RELATION('\'', 1)),
			NODE(52,
				RELATION('A', 2), RELATION('B', 2),
				RELATION('C', 2), RELATION('D', 2),
				RELATION('E', 2), RELATION('F', 2),
				RELATION('G', 2), RELATION('H', 2),
				RELATION('I', 2), RELATION('J', 2),
				RELATION('K', 2), RELATION('L', 2),
				RELATION('M', 2), RELATION('N', 2),
				RELATION('O', 2), RELATION('P', 2),
				RELATION('Q', 2), RELATION('R', 2),
				RELATION('S', 2), RELATION('T', 2),
				RELATION('U', 2), RELATION('V', 2),
				RELATION('W', 2), RELATION('X', 2),
				RELATION('Y', 2), RELATION('Z', 2),
				RELATION('a', 2), RELATION('b', 2),
				RELATION('c', 2), RELATION('d', 2),
				RELATION('e', 2), RELATION('f', 2),
				RELATION('g', 2), RELATION('h', 2),
				RELATION('i', 2), RELATION('j', 2),
				RELATION('k', 2), RELATION('l', 2),
				RELATION('m', 2), RELATION('n', 2),
				RELATION('o', 2), RELATION('p', 2),
				RELATION('q', 2), RELATION('r', 2),
				RELATION('s', 2), RELATION('t', 2),
				RELATION('u', 2), RELATION('v', 2),
				RELATION('w', 2), RELATION('x', 2),
				RELATION('y', 2), RELATION('z', 2)
			),
			NODE(1, RELATION('\'', 3)),
			NODE()
		);

		if (execute(sym_literal_au)) {
			return LEX_LITERAL;
		}

		FST logic_literal_au1(
			word,
			5,
			NODE(1, RELATION('T', 1)),
			NODE(1, RELATION('r', 2)),
			NODE(1, RELATION('u', 3)),
			NODE(1, RELATION('e', 4)),
			NODE()
		);

		if (execute(logic_literal_au1)) {
			return LEX_LITERAL;
		}

		FST logic_literal_au0(
			word,
			6,
			NODE(1, RELATION('F', 1)),
			NODE(1, RELATION('a', 2)),
			NODE(1, RELATION('l', 3)),
			NODE(1, RELATION('s', 4)),
			NODE(1, RELATION('e', 5)),
			NODE()
		);

		if (execute(logic_literal_au0)) {
			return LEX_LITERAL;
		}


		
		

		FST identifier_au(
			word,
			3,
			NODE(156,
				//uppercase latin
				RELATION('A', 0), RELATION('A', 1), RELATION('A', 2),
				RELATION('B', 0), RELATION('B', 1), RELATION('B', 2),
				RELATION('C', 0), RELATION('C', 1), RELATION('C', 2),
				RELATION('D', 0), RELATION('D', 1), RELATION('D', 2),
				RELATION('E', 0), RELATION('E', 1), RELATION('E', 2),
				RELATION('F', 0), RELATION('F', 1), RELATION('F', 2),
				RELATION('G', 0), RELATION('G', 1), RELATION('G', 2),
				RELATION('H', 0), RELATION('H', 1), RELATION('H', 2),
				RELATION('I', 0), RELATION('I', 1), RELATION('I', 2),
				RELATION('J', 0), RELATION('J', 1), RELATION('J', 2),
				RELATION('K', 0), RELATION('K', 1), RELATION('K', 2),
				RELATION('L', 0), RELATION('L', 1), RELATION('L', 2),
				RELATION('M', 0), RELATION('M', 1), RELATION('M', 2),
				RELATION('N', 0), RELATION('N', 1), RELATION('N', 2),
				RELATION('O', 0), RELATION('O', 1), RELATION('O', 2),
				RELATION('P', 0), RELATION('P', 1), RELATION('P', 2),
				RELATION('Q', 0), RELATION('Q', 1), RELATION('Q', 2),
				RELATION('R', 0), RELATION('R', 1), RELATION('R', 2),
				RELATION('S', 0), RELATION('S', 1), RELATION('S', 2),
				RELATION('T', 0), RELATION('T', 1), RELATION('T', 2),
				RELATION('U', 0), RELATION('U', 1), RELATION('U', 2),
				RELATION('V', 0), RELATION('V', 1), RELATION('V', 2),
				RELATION('W', 0), RELATION('W', 1), RELATION('W', 2),
				RELATION('X', 0), RELATION('X', 1), RELATION('X', 2),
				RELATION('Y', 0), RELATION('Y', 1), RELATION('Y', 2),
				RELATION('Z', 0), RELATION('Z', 1), RELATION('Z', 2),
				//lowercase latin
				RELATION('a', 0), RELATION('a', 1), RELATION('a', 2),
				RELATION('b', 0), RELATION('b', 1), RELATION('b', 2),
				RELATION('c', 0), RELATION('c', 1), RELATION('c', 2),
				RELATION('d', 0), RELATION('d', 1), RELATION('d', 2),
				RELATION('e', 0), RELATION('e', 1), RELATION('e', 2),
				RELATION('f', 0), RELATION('f', 1), RELATION('f', 2),
				RELATION('g', 0), RELATION('g', 1), RELATION('g', 2),
				RELATION('h', 0), RELATION('h', 1), RELATION('h', 2),
				RELATION('i', 0), RELATION('i', 1), RELATION('i', 2),
				RELATION('j', 0), RELATION('j', 1), RELATION('j', 2),
				RELATION('k', 0), RELATION('k', 1), RELATION('k', 2),
				RELATION('l', 0), RELATION('l', 1), RELATION('l', 2),
				RELATION('m', 0), RELATION('m', 1), RELATION('m', 2),
				RELATION('n', 0), RELATION('n', 1), RELATION('n', 2),
				RELATION('o', 0), RELATION('o', 1), RELATION('o', 2),
				RELATION('p', 0), RELATION('p', 1), RELATION('p', 2),
				RELATION('q', 0), RELATION('q', 1), RELATION('q', 2),
				RELATION('r', 0), RELATION('r', 1), RELATION('r', 2),
				RELATION('s', 0), RELATION('s', 1), RELATION('s', 2),
				RELATION('t', 0), RELATION('t', 1), RELATION('t', 2),
				RELATION('u', 0), RELATION('u', 1), RELATION('u', 2),
				RELATION('v', 0), RELATION('v', 1), RELATION('v', 2),
				RELATION('w', 0), RELATION('w', 1), RELATION('w', 2),
				RELATION('x', 0), RELATION('x', 1), RELATION('x', 2),
				RELATION('y', 0), RELATION('y', 1), RELATION('y', 2),
				RELATION('z', 0), RELATION('z', 1), RELATION('z', 2),
				//special
				RELATION('_', 0), RELATION('_', 1)
			),
			NODE(126,
				RELATION('0', 1), RELATION('0', 2),
				RELATION('1', 1), RELATION('1', 2),
				RELATION('2', 1), RELATION('2', 2),
				RELATION('3', 1), RELATION('3', 2),
				RELATION('4', 1), RELATION('4', 2),
				RELATION('5', 1), RELATION('5', 2),
				RELATION('6', 1), RELATION('6', 2),
				RELATION('7', 1), RELATION('7', 2),
				RELATION('8', 1), RELATION('8', 2),
				RELATION('9', 1), RELATION('9', 2),

				RELATION('_', 1), RELATION('_', 2),
				//uppercase latin
				RELATION('A', 1), RELATION('A', 2),
				RELATION('B', 1), RELATION('B', 2),
				RELATION('C', 1), RELATION('C', 2),
				RELATION('D', 1), RELATION('D', 2),
				RELATION('E', 1), RELATION('E', 2),
				RELATION('F', 1), RELATION('F', 2),
				RELATION('G', 1), RELATION('G', 2),
				RELATION('H', 1), RELATION('H', 2),
				RELATION('I', 1), RELATION('I', 2),
				RELATION('J', 1), RELATION('J', 2),
				RELATION('K', 1), RELATION('K', 2),
				RELATION('L', 1), RELATION('L', 2),
				RELATION('M', 1), RELATION('M', 2),
				RELATION('N', 1), RELATION('N', 2),
				RELATION('O', 1), RELATION('O', 2),
				RELATION('P', 1), RELATION('P', 2),
				RELATION('Q', 1), RELATION('Q', 2),
				RELATION('R', 1), RELATION('R', 2),
				RELATION('S', 1), RELATION('S', 2),
				RELATION('T', 1), RELATION('T', 2),
				RELATION('U', 1), RELATION('U', 2),
				RELATION('V', 1), RELATION('V', 2),
				RELATION('W', 1), RELATION('W', 2),
				RELATION('X', 1), RELATION('X', 2),
				RELATION('Y', 1), RELATION('Y', 2),
				RELATION('Z', 1), RELATION('Z', 2),
				//lowercase latin
				RELATION('a', 1), RELATION('a', 2),
				RELATION('b', 1), RELATION('b', 2),
				RELATION('c', 1), RELATION('c', 2),
				RELATION('d', 1), RELATION('d', 2),
				RELATION('e', 1), RELATION('e', 2),
				RELATION('f', 1), RELATION('f', 2),
				RELATION('g', 1), RELATION('g', 2),
				RELATION('h', 1), RELATION('h', 2),
				RELATION('i', 1), RELATION('i', 2),
				RELATION('j', 1), RELATION('j', 2),
				RELATION('k', 1), RELATION('k', 2),
				RELATION('l', 1), RELATION('l', 2),
				RELATION('m', 1), RELATION('m', 2),
				RELATION('n', 1), RELATION('n', 2),
				RELATION('o', 1), RELATION('o', 2),
				RELATION('p', 1), RELATION('p', 2),
				RELATION('q', 1), RELATION('q', 2),
				RELATION('r', 1), RELATION('r', 2),
				RELATION('s', 1), RELATION('s', 2),
				RELATION('t', 1), RELATION('t', 2),
				RELATION('u', 1), RELATION('u', 2),
				RELATION('v', 1), RELATION('v', 2),
				RELATION('w', 1), RELATION('w', 2),
				RELATION('x', 1), RELATION('x', 2),
				RELATION('y', 1), RELATION('y', 2),
				RELATION('z', 1), RELATION('z', 2)

			),
			NODE()
		);


		if (execute(identifier_au)) {
			return LEX_ID;
		}

		return LEX_UNDEF;
	}

	bool check_unt(unsigned char* word) {
		FST unt_au(
			word,
			4,
			NODE(1,RELATION('u',1)),
			NODE(1,RELATION('n',2)),
			NODE(1,RELATION('t',3)),
			NODE()
		);
		if (execute(unt_au)) {
			return true;
		}
		return false;
	}

	bool check_logic(unsigned char* word) {
		FST logic_au(
			word,
			5,
			NODE(1, RELATION('b', 1)),
			NODE(1, RELATION('o', 2)),
			NODE(1, RELATION('o', 3)),
			NODE(1, RELATION('l', 4)),
			NODE()
		);

		if (execute(logic_au)) {
			return true;
		}
		return false;
	}

	bool check_sym(unsigned char* word) {
		FST sym_check(
			word,
			4,
			NODE(1, RELATION('s', 1)),
			NODE(1, RELATION('y', 2)),
			NODE(1, RELATION('m', 3)),
			NODE()
		);

		if (execute(sym_check)) {
			return true;
		}
		return false;
	}

	bool check_logic_literals(unsigned char* word) {
		FST logic_lit_0_au(
			word,
			6,
			NODE(1, RELATION('F', 1)),
			NODE(1, RELATION('a', 2)),
			NODE(1, RELATION('l', 3)),
			NODE(1, RELATION('s', 4)),
			NODE(1, RELATION('e', 5)),
			NODE()
		);

		if (execute(logic_lit_0_au)) {
			return true;
		}

		FST logic_lit_1_au(
			word,
			5,
			NODE(1, RELATION('T', 1)),
			NODE(1, RELATION('r', 2)),
			NODE(1, RELATION('u', 3)),
			NODE(1, RELATION('e', 4)),
			NODE()
		);

		if (execute(logic_lit_1_au)) {
			return true;
		}

		return false;
	}

	void GetLexem(LT::LexTable& lextable, IT::IDTable& idtable, In::IN in) {
		stack<char*>scope;
		const char* Literal = "Literal";
		int count_lines = 0;
		int count_literals = 0;
		for (int i = 0; i < in.words_size-1; i++) {
			LT::Entry NewLex;
			IT::Entry NewId;
			unsigned char* current_word = in.words[i];
			if (current_word[0] == '\0' || current_word[0] == ' ') {
				continue;
			}
			if (current_word[0] == '|') {
				count_lines++;
			}
			char lexem = FiniteAutomats(current_word);

			/*if (lexem == LEX_ID && scope.empty()) {
				throw ERROR_THROW(600);
			}*/

			if (lexem == LEX_SKIP) {
				continue;
			}
			/*if (lexem == LEX_UNDEF) {
				throw ERROR_THROW(90);
			}*/
			NewLex.lexem = lexem;
			NewLex.src_str_num = count_lines;
			LT::AddToLexTable(lextable, NewLex);

			if (lexem == LEX_MAIN) {
				scope.push((char*)"Main");
			}
			int gap_front = 1;
			if (lexem == LEX_DATATYPE) {
				NewId.first_line_ID = count_lines;
				bool done = false;
				while (true) {
					if (FiniteAutomats(in.words[i + gap_front]) == LEX_FUNCTION) {
						//scope.push((char*)in.words[i + gap_front]);
						NewId.IDType = IT::F;
						if (check_unt(in.words[i])) {
							NewId.IDDataType = IT::UNT;
						}
						else if (check_logic(in.words[i])) {
							NewId.IDDataType = IT::BOO;
						}
						
						else {
							NewId.IDDataType = IT::SYM;
						}
						NewId.scope = (char*)"NULL";
						break;
					}
					else if (FiniteAutomats(in.words[i + gap_front]) == LEX_ID) {
						if (scope.empty()) {
							throw ERROR_THROW(600);
							
						}
						NewId.IDType = IT::V;
						for (int c = 1; c < 3; c++) {
							if (FiniteAutomats(in.words[i + gap_front + c]) == ',' || FiniteAutomats(in.words[i + gap_front + c]) == ')') {
								NewId.IDType = IT::P;
							}
						}
						NewId.id = (char*)in.words[i + gap_front];
						if (check_unt(in.words[i])) {
							NewId.IDDataType = IT::UNT;
						}
						else if (check_logic(in.words[i])) {
							NewId.IDDataType = IT::BOO;
						}
						
						else {
							NewId.IDDataType = IT::SYM;
						}
						//NewId.scope = scope.top();
						NewId.scope = scope.top();
						IT::AddToIDTable(idtable, NewId);
						done = true;
						break;
					}

					gap_front++;
				}
				int store_gap = gap_front;
				if (!done) {
					gap_front++;
					while (!done) {

						if (FiniteAutomats(in.words[i + gap_front]) == LEX_ID) {
							NewId.id = (char*)in.words[i + gap_front];
							IT::AddToIDTable(idtable, NewId);
							scope.push(NewId.id);
							done = true;
						}
						gap_front++;
					}
				}
				continue;

			}

			else if (lexem == LEX_LITERAL) {
				if (scope.empty()) {
					throw ERROR_THROW(600);
				}
				//forms literal name for ID table
				char* tmp_literal_name = new char[STR_MAXSIZE];
				int g = 0;
				while (Literal[g] != '\0') {
					tmp_literal_name[g] = Literal[g];
					g++;
				}

				tmp_literal_name[g++] = '_';

				int tmp_lit_number = count_literals;
				if (tmp_lit_number == 0) {
					tmp_literal_name[g++] = '0';
				}

				else {
					char* tmp_number = new char[10];
					int h = 0;
					while (tmp_lit_number > 0) {
						tmp_number[h++] = tmp_lit_number % 10 + '0';
						tmp_lit_number /= 10;
					}
					tmp_number[h] = '\0';
					h--;
					while (h >= 0) {

						tmp_literal_name[g++] = tmp_number[h--];
					}
					delete[]tmp_number;
				}

				tmp_literal_name[g] = '\0';
				//end of literal name forming

				//if a symbol literal found(by quotation marks)
				if (check_sym(in.words[i])) {
					NewId.first_line_ID = count_lines;
					NewId.id = tmp_literal_name;
					NewId.IDDataType = IT::SYM;
					NewId.IDType = IT::L;
					NewId.value.sym_val = (char)in.words[i][1];
					
				}
				else if (check_logic_literals(in.words[i])) {
					
					NewId.first_line_ID = count_lines;
					NewId.id = tmp_literal_name;
					NewId.IDDataType = IT::BOO;
					NewId.IDType = IT::L;
					NewId.value.bool_val = (char*)in.words[i];
				}
				
				
				else{
					//NewId.scope = (char*)"null";
					NewId.first_line_ID = count_lines;
					NewId.id = tmp_literal_name;
					NewId.IDDataType = IT::UNT;
					NewId.IDType = IT::L;
					NewId.value.unt_val = (char*)in.words[i];
				}

				//if number literal found(every literal except symbol once)
				
				//checking if there were no such literals
				//and if not -  adding it to id table
				if (!(IT::CheckLiteralPresense(idtable, NewId))) {
					NewId.scope = scope.top();
					IT::AddToIDTable(idtable, NewId);
					idtable.lits[idtable.literal_count++] = NewId;
					count_literals++;
				}

			}
		}

		for (short i = 0; i < scope.size(); i++) {
			scope.pop();
		}
	}
}