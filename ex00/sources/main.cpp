#include <BitcoinExchange.hpp>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: ./btc <filename>\n";
    return EXIT_FAILURE;
  } else {
    try {
      BitcoinExchange btc;
      btc.importData("data.csv");
      btc.printRates(argv[1]);
    } catch (const std::runtime_error &e) {
      std::cerr << "Runtime exception: " << e.what() << "\n";
    } catch (...) {
      std::cerr << "Unexpected exception occured!\n";
    }
  }
  return 0;
}
