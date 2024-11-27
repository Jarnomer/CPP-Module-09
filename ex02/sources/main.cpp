#include <PmergeMe.hpp>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "usage: ./PmergeMe <numbers>";
    return 1;
  } else {
    try {
      PmergeMe::fordJohnsonSort(argc, argv);
      // PmergeMe::displayNumbers();
      PmergeMe::printDuration();
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << "\n";
    }
  }
  return 0;
}
