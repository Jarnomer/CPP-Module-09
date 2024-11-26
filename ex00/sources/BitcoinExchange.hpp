#pragma once

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>

class BitcoinExchange {
private:
  std::map<std::string, double> data;

public: // constructors
  BitcoinExchange(void);

public: // deconstructor
  ~BitcoinExchange(void);

public: // methods
  void importData(const std::string &fileName);
  void printRates(const std::string &fileName);

private: // utils
  void appendData(const std::string &date, double amount);
  void convertRate(const std::string &date, double amount) const;
  std::string trimWhiteSpace(std::string &line) const;
  bool isValidDate(const std::string &date) const;
  bool isValidValue(double amount) const;

private: // parser
  void parseFile(const std::string &fileName, char delim,
                 const std::function<void(const std::string &, double)> &func);
};
