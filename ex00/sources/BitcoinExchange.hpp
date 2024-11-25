#pragma once

#include <fstream>
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
  void importData(const std::string fileName);
  void getExchangeRates(const std::string &fileName);

private: // utilities
  void printRateInfo(std::string &date, std::string &value) const;
  std::string trimWhiteSpace(std::string &line) const;
  bool isValidDate(const std::string &date) const;
  bool isValidValue(const std::string &value) const;
};
