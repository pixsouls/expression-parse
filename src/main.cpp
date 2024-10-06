#include "../include/expression_parse.h"  
#include <iostream>

int main() {
    std::string result;

    // VALID INPUTS
    result = EXPRESSION_PARSE_H::parseExpression("1 + 2 * 7");
    std::cout << "Result: " << result << std::endl;

    // ERROR CONDITIONS
    result = EXPRESSION_PARSE_H::parseExpression("+ 1 + 2 * 7");
    std::cout << "Result: " << result << std::endl;
    result = EXPRESSION_PARSE_H::parseExpression("3 1");
    std::cout << "Result: " << result << std::endl;
    return 0;
}
