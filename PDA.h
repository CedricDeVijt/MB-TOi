#ifndef TOI_PDA_H
#define TOI_PDA_H
#include <string>
#include <tuple>
#include "CFG.h"

typedef std::tuple<std::string, char, std::string, std::string, std::vector<std::string>> Transition;

class PDA {
    std::string startState;
    std::string startStack;
    std::vector<std::string> states;
    std::vector<std::string> alphabet;
    std::vector<std::string> stackAlphabet;
    std::vector<Transition> transitions;

public:
    explicit PDA(const std::string&filename);
    CFG toCFG();

private:
    std::vector<std::string> getCFGVariables();
    std::vector<std::pair<std::string, std::vector<std::string>>> getCFGProductions();
};


#endif //TOI_PDA_H
