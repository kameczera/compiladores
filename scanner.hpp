#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "token.hpp"

using namespace std;

vector<pair<token_type, string>> tokens;
map<string, int> labels;
//Scanline antigo que comentei, mas que pode ser usado se necessário né
// void scan_line(string line) {
//     int init = 0;
//     int last = 0;
//     while(last < line.size()) {
//         for(; isalnum(line[last]) || line[last] == '_'; last++);
//         string token = line.substr(init, last);
//         if(last >= line.size()) {
//             tokens.push_back({token_dict[token], ""});
//             break;
//         }
//         if(line[last] == ':') {
//             tokens.push_back({LABEL, ""});
//             labels.insert({token, tokens.size()-1});
//             break;
//         }
//         init = ++last;
//         for(; isalnum(line[last]) || line[last] == '_'; last++);
//         string value = line.substr(init, last);
//         tokens.push_back({token_dict[token], value});
//     }
// }


void scan_line(string line) {
    // Ignora as linhas vazias ou que só contenham espaços
    if (line.find_first_not_of(" \t\n\v\f\r") == std::string::npos) 
    {
        return;
    }

    int i = 0;
    // Pula espaços em branco no início da linha
    while (i < line.size() && isspace(line[i])) i++;

    // Lê a primeira palavra (que pode ser uma instrução ou o nome de uma label)
    int start = i;
    while (i < line.size() && !isspace(line[i]) && line[i] != ':') i++;
    string token_str = line.substr(start, i - start);

    // Pula os espaços em branco depois da primeira palavra
    while (i < line.size() && isspace(line[i])) i++;

    // Verifica se o que vem a seguir é ':', o que define uma LABEL
    if (i < line.size() && line[i] == ':') {
        tokens.push_back({LABEL, token_str});
        labels.insert({token_str, tokens.size() - 1});
        return; // Linha processada
    }

    // Se não for uma label, verifica se há um argumento (segunda palavra)
    if (i < line.size())
     {
        // É uma instrução com argumento
        start = i;
        while (i < line.size() && !isspace(line[i])) i++;
        string value = line.substr(start, i - start); // Leitura correta do argumento
        tokens.push_back({token_dict[token_str], value});
    } else 
    {
        // É uma instrução sem argumento
        tokens.push_back({token_dict[token_str], ""});
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