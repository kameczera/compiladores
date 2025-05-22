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
            }
            case MUL: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                s.push(top * bottom);
            }
            case DIV: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                s.push(top / bottom);
            }
            case MOD: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                s.push(top % bottom);
            }
            case NEG: {
                int top = s.top(); s.pop();
                s.push(top * -1);
            }
            case STORE: {
                
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