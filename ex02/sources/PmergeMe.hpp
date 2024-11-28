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
  typedef std::chrono::microseconds us;

private:
  static std::vector<int> intVector;
  static std::list<int> intList;
  static std::string containerType;
  static timePoint timer;

public: // constructors
  PmergeMe(void) = delete;
  PmergeMe(const PmergeMe &other) = delete;
  PmergeMe &operator=(const PmergeMe &other) = delete;
  ~PmergeMe(void) = delete;

public: // getters
  static std::vector<int> getIntVector(void);
  static std::list<int> getIntList(void);

private: // utilities
  static void startTimer(void);
  static void printDuration(void);

public: // algorithm template
  template <typename T>
  static void fordJohnsonSort(int argc, char **argv, T container) {
    startTimer();
    parseArguments(argc, argv, container);
    displayNumbers("Before", container);
    sortNumbers(container);
    displayNumbers("After", container);
    printDuration(container);
  }

private: // parse template
  template <typename T>
  static void parseArguments(int argc, char **argv, T &container) {
    std::vector<std::string> args(argv + 1, argv + argc);
    std::unordered_set<int> uniques;
    for (const auto &str : args) {
      int number = std::stoi(str);
      if (number < 0) {
        throw std::invalid_argument("Negative number");
      } else if (!uniques.insert(number).second) {
        throw std::invalid_argument("Duplicate number");
      } else {
        container.push_back(number);
      }
    }
    if (container.size() <= 1) {
      throw std::invalid_argument("Not enough numbers");
    }
  }

private: // sort template
  template <typename T> static void sortNumbers(T &container) {
    auto mid = std::next(container.begin(), 1);
    T unsorted(mid, container.end());
    container.erase(mid, container.end());
    for (const auto &elem : unsorted) {
      auto pos = std::lower_bound(container.begin(), container.end(), elem);
      container.insert(pos, elem);
    }
  }

private: // duration template
  template <typename T> static void printDuration(const T &container) {
    auto endTime = Clock::now();
    auto duration = std::chrono::duration_cast<us>(endTime - timer);
    std::cout << "Time to process a range of " << container.size()
              << " elements with " << containerType << " : " << duration.count()
              << " μs" << std::endl;
  }

public: // print template
  template <typename T>
  static void displayNumbers(const std::string &tag, const T &container) {
    std::cout << tag << " : ";
    for (const auto &num : container) {
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }
};
