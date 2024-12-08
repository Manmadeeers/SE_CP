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

		char special[] = { '(',')','{','}',';',',' };
		char signs[] = { '+','-','/','*' };
		if ((char*)word == (char*)STR_END) {
			return STR_END;
		}
		const int spec_size = 11;
		const int sign_size = 4;

		for (int j = 0; j < spec_size; j++) {
			if (word[0] == special[j]) {
				return special[j];
			}
		}

		for (int k = 0; k < sign_size; k++) {
			if (word[0] == signs[k]) {
				return LEX_MATH;
			}
		}
		if (word[0] == '=') {
			return LEX_EQUALS;
		}

		FST integer_au(
			word,
			8,
			NODE(1, RELATION('i', 1)),
			NODE(1, RELATION('n', 2)),
			NODE(1, RELATION('t', 3)),
			NODE(1, RELATION('e', 4)),
			NODE(1, RELATION('g', 5)),
			NODE(1, RELATION('e', 6)),
			NODE(1, RELATION('r', 7)),
			NODE()
		);
		if (execute(integer_au)) {
			return LEX_DATATYPE;
		}

		FST string_au(
			word,
			7,
			NODE(1, RELATION('s', 1)),
			NODE(1, RELATION('t', 2)),
			NODE(1, RELATION('r', 3)),
			NODE(1, RELATION('i', 4)),
			NODE(1, RELATION('n', 5)),
			NODE(1, RELATION('g', 6)),
			NODE()
		);
		if (execute(string_au)) {
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

		FST declare_au(
			word,
			8,
			NODE(1, RELATION('d', 1)),
			NODE(1, RELATION('e', 2)),
			NODE(1, RELATION('c', 3)),
			NODE(1, RELATION('l', 4)),
			NODE(1, RELATION('a', 5)),
			NODE(1, RELATION('r', 6)),
			NODE(1, RELATION('e', 7)),
			NODE()
		);

		if (execute(declare_au)) {
			return LEX_DECLARE;
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

		FST print_au(
			word,
			6,
			NODE(1, RELATION('p', 1)),
			NODE(1, RELATION('r', 2)),
			NODE(1, RELATION('i', 3)),
			NODE(1, RELATION('n', 4)),
			NODE(1, RELATION('t', 5)),
			NODE()
		);

		if (execute(print_au)) {
			return LEX_PRINT;
		}

		FST main_au(
			word,
			5,
			NODE(1, RELATION('m', 1)),
			NODE(1, RELATION('a', 2)),
			NODE(1, RELATION('i', 3)),
			NODE(1, RELATION('n', 4)),
			NODE()
		);

		if (execute(main_au)) {
			return LEX_MAIN;
		}

		FST integer_literal_au(
			word,
			2,
			NODE(20, RELATION('0', 0), RELATION('0', 1), RELATION('1', 0), RELATION('1', 1), RELATION('2', 0),
				RELATION('2', 1), RELATION('3', 0), RELATION('3', 1), RELATION('4', 0), RELATION('4', 1),
				RELATION('5', 0), RELATION('5', 1), RELATION('6', 0), RELATION('6', 1), RELATION('7', 0),
				RELATION('7', 1), RELATION('8', 0), RELATION('8', 1), RELATION('9', 0), RELATION('9', 1)),
			NODE()
		);
		if (execute(integer_literal_au)) {
			return LEX_LITERAL;
		}


		FST string_literal_au(
			word,
			4,
			NODE(1, RELATION('\'', 1)),
			NODE(258,
				RELATION('A', 1), RELATION('A', 2), RELATION('B', 1), RELATION('B', 2),
				RELATION('C', 1), RELATION('C', 2), RELATION('D', 1), RELATION('D', 2),
				RELATION('E', 1), RELATION('E', 2), RELATION('F', 1), RELATION('F', 2),
				RELATION('G', 1), RELATION('G', 2), RELATION('H', 1), RELATION('H', 2),
				RELATION('I', 1), RELATION('I', 2), RELATION('J', 1), RELATION('J', 2),
				RELATION('K', 1), RELATION('K', 2), RELATION('L', 1), RELATION('L', 2),
				RELATION('M', 1), RELATION('M', 2), RELATION('N', 1), RELATION('N', 2),
				RELATION('O', 1), RELATION('O', 2), RELATION('P', 1), RELATION('P', 2),
				RELATION('Q', 1), RELATION('Q', 2), RELATION('R', 1), RELATION('R', 2),
				RELATION('S', 1), RELATION('S', 2), RELATION('T', 1), RELATION('T', 2),
				RELATION('U', 1), RELATION('U', 2), RELATION('V', 1), RELATION('V', 2),
				RELATION('W', 1), RELATION('W', 2), RELATION('X', 1), RELATION('X', 2),
				RELATION('Y', 1), RELATION('Y', 2), RELATION('Z', 1), RELATION('Z', 2),
				RELATION('a', 1), RELATION('a', 2), RELATION('b', 1), RELATION('b', 2),
				RELATION('c', 1), RELATION('c', 2), RELATION('d', 1), RELATION('d', 2),
				RELATION('e', 1), RELATION('e', 2), RELATION('f', 1), RELATION('f', 2),
				RELATION('g', 1), RELATION('g', 2), RELATION('h', 1), RELATION('h', 2),
				RELATION('i', 1), RELATION('i', 2), RELATION('j', 1), RELATION('j', 2),
				RELATION('k', 1), RELATION('k', 2), RELATION('l', 1), RELATION('l', 2),
				RELATION('m', 1), RELATION('m', 2), RELATION('n', 1), RELATION('n', 2),
				RELATION('o', 1), RELATION('o', 2), RELATION('p', 1), RELATION('p', 2),
				RELATION('q', 1), RELATION('q', 2), RELATION('r', 1), RELATION('r', 2),
				RELATION('s', 1), RELATION('s', 2), RELATION('t', 1), RELATION('t', 2),
				RELATION('u', 1), RELATION('u', 2), RELATION('v', 1), RELATION('v', 2),
				RELATION('w', 1), RELATION('w', 2), RELATION('x', 1), RELATION('x', 2),
				RELATION('y', 1), RELATION('y', 2), RELATION('z', 1), RELATION('z', 2),
				RELATION('À', 1), RELATION('À', 2), RELATION('Á', 1), RELATION('Á', 2),
				RELATION('Â', 1), RELATION('Â', 2), RELATION('Ã', 1), RELATION('Ã', 2),
				RELATION('Ä', 1), RELATION('Ä', 2), RELATION('Å', 1), RELATION('Å', 2),
				RELATION('¨', 1), RELATION('¨', 2), RELATION('Æ', 1), RELATION('Æ', 2),
				RELATION('Ç', 1), RELATION('Ç', 2), RELATION('È', 1), RELATION('È', 2),
				RELATION('É', 1), RELATION('É', 2), RELATION('Ê', 1), RELATION('Ê', 2),
				RELATION('Ë', 1), RELATION('Ë', 2), RELATION('Ì', 1), RELATION('Ì', 2),
				RELATION('Í', 1), RELATION('Í', 2), RELATION('Î', 1), RELATION('Î', 2),
				RELATION('Ï', 1), RELATION('Ï', 2), RELATION('Ð', 1), RELATION('Ð', 2),
				RELATION('Ñ', 1), RELATION('Ñ', 2), RELATION('Ò', 1), RELATION('Ò', 2),
				RELATION('Ó', 1), RELATION('Ó', 2), RELATION('Ô', 1), RELATION('Ô', 2),
				RELATION('Õ', 1), RELATION('Õ', 2), RELATION('Ö', 1), RELATION('Ö', 2),
				RELATION('×', 1), RELATION('×', 2), RELATION('Ø', 1), RELATION('Ø', 2),
				RELATION('Ù', 1), RELATION('Ù', 2), RELATION('Ú', 1), RELATION('Ú', 2),
				RELATION('Û', 1), RELATION('Û', 2), RELATION('Ü', 1), RELATION('Ü', 2),
				RELATION('Ý', 1), RELATION('Ý', 2), RELATION('Þ', 1), RELATION('Þ', 2),
				RELATION('ß', 1), RELATION('ß', 2), RELATION('à', 1), RELATION('à', 2),
				RELATION('á', 1), RELATION('á', 2), RELATION('â', 1), RELATION('â', 2),
				RELATION('ã', 1), RELATION('ã', 2), RELATION('ä', 1), RELATION('ä', 2),
				RELATION('å', 1), RELATION('å', 2), RELATION('¸', 1), RELATION('¸', 2),
				RELATION('æ', 1), RELATION('æ', 2), RELATION('ç', 1), RELATION('ç', 2),
				RELATION('è', 1), RELATION('è', 2), RELATION('é', 1), RELATION('é', 2),
				RELATION('ê', 1), RELATION('ê', 2), RELATION('ë', 1), RELATION('ë', 2),
				RELATION('ì', 1), RELATION('ì', 2), RELATION('í', 1), RELATION('í', 2),
				RELATION('î', 1), RELATION('î', 2), RELATION('ï', 1), RELATION('ï', 2),
				RELATION('ð', 1), RELATION('ð', 2), RELATION('ñ', 1), RELATION('ñ', 2),
				RELATION('ò', 1), RELATION('ò', 2), RELATION('ó', 1), RELATION('ó', 2),
				RELATION('ô', 1), RELATION('ô', 2), RELATION('õ', 1), RELATION('õ', 2),
				RELATION('ö', 1), RELATION('ö', 2), RELATION('÷', 1), RELATION('÷', 2),
				RELATION('ø', 1), RELATION('ø', 2), RELATION('ù', 1), RELATION('ù', 2),
				RELATION('ú', 1), RELATION('ú', 2), RELATION('û', 1), RELATION('û', 2),
				RELATION('ü', 1), RELATION('ü', 2), RELATION('ý', 1), RELATION('ý', 2),
				RELATION('þ', 1), RELATION('þ', 2), RELATION('ÿ', 1), RELATION('ÿ', 2),
				RELATION('0', 1), RELATION('0', 2), RELATION('1', 1), RELATION('1', 2),
				RELATION('2', 1), RELATION('2', 2), RELATION('3', 1), RELATION('3', 2),
				RELATION('4', 1), RELATION('4', 2), RELATION('5', 1), RELATION('5', 2),
				RELATION('6', 1), RELATION('6', 2), RELATION('7', 1), RELATION('7', 2),
				RELATION('8', 1), RELATION('8', 2), RELATION('9', 1), RELATION('9', 2),
				RELATION(' ', 1), RELATION(' ', 2)),
			NODE(1, RELATION('\'', 3)),
			NODE()
		);
		if (execute(string_literal_au)) {
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

	bool check_int(unsigned char* word) {
		FST integer_au(
			word,
			8,
			NODE(1, RELATION('i', 1)),
			NODE(1, RELATION('n', 2)),
			NODE(1, RELATION('t', 3)),
			NODE(1, RELATION('e', 4)),
			NODE(1, RELATION('g', 5)),
			NODE(1, RELATION('e', 6)),
			NODE(1, RELATION('r', 7)),
			NODE()
		);
		if (execute(integer_au)) {
			return true;
		}
		return false;
	}

	void GetLexem(LT::LexTable& lextable, IT::IDTable& idtable, In::IN in) {
		const char* Literal = "Literal";
		int count_lines = 0;
		int count_literals = 0;
		for (int i = 0; i < in.words_size; i++) {
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

			if (lexem == LEX_UNDEF) {
				continue;
			}
			NewLex.lexem = lexem;
			NewLex.src_str_num = count_lines;
			LT::AddToLexTable(lextable, NewLex);


			int gap_front = 1;
			if (lexem == LEX_DATATYPE) {
				NewId.first_line_ID = count_lines;
				bool done = false;
				while (true) {
					if (FiniteAutomats(in.words[i + gap_front]) == LEX_FUNCTION) {
						NewId.IDType = IT::F;
						if (check_int(in.words[i])) {
							NewId.IDDataType = IT::INT;
						}
						else {
							NewId.IDDataType = IT::STR;
						}
						break;
					}
					else if (FiniteAutomats(in.words[i + gap_front]) == LEX_ID) {
						NewId.IDType = IT::V;
						for (int c = 1; c < 3; c++) {
							if (FiniteAutomats(in.words[i + gap_front + c]) == ',' || FiniteAutomats(in.words[i + gap_front + c]) == ')') {
								NewId.IDType = IT::P;
							}
						}
						NewId.id = (char*)in.words[i + gap_front];
						if (check_int(in.words[i])) {
							NewId.IDDataType = IT::INT;
						}
						else {
							NewId.IDDataType = IT::STR;
						}
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
							done = true;
						}
						gap_front++;
					}
				}
				continue;

			}

			else if (lexem == LEX_LITERAL) {

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

				if (in.words[i][0] == '\'') {
					NewId.first_line_ID = count_lines;
					NewId.id = tmp_literal_name;
					NewId.IDDataType = IT::STR;
					NewId.IDType = IT::L;
					NewId.value.vstr.str = (char*)in.words[i];
					short length = 1;
					while (in.words[i][length] != '\'') {
						length++;
					}
					NewId.value.vstr.len = length;
				}
				else {
					NewId.first_line_ID = count_lines;
					NewId.id = tmp_literal_name;
					NewId.IDDataType = IT::INT;
					NewId.IDType = IT::L;
					NewId.value.vint = stoi((char*)in.words[i]);
				}
				if (IT::CheckLiteralPresense(idtable, NewId) == false) {
					IT::AddToIDTable(idtable, NewId);
					count_literals++;
				}

			}
		}
	}
}