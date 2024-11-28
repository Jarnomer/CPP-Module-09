#include <PmergeMe.hpp>

std::vector<int> PmergeMe::intVector;
std::list<int> PmergeMe::intList;
std::string PmergeMe::containerType;

std::chrono::time_point<std::chrono::high_resolution_clock> PmergeMe::timer;

std::vector<int> PmergeMe::getIntVector(void) {
  containerType = "std::vector";
  return intVector;
}
std::list<int> PmergeMe::getIntList(void) {
  containerType = "std::list";
  return intList;
}

void PmergeMe::startTimer() { timer = Clock::now(); }
