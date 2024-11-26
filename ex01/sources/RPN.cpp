#include <RPN.hpp>

std::stack<int> RPN::stack;
std::string RPN::number;

void RPN::calculate(const std::string &expression) {
  for (char c : expression) {
    if (std::isdigit(c)) {
      number += c;
    } else if (std::isspace(c)) {
      appendNumber(number);
      number.clear();
    } else if (isValidOperation(c)) {
      performCalculation(c);
    }
  }
  showResult();
}

void RPN::showResult(void) {
  if (!number.empty()) {
    appendNumber(number);
  } else if (stack.size() != 1) {
    throw std::invalid_argument("Syntax error");
  }
  std::cout << stack.top() << "\n";
}

void RPN::performCalculation(char c) {
  int a, b, result;
  b = stack.top();
  stack.pop();
  a = stack.top();
  stack.pop();
  result = performOperation(a, b, c);
  stack.push(result);
}

void RPN::appendNumber(const std::string &value) {
  if (!number.empty())
    try {
      stack.push(std::stoi(value));
    } catch (const std::invalid_argument &e) {
      std::cerr << "Invalid argument: " << value << "\n";
    } catch (const std::out_of_range &e) {
      std::cerr << "Out of range: " << value << "\n";
    }
}

bool RPN::isValidOperation(char c) {
  static const std::string tokens = "+-/*";
  if (tokens.find(c) == std::string::npos || stack.size() <= 1) {
    throw std::invalid_argument("Syntax error");
  } else {
    return true;
  }
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
