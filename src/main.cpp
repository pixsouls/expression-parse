#include "../include/expression_parse.h"  
#include <iostream>

int main() {
    std::string result = EXPRESSION_PARSE_H::parseExpression("1 + 2 * 7");
    std::cout << "Result: " << result << std::endl;
    return 0;
}
