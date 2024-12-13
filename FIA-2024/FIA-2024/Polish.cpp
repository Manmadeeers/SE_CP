#include "stdafx.h"

namespace PL {

	bool isSuitable(char* lex_string) {
		int iterator = 0;
		while (lex_string[iterator] != '\0') {
			char current = lex_string[iterator];
			if (current == LEX_EQUALS||current=='('||current=='[') {
				return true;
			}
			iterator++;
		}
		return false;
	}

	bool isOperator(char c) {
		return c == LEX_PLUS || c == LEX_MINUS || c == LEX_MULTIPLY || c == LEX_DEVIDE;
	}

	bool isOperand(char c) {
		return isdigit(c) || isalpha(c);
	}

	bool prefixToPolish(std::string lex_string) {
		std::map<char, int>priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3} };
		std::set<char> left_associative = { '+', '-', '*', '/' };
		stack<char>operStack;
		std::string result;
		std::string expression;
		for (int i = 0; i < lex_string.size(); i++) {
			char c = lex_string[i];
			if (isOperand(c)) {
				result.push_back(c);
			}
			else if (c == LEX_LEFTSC) {
				operStack.push(c);
			}
			else if (c == LEX_RIGHTSC) {
				while (!operStack.empty() && operStack.top() != LEX_LEFTSC) {
					result.push_back(operStack.top());
					operStack.pop();
				}
				if (!operStack.empty() && operStack.top() == LEX_LEFTSC) {
					operStack.pop();
				}
			}
			else if (priority.find(c) != priority.end()) {
				while (!operStack.empty() && operStack.top() != LEX_LEFTSC &&
					(priority[operStack.top()] > priority[c] || (priority[operStack.top()] == priority[c] && left_associative.count(c)))) 
				{
					result.push_back(operStack.top());
					operStack.pop();
				}
			}
			while (!operStack.empty()) {
				result.push_back(operStack.top());
				operStack.pop();
			}
		}
		

		cout << result << endl;
		return true;
	
	}



	void proceedPolishPerforming(LT::LexTable &lextable) {
		std::string current_line;
		int store_prev = lextable.table[0].src_str_num;
		for (int i = 0; i < lextable.size; ++i) {
			LT::Entry current = lextable.table[i];
			if (current.src_str_num != store_prev) {
				prefixToPolish(current_line);
				current_line.clear();
				store_prev = current.src_str_num;
				current_line += current.lexem;
			}
			else {
				current_line += current.lexem;
			}
		}

	}

}