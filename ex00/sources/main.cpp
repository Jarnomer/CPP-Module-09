#include <BitcoinExchange.hpp>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: ./btc <filename>\n";
    return 1;
  } else {
    try {
      BitcoinExchange btc;
      btc.importData("data.csv");
      btc.printRates(argv[1]);
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << "\n";
    }
  }
  return 0;
}
