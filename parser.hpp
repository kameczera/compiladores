#ifndef PARSER_HPP
#define PARSER_HPP

#include "expr.hpp"
#include <iostream>
#include <vector>
#include "token.hpp"
#include "expr.hpp"
#include "compiler.hpp"

class ast {
    std::vector<expr*> statements;
};

ast* create_ast(vector<pair<token_type, string>> tokens){
    int i = 0;
    stack<expr*> s;
    std::vector<expr*> statements;
    while(i < tokens.size()) {
        token_type tt = tokens[i].first;
        const std::string& text = tokens[i].second;
        switch(tt) {
            case PUSH: {
                value* e = new value(text);
                push* p = new push(e);
                s.push(p);
                break;
            }
            case POP: {
                pop* e = new pop(s.top()); s.pop();
                statements.push_back(e);
                break;
            }
            case ADD: case SUB: case MUL: case DIV: case MOD: case NEG: case EQ: case NEQ: case LT: case GT: case LE: case GE: {
                expr* top = s.top(); s.pop();
                expr* bottom = s.top(); s.pop();
                binary* e = new binary(tt, top, bottom);
                s.push(e);
                break;
            }
            case STORE: {
                expr* top = s.top(); s.pop();
                store* e = new store(top);
                statements.push_back(e);
                break;
            }
            case LOAD: {
                value* e = new value(vars[text]);
                push* p = new push(e);
                break;
            }
            case JMP: {
                int jmp_idx;
                if (is_number(text)) {
                    jmp_idx = std::stoi(text);
                } else {
                    jmp_idx = labels[text];
                }
                // Gambiarra
                jmp_idx--;
                jz* e = new jz(jmp_idx);
                statements.push_back(e);
                break;
            }
            case JZ: {
                int jmp_idx;
                if (is_number(text)) {
                    jmp_idx = std::stoi(text);
                } else {
                    jmp_idx = labels[text];
                }
                // Gambiarra
                jmp_idx--;
                jz* e = new jz(jmp_idx);
                statements.push_back(e);
                break;
            }
            case JNZ: {
                int jmp_idx;
                if (is_number(text)) {
                    jmp_idx = std::stoi(text);
                } else {
                    jmp_idx = labels[text];
                }
                // Gambiarra
                jmp_idx--;
                jz* e = new jz(jmp_idx);
                statements.push_back(e);
                break;
            }
            case LABEL: {
                label* e = new label();
                statements.push_back(e);
            }
            default:
                break;
        }
        i++;
    }

    // TODO: conectar nos
}


#endif