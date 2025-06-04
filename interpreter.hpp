#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include "token.hpp"
using namespace std;

int pc = 0;
stack<int> s;
map<string, int> vars;

bool is_number(const std::string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(c) && c != '-' && c != '+') return false;
    }
    try {
        std::stoi(s);
        return true;
    } catch (...) {
        return false;
    }
}

void interpret(vector<pair<token_type, string>> tokens) {
    while(pc < tokens.size()){
        switch(tokens[pc].first) {
            case PUSH: {
                s.push(stoi(tokens[pc].second));
                break;
            }
            case POP: {
                s.pop();
                break;
            }
            case ADD: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                s.push(top + bottom);
                break;
            }
            case SUB: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                s.push(top - bottom);
                break;
            }
            case MUL: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                s.push(top * bottom);
                break;
            }
            case DIV: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                s.push(top / bottom);
                break;
            }
            case MOD: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                s.push(top % bottom);
                break;
            }
            case NEG: {
                int top = s.top(); s.pop();
                s.push(top * -1);
                break;
            }
            case STORE: {
                int top = s.top(); s.pop();
                vars.insert({tokens[pc].second, top});
                break;
            }
            case LOAD: {
                if(vars[tokens[pc].second]) s.push(vars[tokens[pc].second]);
                else {
                    // TODO
                }
                break;
            }
            case JMP: {
                if (is_number(tokens[pc].second)) {
                    pc = std::stoi(tokens[pc].second);
                } else {
                    pc = labels[tokens[pc].second];
                }
                // Gambiarra
                pc--;
                break;
            }
            case JZ: {
                int top = s.top(); s.pop();
                if(top == 0) {
                    if (is_number(tokens[pc].second)) {
                        pc = std::stoi(tokens[pc].second);
                    } else {
                        pc = labels[tokens[pc].second];
                    }
                    // Gambiarra
                    pc--;
                }
                break;
            }
            case JNZ: {
                int top = s.top(); s.pop();
                if(top != 0) {
                    if (is_number(tokens[pc].second)) {
                        pc = std::stoi(tokens[pc].second);
                    } else {
                        pc = labels[tokens[pc].second];
                    }
                    // Gambiarra
                    pc--;
                }
                break;
            }
            case HALT: {
                // ???
                break;
            }
            case EQ: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                if(top == bottom) s.push(1);
                else s.push(0);
                break;
            }
            case NEQ: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                if(top != bottom) s.push(1);
                else s.push(0);
                break;
            }
            case LT: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                if(bottom < top) s.push(1);
                else s.push(0);
                break;
            }
            case GT: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                if(bottom > top) s.push(1);
                else s.push(0);
                break;
            }
            case LE: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                if(bottom <= top) s.push(1);
                else s.push(0);
                break;
            }
            case GE: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                if(bottom >= top) s.push(1);
                else s.push(0);
                break;
            }
            case CALL: {
                // TODO
                break;
            }
            case RET: {
                // TODO
                break;
            }
            case READ: {
                // TODO
                break;
            }
            case PRINT: {
                int val = s.top();
                cout << val << "\n";
                break;
            }
            default: {
                break;
            }
        }
        pc++;
    }
}



#endif