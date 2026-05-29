// Copyright 2022 NNTU-CS
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include "tree.h"

void PrintSequence(const std::vector<char>& seq) {
  for (char c : seq) {
    std::cout << c;
  }
}

int main() {
 
  std::vector<char> demo_input = { '1', '2', '3' };
  PMTree demo_tree(demo_input);

  std::cout << "All permutations for {1,2,3}:\n";
  auto all_results = GetAllPermutations(demo_tree);
  for (const auto& perm : all_results) {
    PrintSequence(perm);
    std::cout << "  ";
  }
  std::cout << "\n\n";

  std::cout << "Permutation #1 (slow): ";
  PrintSequence(GetPermutationByIndexSlow(demo_tree, 1));
  std::cout << "\n";

  std::cout << "Permutation #2 (fast): ";
  PrintSequence(GetPermutationByIndexFast(demo_tree, 2));
  std::cout << "\n\n";

  std::cout << "n;getAllPerms(s);getPerm1(s);getPerm2(s)\n";

  for (int alphabet_size = 3; alphabet_size <= 8; ++alphabet_size) {
    std::vector<char> input_chars;
    for (int i = 0; i < alphabet_size; ++i) {
      input_chars.push_back(static_cast<char>('a' + i));
    }
    PMTree benchmark_tree(input_chars);

    std::mt19937 rng_engine(42);
    std::uniform_int_distribution<> dist(1, static_cast<int>(CalculateFactorial(alphabet_size)));
    int random_index = dist(rng_engine);

    auto start_all = std::chrono::high_resolution_clock::now();
    GetAllPermutations(benchmark_tree);
    auto end_all = std::chrono::high_resolution_clock::now();

    auto start_slow = std::chrono::high_resolution_clock::now();
    GetPermutationByIndexSlow(benchmark_tree, random_index);
    auto end_slow = std::chrono::high_resolution_clock::now();

    auto start_fast = std::chrono::high_resolution_clock::now();
    GetPermutationByIndexFast(benchmark_tree, random_index);
    auto end_fast = std::chrono::high_resolution_clock::now();

    double time_all = std::chrono::duration<double>(end_all - start_all).count();
    double time_slow = std::chrono::duration<double>(end_slow - start_slow).count();
    double time_fast = std::chrono::duration<double>(end_fast - start_fast).count();

    std::cout << alphabet_size << ";"
      << std::fixed << std::setprecision(6) << time_all << ";"
      << time_slow << ";"
      << time_fast << std::endl;
  }

  return 0;
}
