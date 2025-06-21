#ifndef COMPILER_HPP
#define COMPILER_HPP

#include <string>

using namespace std;

bool is_number(const std::string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(c) && c != '-' && c != '+') return false;
    }
    try {
        std::stoi(s);
        return true;
    } catch (...) {
        return false;
    }
}

#endif