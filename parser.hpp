#ifndef PARSER_HPP
#define PARSER_HPP

#include "expr.hpp"
#include <vector>
#include "token.hpp"
#include "expr.hpp"

class ast {
    expr* root;
};

ast* create_ast(vector<pair<token_type, string>> tokens){
    int cont = 0;
    stack<expr*> s;
    switch(tokens[cont].first) {
        case PUSH:
            value* e = new value(tokens[cont].second);
            push* p = new push(e);
            s.push(p);
            break;
        case POP:
            pop* e = new pop(s.top()); s.pop();
            break;
        case ADD:
            expr* top = s.top(); s.pop();
            expr* bottom = s.top(); s.pop();
            binary* e = new binary(ADD, top, bottom);
            s.push(e);
            break;
        case SUB:
            expr* top = s.top(); s.pop();
            expr* bottom = s.top(); s.pop();
            binary* e = new binary(SUB, top, bottom);
            s.push(e);
            break;
        case MUL:
            expr* top = s.top(); s.pop();
            expr* bottom = s.top(); s.pop();
            binary* e = new binary(MUL, top, bottom);
            s.push(e);
            break;
        case DIV:
            expr* top = s.top(); s.pop();
            expr* bottom = s.top(); s.pop();
            binary* e = new binary(DIV, top, bottom);
            s.push(e);
            break;
        case MOD:
            expr* top = s.top(); s.pop();
            expr* bottom = s.top(); s.pop();
            binary* e = new binary(MOD, top, bottom);
            s.push(e);
            break;
        case NEG:
            expr* top = s.top(); s.pop();
            expr* bottom = s.top(); s.pop();
            binary* e = new binary(NEG, top, bottom);
            s.push(e);
            break;
        case STORE:
            expr* top = s.top(); s.pop();
            store* e = new store(top);
            break;
        case LOAD:
            expr* top = s.top(); s.pop();
            load* e = new load(top);
        default:
            break;
    }
}


#endif