#include <BitcoinExchange.hpp>

BitcoinExchange::BitcoinExchange(void) {
  std::cout << "Default constructor called\n";
}

BitcoinExchange::~BitcoinExchange(void) {
  std::cout << "Deconstructor called\n";
}

void BitcoinExchange::importData(const std::string fileName) {
  std::ifstream input(fileName);
  std::string line, date, value;
  if (input.is_open()) {
    std::getline(input, line); // skip header
    while (std::getline(input, line)) {
      std::istringstream readLine(line);
      if (!std::getline(readLine, date, ',') ||
          !std::getline(readLine, value)) {
        std::cerr << "Invalid line format: " << line << "\n";
      } else if (isValidDate(trimWhiteSpace(date))) {
        data.emplace(date, std::stod(trimWhiteSpace(value)));
      }
    }
    input.close();
  } else {
    throw std::runtime_error("Failed to open file: " + fileName);
  }
}

void BitcoinExchange::getExchangeRates(const std::string &fileName) {
  std::ifstream input(fileName);
  std::string line, date, value;
  if (input.is_open()) {
    std::getline(input, line); // skip header
    while (std::getline(input, line)) {
      std::istringstream readLine(line);
      if (!std::getline(readLine, date, '|') ||
          !std::getline(readLine, value)) {
        std::cerr << "Invalid line format: " << line << "\n";
      } else if (isValidDate(trimWhiteSpace(date)) &&
                 isValidValue(trimWhiteSpace(value))) {
        printRateInfo(date, value);
      }
    }
    input.close();
  } else {
    throw std::runtime_error("Failed to open file: " + fileName);
  }
}

void BitcoinExchange::printRateInfo(std::string &date,
                                    std::string &value) const {
  for (const auto &[day, rate] : data) {
    if (day == date) {
      std::cout << day << " => " << value << " = " << rate << "\n";
      return;
    }
  }
  std::cerr << "Date not found from data: " << date << "\n";
}

std::string BitcoinExchange::trimWhiteSpace(std::string &str) const {
  str = std::regex_replace(str, std::regex("^[ \t]+|[ \t]+$"), "");
  return str;
}

bool BitcoinExchange::isValidDate(const std::string &str) const {
  std::regex pattern(R"((\d{4})-(\d{2})-(\d{2}))");
  if (!std::regex_match(str, pattern)) {
    std::cerr << "Invalid date format: " << str << "\n";
    return false;
  } else {
    return true;
  }
}

bool BitcoinExchange::isValidValue(const std::string &str) const {
  double value = std::stod(str);
  if (value > 1000 || value < 0) {
    std::cerr << "Value out of range: " << str << "\n";
    return false;
  } else {
    return true;
  }
}
