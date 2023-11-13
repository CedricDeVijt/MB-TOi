#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include "PDA.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

PDA::PDA(const std::string &filename) {
    ifstream input_stream(filename);
    json json_input = json::parse(input_stream);

    // Get States
    for (const auto &symbol: json_input["States"]) {
        states.push_back(symbol);
    }

    // Get Alphabet
    for (const auto &symbol: json_input["Alphabet"]) {
        alphabet.push_back(symbol);
    }

    // Get StackAlphabet
    for (const auto &symbol: json_input["StackAlphabet"]) {
        stackAlphabet.push_back(symbol);
    }

    // Get StartState
    startState = std::string(json_input["StartState"]);

    // Get StartStack
    startStack = std::string(json_input["StartStack"]);

    // Get Transitions
    for (const auto &transition: json_input["Transitions"]) {
        std::string from_state = transition["from"];
        std::string input_symbol = transition["input"];
        std::string stack_top = transition["stacktop"];
        std::string to_state = transition["to"];
        std::vector<std::string> replacement = transition["replacement"];

        // Create a Transition tuple and add it to the transitions vector
        transitions.emplace_back(from_state, input_symbol[0], stack_top, to_state, replacement);
    }
}

std::vector<std::string> PDA::getCFGVariables() {
    std::vector<std::string> variables = {"S"};
    for (const auto &state1: states) {
        for (const auto &symbol: stackAlphabet) {
            for (const auto &state2: states) {
                variables.push_back("[" + state1 + "," + string(symbol) + "," + string(state2) + "]");
            }
        }
    }
    return variables;
}

std::vector<std::pair<std::string, std::vector<std::string>>> PDA::getCFGProductions() {
    std::vector<std::pair<std::string, std::vector<std::string>>> productions;

    // Start state
    productions.reserve(states.size());
    for (auto &state: states) {
        productions.emplace_back("S",
                                 std::vector<std::string>{"[" + startState + "," + startStack + "," + state + "]"});
    }

    // Transitions
    for (const auto &transition: transitions) {
        std::string from_state = std::get<0>(transition);
        char input_char = std::get<1>(transition);
        string input_symbol = string(1, std::get<1>(transition));
        if (input_char == '\0'){
            input_symbol = "";
        }
        std::string stack_top = std::get<2>(transition);
        std::string to_state = std::get<3>(transition);
        std::vector<std::string> replacement = std::get<4>(transition);

        if (replacement.empty()){
            string head = "[" + from_state + "," + stack_top + "," + to_state + "]";
            productions.emplace_back(head, std::vector<std::string>{input_symbol});
        } else if (replacement.size() == 1){
            for (auto state1: states){
                string head = "[" + from_state + "," + stack_top + "," + state1 + "]";
                productions.emplace_back(head, std::vector<std::string>{input_symbol + " [" + to_state + "," + replacement[0] + "," + state1 + "]"});
            }
        } else if (replacement.size() == 2){
            for (auto state1: states){
                for (auto state2: states){
                    string head = "[" + from_state + "," + stack_top + "," + state1 + "]";
                    productions.emplace_back(head, std::vector<std::string>{input_symbol + " [" + to_state + "," + replacement[0] + "," + state2 + "]"+ " [" + state2 + "," + replacement[1] + "," + state1 + "]"});
                }
            }
        }

    }
    return productions;
};

CFG PDA::toCFG() {
    return {getCFGVariables(), alphabet, getCFGProductions(), "S"};
}

