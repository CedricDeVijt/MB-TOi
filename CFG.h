#ifndef PO1_CFG_H
#define PO1_CFG_H

#include <vector>

class CFG {
    std::vector<std::string> variables;
    std::vector<std::string> terminals;
    std::vector<std::pair<std::string, std::vector<std::string>>> productions;
    std::string start;

public:
    CFG(const std::vector<std::string>&variables, const std::vector<std::string>&terminals,
        const std::vector<std::pair<std::string, std::vector<std::string>>>&productions, const std::string&start);

    explicit CFG(const std::string&filename);

    void print();
};


#endif //PO1_CFG_H
