#include <PmergeMe.hpp>

std::vector<int> PmergeMe::intVector;
std::list<int> PmergeMe::intList;
std::chrono::time_point<std::chrono::high_resolution_clock> PmergeMe::timer;

void PmergeMe::fordJohnsonSort(int argc, char **argv) {
  ParseArguments(argc, argv);
  startTimer();
  sortNumbers();
}

void PmergeMe::ParseArguments(int argc, char **argv) {
  std::vector<std::string> args(argv + 1, argv + argc);
  std::unordered_set<int> uniques;
  for (const auto &str : args) {
    int number = std::stoi(str);
    if (number < 0) {
      throw std::invalid_argument("Negative number");
    } else if (!uniques.insert(number).second) {
      throw std::invalid_argument("Duplicate number");
    } else {
      intVector.push_back(number);
    }
  }
  if (intVector.size() <= 1) {
    throw std::invalid_argument("Not enough numbers");
  }
}

void PmergeMe::sortNumbers() {
  auto mid = intVector.begin() + 1;
  std::vector<int> unsorted(mid, intVector.end());
  intVector.erase(mid, intVector.end());
  for (const auto &elem : unsorted) {
    auto pos = std::lower_bound(intVector.begin(), intVector.end(), elem);
    intVector.insert(pos, elem);
  }
}

void PmergeMe::startTimer() { timer = Clock::now(); }

void PmergeMe::printDuration() {
  auto endTime = Clock::now();
  auto duration = std::chrono::duration_cast<ms>(endTime - timer);
  std::cout << "Time to process a range of " << intVector.size()
            << " elements with " << "std::vector"
            << " : " << duration.count() << " μs\n";
}

void PmergeMe::displayNumbers() {
  for (const auto &num : intVector) {
    std::cout << num << " ";
  }
  std::cout << std::endl;
}
