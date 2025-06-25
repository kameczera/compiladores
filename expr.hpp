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

class jmp : public expr {
    public:
        expr* jump;
        
        jmp() {}
        jmp(expr* jump) : jump(jump) {}
};

class jz : public expr {
    public:
        int jump_idx;
        expr* jump_z;
        expr* jump_nz;

        jz() {}
        jz(expr* jump_z, expr* jump_nz) : jump_z(jump_z), jump_nz(jump_nz) {}
};

class label : public expr {
    public:
        expr* pointer;
        label() {}
        label(expr* pointer) : pointer(pointer) {}
};

#endif