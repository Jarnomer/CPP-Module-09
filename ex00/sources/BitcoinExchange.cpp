#include <BitcoinExchange.hpp>
#include <string>

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
      } else if (isValidDate(trimWhiteSpace(date))) {
        double amount = std::stod(trimWhiteSpace(value));
        if (isValidValue(amount)) {
          printRateInfo(date, amount);
        }
      }
    }
    input.close();
  } else {
    throw std::runtime_error("Failed to open file: " + fileName);
  }
}

void BitcoinExchange::printRateInfo(std::string &day, double amount) const {
  std::string closestDate{};
  double closestRate = 0;
  for (const auto &[date, rate] : data) {
    if (date <= day) {
      closestDate = date;
      closestRate = rate;
    } else {
      break;
    }
  }
  std::cout << closestDate << " => " << amount << " = " << amount * closestRate
            << "\n";
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

bool BitcoinExchange::isValidValue(double value) const {
  if (value > 1000 || value < 0) {
    std::cerr << "Value out of range: " << value << "\n";
    return false;
  } else {
    return true;
  }
}
