#pragma once

#include "Graph.hpp"
#include "Draw.hpp"
#include "Airport.hpp"

std::string lowercase(std::string input) {
    for (unsigned i = 0; i < input.length(); ++i) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            input[i] = input[i] + 32;
        }
    }
    return input;
};


int main(int argc, char **argv) {
    // operations: 
    std::string operation = "";
    for (int i = 0; i < argc; ++i) {
        operation += lowercase(argv[i]);
    }

    if (operation == ""){}
}