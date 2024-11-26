#include <BitcoinExchange.hpp>

BitcoinExchange::BitcoinExchange(void) {
  std::cout << "Default constructor called\n";
}

BitcoinExchange::~BitcoinExchange(void) {
  std::cout << "Deconstructor called\n";
}

void BitcoinExchange::printRate(const std::string &date, double amount) const {
  if (!isValidValue(amount)) {
    return;
  } else {
    auto it = data.upper_bound(date);
    if (it == data.begin()) {
      std::cerr << "No date found: " << date << "\n";
      return;
    } else {
      auto [targetDate, targetRate] = *(--it);
      std::cout << targetDate << " => " << amount << " = "
                << amount * targetRate << "\n";
    }
  }
}

void BitcoinExchange::printRates(const std::string &fileName) {
  parseFile(fileName, '|', [this](const std::string &date, double amount) {
    printRate(date, amount);
  });
}

void BitcoinExchange::importInfo(const std::string &date, double amount) {
  data.emplace(date, amount);
}

void BitcoinExchange::importData(const std::string &fileName) {
  parseFile(fileName, ',', [this](const std::string &date, double amount) {
    importInfo(date, amount);
  });
}

void BitcoinExchange::parseFile(
    const std::string &fileName, char delim,
    const std::function<void(const std::string &, double)> &append_or_print) {
  std::ifstream input(fileName);
  std::string line, date, value;
  if (input.is_open()) {
    std::getline(input, line); // header
    while (std::getline(input, line)) {
      std::istringstream readLine(line);
      if (!std::getline(readLine, date, delim) ||
          !std::getline(readLine, value)) {
        std::cerr << "Invalid line format: " << line << "\n";
      } else if (isValidDate(trimWhiteSpace(date))) {
        try {
          double amount = std::stod(trimWhiteSpace(value));
          append_or_print(date, amount);
        } catch (const std::invalid_argument &e) {
          std::cerr << "Invalid argument: " << value << "\n";
        } catch (const std::out_of_range &e) {
          std::cerr << "Out of range: " << value << "\n";
        }
      }
    }
    input.close();
  } else {
    throw std::runtime_error("Failed to open file: " + fileName);
  }
}

std::string BitcoinExchange::trimWhiteSpace(std::string &str) const {
  str = std::regex_replace(str, std::regex("^[ \t]+|[ \t]+$"), "");
  return str;
}

bool BitcoinExchange::isValidDate(const std::string &date) const {
  std::regex pattern(R"((\d{4})-(\d{2})-(\d{2}))");
  if (!std::regex_match(date, pattern)) {
    std::cerr << "Invalid date format: " << date << "\n";
    return false;
  } else {
    return true;
  }
}

bool BitcoinExchange::isValidValue(double amount) const {
  if (amount > 1000 || amount < 0) {
    std::cerr << "Amount out of range: " << amount << "\n";
    return false;
  } else {
    return true;
  }
}
