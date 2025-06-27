#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <fstream>

#include "scanner.hpp"
#include "interpreter.hpp"

#define DEBUG 0

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " <nome_do_arquivo>" << endl;
        return 1;
    }

    string file_name = argv[1];
    ifstream file(file_name);

    if (file.is_open()) {
        vector<pair<token_type, string>> tokens = scan_tokens(file);
        file.close();
        if(DEBUG) {
            print_tokens();
            print_labels();
        }
        interpret(tokens);
    } else {
        cout << "Erro ao abrir o arquivo: " << file_name << endl;
        return 1;
    }

    return 0;
}
