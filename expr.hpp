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
        pop() {}
};

class add : public expr {
    public:
        expr* top;
        expr* bottom;
        add(expr* top, expr* bottom) : top(top), bottom(bottom) {}
};

#endif