#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include "token.hpp"
#include "compiler.hpp"

using namespace std;

int pc = 0;
stack<int> s;
map<string, int> vars;

void print_stack()
{
    if (s.empty()) return;
    int x = s.top();
    s.pop();
    print_stack();
    cout << x << " ";
    s.push(x);
}

void print_vars() {
    for (const auto& par : vars) {
        std::cout << "Chave: " << par.first << ", Valor: " << par.second << std::endl;
    }
}

void interpret(vector<pair<token_type, string>> tokens) {
    while(pc < tokens.size()){
        cout << "PC: " << pc+1 << ", Token: " << tokens[pc].first << ", Value: " << tokens[pc].second << " valor2: " << labels[tokens[pc].second] << "\n";
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
                s.push(bottom + top);
                break;
            }
            case SUB: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                s.push(bottom - top);
                break;
            }
            case MUL: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                s.push(bottom * top);
                break;
            }
            case DIV: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                s.push(bottom / top);
                break;
            }
            case MOD: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                s.push(bottom % top);
                break;
            }
            case NEG: {
                int top = s.top(); s.pop();
                s.push(top * -1);
                break;
            }
            case STORE: {
                int top = s.top(); s.pop();
                vars[tokens[pc].second] = top;
                break;
            }
            case LOAD: {
                auto it = vars.find(tokens[pc].second);
                if (it != vars.end()) {
                    s.push(it->second);
                } else {
                    // TODO: verificacao de erros (se precisar)
                }
                break;
            }
            case JMP: {
                if (is_number(tokens[pc].second)) {
                    pc = std::stoi(tokens[pc].second);
                } else {
                    pc = labels[tokens[pc].second];
                }
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
                }
                break;
            }
            case HALT: {
                cout << "Fim da execucao\n";
                print_stack();
                print_vars();
                goto fim_do_loop;
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
                int func;
                s.push(pc);
                cout << "\n-------------" << pc << "---------\n";
                if (is_number(tokens[pc].second)) {
                    func = std::stoi(tokens[pc].second);
                } else {
                    func = labels[tokens[pc].second];
                }
                pc = func;
                break;
            }
            case RET: {
                pc = s.top(); s.pop();
                break;
            }
            case READ: {
                int input;
                cout << "Digite um valor: ";
                cin >> input;
                s.push(input);
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
    fim_do_loop:
    return;
}



#endif