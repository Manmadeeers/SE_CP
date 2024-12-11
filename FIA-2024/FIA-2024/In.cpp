#include "stdafx.h"

namespace In {
	IN getin(wchar_t infile[])
	{
		IN in_to_return;

		in_to_return.size = 0;//to count all the symbols
		in_to_return.lines = 1;//to count all the lines in a file knowing we have at least 1
		in_to_return.ignore = 0;
		int column = 1;
		unsigned char* text = new unsigned char[IN_MAX_LEN_TEXT];


		ifstream from_file(infile);//open file to read 

		if (!from_file.is_open()) {
			throw ERROR_THROW(110);
		}


		while (in_to_return.size <= IN_MAX_LEN_TEXT) {

			if (in_to_return.size == IN_MAX_LEN_TEXT - 1) {
				throw ERROR_THROW(105);
			}
			if (from_file.eof()) {//if the end of the file is met
				text[in_to_return.size] = '\0';
				break;
			}
			char c;
			from_file.get(c);
			unsigned char current_symbol = c;
			char next;

			switch (in_to_return.code[current_symbol]) {
			case IN::T:
				text[in_to_return.size] = current_symbol;

				in_to_return.size++;
				column++;
				break;
			case IN::L:
				if (text[in_to_return.size] == ';' && text[in_to_return.size + 1] == ';') {
					throw ERROR_THROW(98);
				}
				text[in_to_return.size] = current_symbol;
				column++;
				in_to_return.size++;
				break;
			case IN::Q:
				text[in_to_return.size] = current_symbol;
				column++;
				in_to_return.size++;
				break;
			case IN::I:
				in_to_return.ignore++;
				column++;
				break;
			case IN::F:
				text[in_to_return.size] = '\0';

				//returns errors structure with all the symbols untill an error has occured
				throw ERROR_THROW_IN(111, in_to_return.lines, column, text);

				break;
			case IN::S:
				//if a space symbol is met checks if the next symbol is a space or a separator and if true ignored the next space and
				// moves forward to the next symbol
				if (in_to_return.code[from_file.peek()] == IN::S || text[in_to_return.size - 1] == '|' || in_to_return.size == 0) {
					in_to_return.ignore++;
					column++;
				}
				else {//if it's just a single space and it's not at the very start of the line adds this symbol
					//to the text fiels of the returned structure
					text[in_to_return.size] = current_symbol;
					//count_words++;
					in_to_return.size++;

				}
				break;
			default:
				text[in_to_return.size] = in_to_return.code[current_symbol];
				in_to_return.size++;


				column++;
				break;
			}
			if (current_symbol == IN_CODE_ENDL) {//if the current symbol is the end of the line
				in_to_return.lines++;
				column = 1;//renew the variable counting columns
			}
		}


		//transfer a string into an array of single separated words
		in_to_return.text = text;


		unsigned char** words = new unsigned char* [LT_MAXSIZE];
		for (int i = 0; i < LT_MAXSIZE; i++) {
			words[i] = new unsigned char[MAX_WORD_LENGTH];
		}

		int count_words = 0;
		int count_symbols = 0;

		for (int i = 0; i < in_to_return.size; i++) {
			unsigned char current_symbol = in_to_return.text[i];

			switch (in_to_return.code[current_symbol]) {




			case IN::L:
				words[count_words][count_symbols++] = '\0';
				count_words++;
				count_symbols = 0;
				words[count_words][count_symbols++] = current_symbol;

				if (in_to_return.text[i + 1] == '='&&current_symbol=='=') {
					words[count_words][count_symbols++] = in_to_return.text[i + 1];
					i += 2;
				}

				if (current_symbol == '+' && in_to_return.text[i + 1]) {
					words[count_words][count_symbols++] = in_to_return.text[i + 1];
					i += 2;
				}
				if (current_symbol == ';' && in_to_return.text[i + 1] == ';') {
					//throw ERROR_THROW(98);
					i += 2;
				}
				words[count_words][count_symbols] = '\0';
				count_symbols = 0;
				count_words++;
				break;
			case IN::S:
				words[count_words][count_symbols] = '\0';
				count_words++;
				count_symbols = 0;
				break;

			case IN::Q:
				words[count_words][count_symbols++] = current_symbol;
				i++;
				for (; i < in_to_return.size; i++) {
					words[count_words][count_symbols++] = in_to_return.text[i];
					if (in_to_return.code[in_to_return.text[i]] == IN::Q) {
						break;
					}
				}
				words[count_words][count_symbols] = '\0';
				count_words++;
				count_symbols = 0;
				break;

			default:

				if (current_symbol == '|') {
					words[count_words][count_symbols] = '\0';
					count_words++;
					count_symbols = 0;
					words[count_words][0] = current_symbol;
					words[count_words][1] = '\0';
					count_words++;
				}

				else {
					words[count_words][count_symbols++] = current_symbol;
				}


				break;
			}


		}
		in_to_return.words = words;
		in_to_return.words_size = count_words;

		return in_to_return;
	}

	void deleteIN(IN in) {
		for (int i = 0; i < in.words_size; i++) {
			delete[]in.words[i];
		}
		delete[]in.words;
		delete[]in.text;
		delete[]in.code;
		in.size = 0;
		in.ignore = 0;
		in.lines = 0;
		in.words_size = 0;

	}
}