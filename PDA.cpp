#include <iostream>
#include <fstream>
#include "PDA.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

bool comparePairWords2(const pair<string,vector<string>>& a, const pair<string,vector<string>>& b) {
    if (a.first == b.first) {
        string one;
        for (const auto& elem: a.second)
            one += elem;
        string two;
        for (const auto& elem: b.second)
            two += elem;
        return one < two;
    }
    return a.first < b.first;
}

PDA::PDA(const std::string&filename) {
    ifstream input_stream(filename);
    json json_input = json::parse(input_stream);

    // Get States
    for (const auto&symbol: json_input["States"]) {
        states.push_back(symbol);
    }

    // Get Alphabet
    for (const auto&symbol: json_input["Alphabet"]) {
        alphabet.push_back(symbol);
    }

    // Get StackAlphabet
    for (const auto&symbol: json_input["StackAlphabet"]) {
        stackAlphabet.push_back(symbol);
    }

    // Get StartState
    startState = std::string(json_input["StartState"]);

    // Get StartStack
    startStack = std::string(json_input["StartStack"]);

    // Get Transitions
    for (const auto&transition: json_input["Transitions"]) {
        std::string from_state = transition["from"];
        std::string input_symbol = transition["input"];
        std::string stack_top = transition["stacktop"];
        std::string to_state = transition["to"];
        std::vector<std::string> replacement = transition["replacement"];

        // Create a Transition tuple and add it to the transitions vector
        transitions.push_back(std::make_tuple(from_state, input_symbol[0], stack_top, to_state, replacement));
    }
}

CFG PDA::toCFG() {
    // Get Variables
    std::vector<std::string> variables = {"S"};
    for (const auto&state1: states) {
        for (const auto&symbol: stackAlphabet) {
            for (const auto&state2: states) {
                variables.push_back("[" + state1 + "," + string(symbol) + "," + string(state2) + "]");
            }
        }
    }

    // Get Terminals
    std::vector<std::string> terminals = alphabet;

    // Get Productions
    std::vector<std::pair<std::string, std::vector<std::string>>> productions;
    


    //  Get Start
    std::string start = "S";

    return {variables, terminals, productions, start};
}
