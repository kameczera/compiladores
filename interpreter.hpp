#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include "token.hpp"
#include "compiler.hpp"

using namespace std;


// 2. PROTÓTIPOS DE TODAS AS FUNÇÕES DO ARQUIVO
// Isso garante que o compilador conheça todas as funções antes de usá-las.
void interpret(vector<pair<token_type, string>> tokens);
vector<pair<token_type, string>> optimize_tokens(const vector<pair<token_type, string>>& original_tokens);
void print_stack();
void print_vars();

int pc = 0;
stack<int> s;
map<string, int> vars;

void print_stack()
{
    if (s.empty()) return;
    int x = s.top();
    s.pop();
    print_stack();
    cout << x << " ";
    s.push(x);
}

void print_vars() {
    for (const auto& par : vars) {
        std::cout << "Chave: " << par.first << ", Valor: " << par.second << std::endl;
    }
}

// Função auxiliar para imprimir o nome do token
string token_type_to_string(token_type t) {
    switch (t) {
        case PUSH: return "PUSH"; case POP: return "POP";
        case ADD: return "ADD"; case SUB: return "SUB";
        case MUL: return "MUL"; case DIV: return "DIV";
        case MOD: return "MOD"; case NEG: return "NEG";
        case STORE: return "STORE"; case LOAD: return "LOAD";
        case JMP: return "JMP"; case JZ: return "JZ";
        case JNZ: return "JNZ"; case HALT: return "HALT";
        case EQ: return "EQ"; case NEQ: return "NEQ";
        case LT: return "LT"; case GT: return "GT";
        case LE: return "LE"; case GE: return "GE";
        case CALL: return "CALL"; case RET: return "RET";
        case PRINT: return "PRINT"; case READ: return "READ";
        case LABEL: return "LABEL";
        case END: return "END";
        default: return "UNKNOWN";
    }
}

// Sua função optimize_tokens, agora com logs de otimização
vector<pair<token_type, string>> optimize_tokens(const vector<pair<token_type, string>>& original_tokens) 
{
    vector<pair<token_type, string>> current_tokens = original_tokens;
    int pass_count = 1;

    cout << "--- Iniciando Otimizacao Multi-Passo ---" << endl;

    while (true) {
        int size_before = current_tokens.size();
        vector<pair<token_type, string>> optimized_pass;
        int i = 0;
        bool pass_made_changes = false;

        while (i < current_tokens.size()) 
        {
            // Tenta aplicar o Padrão 1 (3 instruções)
            if (i + 2 < current_tokens.size() &&
                current_tokens[i].first == PUSH && is_number(current_tokens[i].second) &&
                current_tokens[i+1].first == PUSH && is_number(current_tokens[i+1].second))
            {
                token_type op = current_tokens[i+2].first;
                int result;
                bool pattern_matched = false;

                if (op == ADD) { pattern_matched = true; }
                else if (op == SUB) { pattern_matched = true; }
                else if (op == MUL) { pattern_matched = true; }
                else if (op == DIV && stoi(current_tokens[i+1].second) != 0) { pattern_matched = true; }
                else if (op == GT) { pattern_matched = true; }
                else if (op == LT) { pattern_matched = true; }
                else if (op == EQ) { pattern_matched = true; }
                
                if (pattern_matched) {
                    pass_made_changes = true;
                    int num1 = stoi(current_tokens[i].second);
                    int num2 = stoi(current_tokens[i+1].second);
                    if (op == ADD) result = num1 + num2;
                    else if (op == SUB) result = num1 - num2;
                    else if (op == MUL) result = num1 * num2;
                    else if (op == DIV) result = num1 / num2;
                    else if (op == GT) result = (num1 > num2) ? 1 : 0;
                    else if (op == LT) result = (num1 < num2) ? 1 : 0;
                    else if (op == EQ) result = (num1 == num2) ? 1 : 0;
                    
                    // --- LOG DE OTIMIZAÇÃO ADICIONADO ---
                    cout << "  [Passo " << pass_count << "] Otimizando: "
                         << "PUSH " << num1 << ", PUSH " << num2 << ", " << token_type_to_string(op)
                         << "  ->  PUSH " << result << endl;

                    optimized_pass.push_back({PUSH, to_string(result)});
                    i += 3;
                    continue;
                }
            }
            
            // Tenta o Padrão 2 (2 instruções)
            if (i + 1 < current_tokens.size() &&
                current_tokens[i].first == PUSH && is_number(current_tokens[i].second) &&
                current_tokens[i+1].first == NEG)
            {
                pass_made_changes = true;
                int num = stoi(current_tokens[i].second);
                int result = -num;

                // --- LOG DE OTIMIZAÇÃO ADICIONADO ---
                cout << "  [Passo " << pass_count << "] Otimizando: "
                     << "PUSH " << num << ", NEG" 
                     << "  ->  PUSH " << result << endl;

                optimized_pass.push_back({PUSH, to_string(result)});
                i += 2;
                continue;
            }

            // Se nenhum padrão foi encontrado, apenas copia
            optimized_pass.push_back(current_tokens[i]);
            i++;
        }

        if (!pass_made_changes) {
            break; // Se nenhuma mudança foi feita nesta passada, termina.
        }
        
        current_tokens = optimized_pass;
        pass_count++;
    }

    cout << "--- Otimizacao Finalizada ---" << endl;
    return current_tokens;
}


void interpret(vector<pair<token_type, string>> tokens) 
{
    pc = 0; // Garante que a execução sempre comece do início
    
   while(!s.empty()) s.pop();
    vars.clear();
    while(pc < tokens.size())
    {
        switch(tokens[pc].first) 
        {
            case PUSH: {
                s.push(stoi(tokens[pc].second));
                break;
            }
            case POP: {
                s.pop();
                break;
            }
            case ADD: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                s.push(bottom + top);
                break;
            }
            case SUB: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                s.push(bottom - top);
                break;
            }
            case MUL: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                s.push(bottom * top);
                break;
            }
            case DIV: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                s.push(bottom / top);
                break;
            }
            case MOD: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                s.push(bottom % top);
                break;
            }
            case NEG: {
                int top = s.top(); s.pop();
                s.push(top * -1);
                break;
            }
            case STORE: {
                int top = s.top(); s.pop();
                vars[tokens[pc].second] = top;
                break;
            }
            case LOAD: {
                auto it = vars.find(tokens[pc].second);
                if (it != vars.end()) {
                    s.push(it->second);
                } else {
                    // TODO: verificacao de erros (se precisar)
                }
                break;
            }
            case JMP: {
                if (is_number(tokens[pc].second)) {
                    pc = std::stoi(tokens[pc].second);
                } else {
                    pc = labels[tokens[pc].second];
                }
                continue; 
            }
            case JZ: {
                int top = s.top(); s.pop();
                if(top == 0) {
                    if (is_number(tokens[pc].second)) {
                        pc = std::stoi(tokens[pc].second);
                    } else {
                        pc = labels[tokens[pc].second];
                    }
                    continue; 
                }
                break; 
            }
            case JNZ: {
                int top = s.top(); s.pop();
                if(top != 0) {
                    if (is_number(tokens[pc].second)) {
                        pc = std::stoi(tokens[pc].second);
                    } else {
                        pc = labels[tokens[pc].second];
                    }
                    continue; 
                }
                break; 
            }
            case HALT: {
                print_stack();
                print_vars();
                goto fim_do_loop;
            }
            case EQ: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                if(top == bottom) s.push(1);
                else s.push(0);
                break;
            }
            case NEQ: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                if(top != bottom) s.push(1);
                else s.push(0);
                break;
            }
            case LT: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                if(bottom < top) s.push(1);
                else s.push(0);
                break;
            }
            case GT: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                if(bottom > top) s.push(1);
                else s.push(0);
                break;
            }
            case LE: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                if(bottom <= top) s.push(1);
                else s.push(0);
                break;
            }
            case GE: {
                int top = s.top(); s.pop();
                int bottom = s.top(); s.pop();
                if(bottom >= top) s.push(1);
                else s.push(0);
                break;
            }
            case CALL: {
                s.push(pc + 1); // Usa a pilha principal s
                if (is_number(tokens[pc].second)) {
                    pc = std::stoi(tokens[pc].second);
                } else {
                    pc = labels[tokens[pc].second];
                }
                continue; 
            }
            case RET: {
                pc = s.top(); s.pop(); // Usa a pilha principal s
                continue;
            }
            case READ: {
                int input;
                cin >> input;
                s.push(input);
                break;
            }
            case PRINT: {
                int val = s.top();
                cout << val << "\n";
                break;
            }
            default: {
                break;
            }
        }
        pc++;
    }
    fim_do_loop:
    return;
}



#endif