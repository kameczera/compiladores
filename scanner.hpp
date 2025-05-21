#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "error.hpp"

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

static map<string, token_type> token_dict = {
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

vector<pair<string, token_type>> tokens;

void scan_line(string line) {
    int init = 0;
    int last = 0;
    while(last < line.size()) {
        for(; isalnum(line[last]) || line[last] == '_'; last++);
        string token = line.substr(init, last);
        if (token_dict.find(token) != token_dict.end()) {
            tokens.push_back({token, token_dict[token]});
        } else {
            tokens.push_back({token, ID});
        }
        init = ++last;
    }
}

vector<pair<string, token_type>> scan_tokens(ifstream& file) {
    string line;
    while (getline(file, line)) {
        scan_line(line);
    }
    return tokens;
}

void print_tokens() {
    for(const pair<string, token_type>& token : tokens) cout << token.first << ": " << token.second << "\n";
}

#endif