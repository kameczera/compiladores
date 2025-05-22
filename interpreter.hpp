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
                int val1 = s.top(); s.pop();
                int val2 = s.top(); s.pop();
                s.push(val1 + val2);
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