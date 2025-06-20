#ifndef EXPR_HPP
#define EXPR_HPP

#include <stack>
#include <iostream>
#include <string>

using namespace std;

class expr {
    public:
        virtual ~expr() = default;
};

class value : public expr {
    public:
        value(string data) : data(stoi(data)) {}
        int data;

};

class push : public expr {
    public:
        push(expr* value) : value(value) {}
        expr* value;
};

class pop : public expr {
    public:
        pop(expr* out) : out(out) {}
        expr* out;
};

class binary : public expr {
    public:
        int type;
        expr* top;
        expr* bottom;
        binary(int type, expr* top, expr* bottom) : type(type), top(top), bottom(bottom) {}
};

class store : public expr {
    public:
        expr* stored;
        store(expr* stored) : stored(stored) {}
};

#endif