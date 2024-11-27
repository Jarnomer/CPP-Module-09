#pragma once

#include <cctype>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>

class RPN {
public:
  RPN(void) = delete;
  RPN(const RPN &other) = delete;
  RPN &operator=(const RPN &other) = delete;
  ~RPN(void) = delete;

private:
  static std::stack<int> stack;
  static std::string number;
  static const std::string tokens;

public:
  static void calculate(const std::string &expression);
  static void appendStack(const std::string &value);
  static bool isValidOperation(char c);
  static void performCalculation(char c);
  static int performOperation(int a, int b, char op);
  static void printResult(void);
};
