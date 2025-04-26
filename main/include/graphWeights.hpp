#ifndef WEIGHTS_HPP
#define WEIGHTS_HPP

#include<iostream>

enum Weight{
    WEAK,
    STRONG
};

// Overload the >> operator for input Weights
inline std::istream& operator>>(std::istream& in, Weight& command) {
    std::string value;
    in >> value;

    static const std::unordered_map<std::string, Weight> commandMap = {
        {"WEAK", Weight::WEAK},
        {"STRONG", Weight::STRONG}
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