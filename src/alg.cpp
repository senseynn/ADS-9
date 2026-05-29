// Copyright 2022 NNTU-CS
#include <algorithm>
#include <cstdlib>
#include "tree.h"

PMTree::PMTree(const std::vector<char>& input_data) : source_elements(input_data) {
  root_node = new TreeNode(0);

  std::vector<char> sorted_input = input_data;
  std::sort(sorted_input.begin(), sorted_input.end());

  for (char current_char : sorted_input) {
    std::vector<char> remaining = sorted_input;
    auto it = std::find(remaining.begin(), remaining.end(), current_char);
    if (it != remaining.end()) {
      remaining.erase(it);
    }
    TreeNode* new_child = BuildSubtree(remaining);
    new_child->symbol = current_char;
    root_node->branches.push_back(new_child);
  }
}

PMTree::~PMTree() {
  CleanupTree(root_node);
}

PMTree::TreeNode* PMTree::BuildSubtree(const std::vector<char>& remaining) {
  if (remaining.empty()) {
    return new TreeNode(0);
  }

  TreeNode* current_node = new TreeNode(0);
  std::vector<char> sorted_remaining = remaining;
  std::sort(sorted_remaining.begin(), sorted_remaining.end());

  for (char ch : sorted_remaining) {
    std::vector<char> next_level = sorted_remaining;
    auto pos = std::find(next_level.begin(), next_level.end(), ch);
    if (pos != next_level.end()) {
      next_level.erase(pos);
    }
    TreeNode* child_node = BuildSubtree(next_level);
    child_node->symbol = ch;
    current_node->branches.push_back(child_node);
  }
  return current_node;
}

void PMTree::CleanupTree(TreeNode* node_ptr) {
  if (node_ptr == nullptr) {
    return;
  }
  for (TreeNode* child : node_ptr->branches) {
    CleanupTree(child);
  }
  delete node_ptr;
}

namespace {
  void DepthFirstCollect(PMTree::TreeNode* current,
    std::vector<char>& buffer,
    std::vector<std::vector<char>>& output,
    int current_depth,
    int target_depth) {
    if (current_depth == target_depth) {
      output.emplace_back(buffer);
      return;
    }
    for (PMTree::TreeNode* next_node : current->branches) {
      buffer.push_back(next_node->symbol);
      DepthFirstCollect(next_node, buffer, output, current_depth + 1, target_depth);
      buffer.pop_back();
    }
  }
}

std::vector<std::vector<char>> GetAllPermutations(PMTree& tree_obj) {
  std::vector<std::vector<char>> result_collection;
  std::vector<char> current_path;
  const int total_length = static_cast<int>(tree_obj.source_elements.size());

  for (PMTree::TreeNode* first_level : tree_obj.root_node->branches) {
    current_path.push_back(first_level->symbol);
    DepthFirstCollect(first_level, current_path, result_collection, 1, total_length);
    current_path.pop_back();
  }
  return result_collection;
}

std::vector<char> GetPermutationByIndexSlow(PMTree& tree_obj, int index) {
  auto all_variants = GetAllPermutations(tree_obj);
  if (index <= 0 || index > static_cast<int>(all_variants.size())) {
    return {};
  }
  return all_variants[index - 1];
}

size_t CalculateFactorial(int n) {
  size_t result = 1;
  for (int i = 2; i <= n; ++i) {
    result *= static_cast<size_t>(i);
  }
  return result;
}

std::vector<char> GetPermutationByIndexFast(PMTree& tree_obj, int index) {
  const int total_chars = static_cast<int>(tree_obj.source_elements.size());
  const size_t max_permutations = CalculateFactorial(total_chars);

  if (index <= 0 || static_cast<size_t>(index) > max_permutations) {
    return {};
  }

  std::vector<char> output_sequence;
  int offset = index - 1;
  PMTree::TreeNode* cursor = tree_obj.root_node;

  for (int position = 0; position < total_chars; ++position) {
    size_t block_size = CalculateFactorial(total_chars - position - 1);
    int branch_index = offset / static_cast<int>(block_size);
    offset %= static_cast<int>(block_size);

    if (branch_index >= static_cast<int>(cursor->branches.size())) {
      return {};
    }
    cursor = cursor->branches[branch_index];
    output_sequence.push_back(cursor->symbol);
  }
  return output_sequence;
}
