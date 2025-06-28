#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <fstream>

#include "scanner.hpp"
#include "interpreter.hpp" 

#define DEBUG 0

using namespace std;

int main(int argc, char* argv[]) 
{
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " <nome_do_arquivo>" << endl;
        return 1;
    }

    string file_name = argv[1];
    ifstream file(file_name);

    if (file.is_open())
     {
        vector<pair<token_type, string>> tokens = scan_tokens(file);
        file.close();
        
        cout << "--- Otimizacao ---" << endl;
        cout << "Tamanho do bytecode original: " << tokens.size() - 1 << " instrucoes." << endl;

        // Chama a função de otimização
        vector<pair<token_type, string>> optimized_tokens = optimize_tokens(tokens);
        
        cout << "Tamanho do bytecode otimizado: " << optimized_tokens.size() - 1 << " instrucoes." << endl;
        cout << "--------------------" << endl << endl;

        // Recalcula o mapa de labels com base nos tokens otimizados para garantir que os endereços de pulo estejam corretos.
        labels.clear(); // Limpa o mapa antigo com os índices desatualizados.
        for (int i = 0; i < optimized_tokens.size(); ++i) {
            if (optimized_tokens[i].first == LABEL) {
                // Adiciona a label com seu nome e o NOVO índice correto na lista otimizada.
                labels[optimized_tokens[i].second] = i;
            }
        }

//Bloco de debug para imprimir o mapa de labels atualizado
        cout << "--- Mapa de Labels Final (para Debug) ---" << endl;
        for (const auto& par : labels) 
        {
            cout << "Label: '" << par.first << "' -> Posicao: " << par.second << endl;
        }
        cout << "---------------------------------------" << endl << endl;

        if(DEBUG) 
        {
            cout << "Tokens Originais:" << endl;
            print_tokens(); 
            print_labels();
            cout << "\nTokens Otimizados:" << endl;
        }

        // Finalmente, interpreta o código JÁ OTIMIZADO (graças a deus) com o mapa de labels CORRETO.
        interpret(optimized_tokens);

    } else 
    {
        cout << "Erro ao abrir o arquivo: " << file_name << endl;
        return 1;
    }

    return 0;
}