#include "../include/expression_parse.h"
#include <iostream>
#include <sstream>
#include <string>
#include <deque>
#include <array>
#include <vector>
#include <cmath>

using namespace std;

enum class Operator {
    addition = '+',
    subtraction = '-',
    multiplication = '*',
    division = '/'
};

array<char, 4> OPERATORS = {'*', '/', '+', '-'};
char SPACE_CHARACTER = ' ';


bool isOperator(char character) {
    for (int i = 0; i < OPERATORS.size(); i++) {
        if (character == OPERATORS[i]) {
           return true;
        }
    }
    return false;
}


char operatorAt(char character) {
    for (int i = 0; i < OPERATORS.size(); i++) {
        if (character == OPERATORS[i]) {
           return OPERATORS[i];
        }
    }

    // ERROR CASE
    return '?';
}


deque<char> parseOperators(string userInput) {
    deque<char> operatorDequeOutput;
    for (int i = 0; i < userInput.size(); i++) {
        if (isOperator(userInput[i])) {
            switch (operatorAt(userInput[i]))
            {
            case '*':
                operatorDequeOutput.push_front(operatorAt(userInput[i]));
                break;
            case '/':
                operatorDequeOutput.push_front(operatorAt(userInput[i]));
                break;
            case '+':
                operatorDequeOutput.push_back(operatorAt(userInput[i]));
                break;
            case '-':
                operatorDequeOutput.push_back(operatorAt(userInput[i]));
                break;
            default:
                break;
            }
        }
    }


    return operatorDequeOutput;
};


string singleOperation(string strInput, char operation) {
    int strPosition = strInput.find(operation);

    // Get left number (move left from the operator)
    int strPositionLeft = strPosition - 2;  // Start 2 positions before operator (to skip the space)
    string leftStr = "";
    while (strPositionLeft >= 0 && strInput[strPositionLeft] != SPACE_CHARACTER) {
        leftStr = strInput[strPositionLeft] + leftStr;  // Collect digits from left
        strPositionLeft--;
    }
    float leftOperand = stof(leftStr);  // Convert to float

    // Get right number (move right from the operator)
    int strPositionRight = strPosition + 2;  // Start 2 positions after operator (to skip the space)
    string rightStr = "";
    while (strPositionRight < strInput.size() && strInput[strPositionRight] != SPACE_CHARACTER) {
        rightStr += strInput[strPositionRight];  // Collect digits from right
        strPositionRight++;
    }
    float rightOperand = stof(rightStr);  // Convert to float

    // Perform the operation
    float result = 0;
    switch (operation) {
        case '+':
            result = leftOperand + rightOperand;
            break;
        case '-':
            result = leftOperand - rightOperand;
            break;
        case '*':
            result = leftOperand * rightOperand;
            break;
        case '/':
            result = leftOperand / rightOperand;
            break;
        default:
            cout << "Invalid operation" << endl;
            return strInput;
    }

    // Replace the expression in the original string with the result
    string resultStr = to_string((int) result);
    return strInput.replace(strPositionLeft + 1, strPositionRight - strPositionLeft - 1, resultStr);
}


string formatExpression(string expression) {
    for (int i = 0; i < expression.size(); i++) {
        for (auto op : OPERATORS) {
            // space before and after
            if (expression[i] == op) {
                // yeah.............
                if (expression[i + 1] != ' ' and expression[i - 1] != ' ') {
                    expression.insert(i + 1, 1, ' ');
                    expression.insert(i, 1, ' ');
                    i += 2;
                } else if (expression[i + 1] != ' ') {
                    expression.insert(i + 1, 1, ' ');
                } else if (expression[i - 1] != ' ') {
                    expression.insert(i, 1, ' ');
                }
            }
        }
    }
    return expression;
}


std::string parseExpression(string expression) {
    cout << "User Input: " << expression << endl;

    // check if expression given by user is valid 
    // ERROR: needs at least 1 operator
    bool isOperatorsPresent = false;
    for (int i = 0; i < OPERATORS.size(); i++) {
        if (expression.find(OPERATORS[i]) != string::npos) {
            isOperatorsPresent = true;
        }
    }
    if (!isOperatorsPresent) {
        return "No operations found";
    }


    // ERROR: check if expression starts with an operator
    for (auto op : OPERATORS) {
        if (expression[0] == op) {
            return "Expression cannot start with an operator";
        }
    }

    expression = formatExpression(expression);
    cout << "Interpretted As: " << expression << endl; 
    string expressionResult;
    deque<char> operatorDeque = parseOperators(expression);

    while (!operatorDeque.empty()) {
        char op = operatorDeque.front();
        operatorDeque.pop_front();
        expressionResult = singleOperation(expression, op);
    }

    return expression;
}