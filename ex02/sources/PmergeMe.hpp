#pragma once

#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <list>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

class PmergeMe {
private:
  typedef std::chrono::high_resolution_clock Clock;
  typedef std::chrono::time_point<Clock> timePoint;
  typedef std::chrono::microseconds ms;

private:
  static std::vector<int> intVector;
  static std::list<int> intList;
  static timePoint timer;

public: // constructors
  PmergeMe(void) = delete;
  PmergeMe(const PmergeMe &other) = delete;
  PmergeMe &operator=(const PmergeMe &other) = delete;
  ~PmergeMe(void) = delete;

public: // methods
  static void fordJohnsonSort(int argc, char **argv);
  static void displayNumbers(void);
  static void printDuration(void);

private: // utils
  static void ParseArguments(int argc, char **argv);
  static void startTimer(void);
  static void sortNumbers(void);
};
