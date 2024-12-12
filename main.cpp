#include <iostream>
#include <stack>
#include <cctype>
#include <string>
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1; // Low precedence
    if (op == '*' || op == '/') return 2; // High precedence
    return 0; // For non-operator characters
}

int applyOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;  // Add numbers
        case '-': return a - b;  // Subtract numbers
        case '*': return a * b;  // Multiply numbers
        case '/': return a / b;  // Divide numbers
        default: return 0;
    }
}

int evaluateExpression(string expression) {
    stack<int> numbers;       // To store numbers
    stack<char> operators;    // To store operators

    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ') continue;  // Skip spaces

        if (isdigit(expression[i])) {
            int num = 0;

            // Read the full number
            while (i < expression.length() && isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--;  // Adjust `i` because the loop goes one step extra
            numbers.push(num);  // Push the number to the stack
        }
        else if (expression[i] == '(') {
            operators.push(expression[i]);  // Push opening parenthesis
        }
        else if (expression[i] == ')') {
            // Process until '(' is found
            while (!operators.empty() && operators.top() != '(') {
                int b = numbers.top(); numbers.pop();
                int a = numbers.top(); numbers.pop();
                char op = operators.top(); operators.pop();
                numbers.push(applyOperation(a, b, op));
            }
            operators.pop();  // Remove the '('
        }
        else {
            // Operator is encountered
            while (!operators.empty() && precedence(operators.top()) >= precedence(expression[i])) {
                int b = numbers.top(); numbers.pop();
                int a = numbers.top(); numbers.pop();
                char op = operators.top(); operators.pop();
                numbers.push(applyOperation(a, b, op));
            }
            operators.push(expression[i]);  // Push the current operator
        }
    }

    // Process remaining operators in the stack
    while (!operators.empty()) {
        int b = numbers.top(); numbers.pop();
        int a = numbers.top(); numbers.pop();
        char op = operators.top(); operators.pop();
        numbers.push(applyOperation(a, b, op));
    }

    return numbers.top();  // Final result
}

int main() {
    string expression;
    cout << "Enter a mathematical expression: ";
    getline(cin, expression);  // Read the full expression with spaces
    cout << "Result: " << evaluateExpression(expression) << endl;
    return 0;
}
