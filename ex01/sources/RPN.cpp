#include <RPN.hpp>

std::stack<int> RPN::stack;
std::string RPN::number;
const std::string RPN::tokens = "+-/*";

void RPN::calculate(const std::string &expression) {
  for (char c : expression) {
    if (std::isdigit(c)) {
      number += c;
    } else if (std::isspace(c)) {
      appendStack(number);
      number.clear();
    } else if (isValidOperation(c)) {
      performCalculation(c);
    }
  }
  printResult();
}

// no try-catch, return to main in case of error
void RPN::appendStack(const std::string &value) {
  if (!number.empty()) {
    stack.push(std::stoi(value));
  }
}

bool RPN::isValidOperation(char c) {
  if (tokens.find(c) == std::string::npos || stack.size() < 2) {
    throw std::invalid_argument("Syntax error");
  } else {
    return true;
  }
}

// no try-catch, return to main in case of error
void RPN::performCalculation(char c) {
  int a, b, result;
  b = stack.top();
  stack.pop();
  a = stack.top();
  stack.pop();
  result = performOperation(a, b, c);
  stack.push(result);
}

int RPN::performOperation(int a, int b, char op) {
  switch (op) {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    if (b == 0) {
      throw std::invalid_argument("Division by zero");
    } else {
      return a / b;
    }
  default:
    throw std::invalid_argument("Syntax error");
  }
}

void RPN::printResult(void) {
  if (!number.empty()) {
    appendStack(number);
  }
  if (stack.size() != 1) {
    throw std::invalid_argument("Syntax error");
  } else {
    std::cout << stack.top() << "\n";
  }
}
