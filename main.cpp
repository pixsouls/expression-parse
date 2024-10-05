// Your First C++ Program

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



int main() {
    string userInput;
    getline(cin, userInput);  // Read the entire input, including spaces
    cout << "User Input: " << userInput << endl;

    deque<char> operatorDeque = parseOperators(userInput);
    
    while (!operatorDeque.empty()) {
        char op = operatorDeque.front(); // Get the front operator
        operatorDeque.pop_front();             // Remove the top element
        userInput = singleOperation(userInput, op);
    }

    cout << "Result: " << userInput << endl;
    return 0;
}