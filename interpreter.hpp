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
stack<int> call_stack; // <-- ADICIONE ESTA NOVA PILHA

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

vector<pair<token_type, string>> optimize_tokens(const vector<pair<token_type, string>>& original_tokens) 
{
    vector<pair<token_type, string>> optimized_tokens;
    int i = 0;
    while (i < original_tokens.size()) 
    {
        bool pattern_found = false;

        if (i + 2 < original_tokens.size()) 
        {
            if (original_tokens[i].first == PUSH && is_number(original_tokens[i].second) &&
                original_tokens[i+1].first == PUSH && is_number(original_tokens[i+1].second))
            {
                int num1 = stoi(original_tokens[i].second);
                int num2 = stoi(original_tokens[i+1].second);
                token_type op = original_tokens[i+2].first;
                int result;

                if (op == ADD) { result = num1 + num2; pattern_found = true; }
                else if (op == SUB) { result = num1 - num2; pattern_found = true; }
                else if (op == MUL) { result = num1 * num2; pattern_found = true; }
                else if (op == DIV && num2 != 0) { result = num1 / num2; pattern_found = true; }
                else if (op == GT) { result = (num1 > num2) ? 1 : 0; pattern_found = true; }
                else if (op == LT) { result = (num1 < num2) ? 1 : 0; pattern_found = true; }
                else if (op == EQ) { result = (num1 == num2) ? 1 : 0; pattern_found = true; }

                if(pattern_found) 
                {
                    optimized_tokens.push_back({PUSH, to_string(result)});
                    i += 3;
                }
            }
        }

        // Se o padrão acima não foi encontrado, tenta outros
        if (!pattern_found) 
        {
            // Padrão 2: PUSH num, NEG
            if (i + 1 < original_tokens.size() &&
                original_tokens[i].first == PUSH && is_number(original_tokens[i].second) &&
                original_tokens[i+1].first == NEG)
            {
                int num = stoi(original_tokens[i].second);
                int result = -num;
                optimized_tokens.push_back({PUSH, to_string(result)});
                i += 2;
                pattern_found = true;
            }
        }
        
        // Se nenhum padrão de otimização foi encontrado, apenas copia a instrução
        if (!pattern_found) 
        {
            optimized_tokens.push_back(original_tokens[i]);
            i++;
        }
    }
    return optimized_tokens;
}


void interpret(vector<pair<token_type, string>> tokens) 
{
    pc = 0; // Garante que a execução sempre comece do início
    
   while(!s.empty()) s.pop();
    vars.clear();
    while(!call_stack.empty()) call_stack.pop();
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
                call_stack.push(pc + 1); //Usa a call_stack implementada
                if (is_number(tokens[pc].second)) {
                    pc = std::stoi(tokens[pc].second);
                } else {
                    pc = labels[tokens[pc].second];
                }
                continue; 
            }
            case RET: {
                pc = call_stack.top(); call_stack.pop(); //Usa a call_stack implementada
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