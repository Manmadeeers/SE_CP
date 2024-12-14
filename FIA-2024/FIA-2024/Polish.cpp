#include "stdafx.h"

namespace PL {

    void findN(LT::LexTable& lextable, IT::IDTable& idtable) {
        int pos = 0;
        for (int i = 0; i <= lextable.size; i++) {
            if (lextable.table[i].lexem == '=') {
                pos = i + 1;
                PolishNotation(pos, lextable, idtable);
            }
        }
    }

    bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IDTable& idtable) {

        std::map<char, int> precedence = { {'+', 1},{'-', 1}, {'*', 2}, {'/', 2}, {'^', 2} };
        std::set<char> left_associative = { '+', '-', '/', '*' };

        LT::LexTable expression = LT::Create(LEN);
        int length = 0;

        for (int i = lextable_pos; lextable.table[i].lexem != ';'; i++) {
            LT::AddToLexTable(expression, lextable.table[i]);
            length++;
        }


        std::stack<LT::Entry> stack;
        LT::LexTable output = LT::Create(LEN);



        for (int i = 0; i <= length; i++) {
            if (std::isalnum(expression.table[i].lexem)) {
                if (idtable.table[expression.table[i].src_str_num].IDType == IT::F) {
                    stack.push(expression.table[i]);
                }
                else {
                    LT::AddToLexTable(output, expression.table[i]);
                }
            }
            else if (expression.table[i].lexem == '(') {
                stack.push(expression.table[i]);
            }
            else if (expression.table[i].lexem == ')') {
                while (!stack.empty() && stack.top().lexem != '(') {
                    LT::AddToLexTable(output, stack.top());
                    stack.pop();
                }
                if (!stack.empty() && stack.top().lexem == '(') {
                    stack.pop();
                }
            }
            else if (precedence.find(expression.table[i].lexem) != precedence.end()) {
                LT::Entry op = expression.table[i];
                while (!stack.empty() && stack.top().lexem != '(' &&
                    (precedence[stack.top().lexem] > precedence[op.lexem] ||
                        (precedence[stack.top().lexem] == precedence[op.lexem] && left_associative.count(op.lexem)))) {
                    LT::AddToLexTable(output, stack.top());
                    stack.pop();
                }
                stack.push(op);
            }
        }


        while (!stack.empty()) {
            LT::AddToLexTable(output, stack.top());
            stack.pop();
        }



        for (int i = output.size; i < length; i++) {
            LT::AddToLexTable(output, { '$', LT::GetEntry(output, output.size - 1).src_str_num });
        }

        for (int i = 0; i < length; i++) {
            lextable.table[i + lextable_pos] = output.table[i];
        }
        return true;
    }
}