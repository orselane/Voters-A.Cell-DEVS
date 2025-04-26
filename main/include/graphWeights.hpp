#ifndef WEIGHTS_HPP
#define WEIGHTS_HPP

#include<iostream>

enum Weights{
    WEAK,
    STRONG
};

// Overload the >> operator for input Weights
inline std::istream& operator>>(std::istream& in, Weights& command) {
    std::string value;
    in >> value;

    static const std::unordered_map<std::string, Weights> commandMap = {
        {"WEAK", Weights::WEAK},
        {"STRONG", Weights::STRONG}
    };

    auto it = commandMap.find(value);
    if (it != commandMap.end()) {
        command = it->second;
    } else {
        in.setstate(std::ios::failbit);  // Set fail state if invalid
    }

    return in;
}

#endif