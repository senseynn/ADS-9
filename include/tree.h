// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMTree {
public:
  struct TreeNode {
    char symbol;
    std::vector<TreeNode*> branches;
    explicit TreeNode(char val) : symbol(val) {}
  };

  TreeNode* root_node;
  std::vector<char> source_elements;

  explicit PMTree(const std::vector<char>& input_data);
  ~PMTree();

  PMTree(const PMTree&) = delete;
  PMTree& operator=(const PMTree&) = delete;

private:
  TreeNode* BuildSubtree(const std::vector<char>& remaining);
  void CleanupTree(TreeNode* node_ptr);
};

std::vector<std::vector<char>> GetAllPermutations(PMTree& tree_obj);
std::vector<char> GetPermutationByIndexSlow(PMTree& tree_obj, int index);
std::vector<char> GetPermutationByIndexFast(PMTree& tree_obj, int index);

size_t CalculateFactorial(int value);

#endif  // INCLUDE_TREE_H_
