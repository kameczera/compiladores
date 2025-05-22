#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <map>
#include <vector>

using namespace std;

enum token_type {
    PUSH, POP, ADD, SUB, MUL,
    DIV, MOD, NEG,
    
    STORE, LOAD,

    JMP, JZ, JNZ, HALT,

    EQ, NEQ, LT, GT, LE, GE,

    CALL, RET, PRINT, READ,

    ID,
};

map<string, token_type> token_dict = {
    {"PUSH", token_type::PUSH},
    {"POP", token_type::POP},
    {"ADD", token_type::ADD},
    {"MUL", token_type::MUL},
    {"DIV", token_type::DIV},
    {"MOD", token_type::MOD},
    {"NEG", token_type::NEG},
    {"STORE", token_type::STORE},
    {"LOAD", token_type::LOAD},
    {"JMP", token_type::JMP},
    {"JZ", token_type::JZ},
    {"JNZ", token_type::JNZ},
    {"HALT", token_type::HALT},
    {"EQ", token_type::EQ},
    {"NEQ", token_type::NEQ},
    {"LT", token_type::LT},
    {"GT", token_type::GT},
    {"LE", token_type::LE},
    {"GE", token_type::GE},
    {"CALL", token_type::CALL},
    {"RET", token_type::RET},
    {"PRINT", token_type::PRINT},
    {"READ", token_type::READ},
};

#endif