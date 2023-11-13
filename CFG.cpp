#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "json.hpp"
#include "CFG.h"

using namespace std;
using json = nlohmann::json;

void CFG::print() {
    // Sort variables, terminals, and productions
    std::sort(variables.begin(), variables.end());
    std::sort(terminals.begin(), terminals.end());
    std::sort(productions.begin(), productions.end());

    // Print variables
    std::cout << "V = {" << variables[0];
    for (int i = 1; i < variables.size(); ++i) {
        std::cout << ", " << variables[i];
    }
    std::cout << "}" << std::endl;

    // Print Terminals
    std::cout << "T = {" << terminals[0];
    for (int i = 1; i < terminals.size(); ++i) {
        std::cout << ", " << terminals[i];
    }
    std::cout << "}" << std::endl;

    // Print P
    std::cout << "P = {" << std::endl;
    for (const auto &production: productions) {
        if (production.first == "S") {
            std::cout << "    " << production.first << "   -> ";
        } else {
            std::cout << "    " << std::setw(12) << std::left << production.first << "-> ";
        }


        if (production.second.empty()) {
            std::cout << "``";
        } else {
            std::cout << "`";
            for (size_t i = 0; i < production.second.size(); ++i) {
                std::cout << production.second[i];
                if (i < production.second.size() - 1) {
                    std::cout << " ";
                }
            }
            std::cout << "`";
        }
        std::cout << std::endl;
    }
    std::cout << "}" << std::endl;


    // Print start
    std::cout << "S = " << start;
}


CFG::CFG(const string &filename) {
    ifstream input_stream(filename);
    json json_input = json::parse(input_stream);

    // Get Variables
    for (const auto &symbol: json_input["Variables"]) {
        variables.push_back(symbol);
    }

    // Get Terminals
    for (const auto &symbol: json_input["Terminals"]) {
        terminals.push_back(symbol);
    }

    // Get Productions
    for (const auto &production: json_input["Productions"]) {
        std::string head = production["head"];
        std::vector<std::string> body;

        for (const auto &symbol: production["body"]) {
            body.push_back(symbol);
        }

        productions.emplace_back(head, body);
    }

    // Get start state
    start = std::string(json_input["Start"]);

    // Sorteer de variabelen, terminals en producties
    std::sort(variables.begin(), variables.end());
    std::sort(terminals.begin(), terminals.end());
    std::sort(productions.begin(), productions.end());
}

CFG::CFG(const std::vector<std::string> &variables, const std::vector<std::string> &terminals,
         const std::vector<std::pair<std::string, std::vector<std::string>>> &productions, const std::string &start)
        : variables(variables),
          terminals(terminals),
          productions(productions),
          start(start) {
}
