#include <RPN.hpp>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "usage: ./RPN <expression>";
    return 1;
  } else {
    try {
      RPN::calculate(argv[1]);
    } catch (const std::exception &e) {
      std::cerr << "Exception occured: " << e.what() << "\n";
    }
  }
  return 0;
}
