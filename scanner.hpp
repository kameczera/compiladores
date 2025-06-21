#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "error.hpp"
#include "token.hpp"

using namespace std;

vector<pair<token_type, string>> tokens;
map<string, int> labels;

void scan_line(string line) {
    int init = 0;
    int last = 0;
    while(last < line.size()) {
        for(; isalnum(line[last]) || line[last] == '_'; last++);
        string token = line.substr(init, last);
        if(last >= line.size()) {
            tokens.push_back({token_dict[token], ""});
            break;
        }
        if(line[last] == ':') {
            tokens.push_back({LABEL, ""});
            labels.insert({token, tokens.size()});
            break;
        }
        init = ++last;
        for(; isalnum(line[last]) || line[last] == '_'; last++);
        string value = line.substr(init, last);
        tokens.push_back({token_dict[token], value});
    }
}

vector<pair<token_type, string>> scan_tokens(ifstream& file) {
    string line;
    int i = 0;
    while (getline(file, line)) {
        scan_line(line);
    }
    tokens.push_back({END, "end"});
    return tokens;
}

void print_tokens() {
    cout << "Lista de tokens:\n";
    cout << "Lexema: Id no dicionário\n";
    for(const pair<token_type, string>& token : tokens) cout << token.first << ": " << token.second << "\n";
}

void print_labels() {
    cout << "Lista de labels:\n";
    cout << "Label: Posição\n";
    for (const auto& par : labels) {
        std::cout << "Chave: " << par.first << ", Valor: " << par.second << std::endl;
    }
}

#endif