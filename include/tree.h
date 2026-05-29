// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMTree {
 public:
  struct Node {
    char sym;
    std::vector<Node*> links;
    explicit Node(char s) : sym(s) {}
  };

  Node* top;
  std::vector<char> base;

  explicit PMTree(const std::vector<char>& src);
  ~PMTree();

  PMTree(const PMTree&) = delete;
  PMTree& operator=(const PMTree&) = delete;

 private:  // NOLINT
  Node* BuildSubtree(const std::vector<char>& rest);
  void Cleanup(Node* ptr);
};

std::vector<std::vector<char>> getAllPerms(PMTree& obj);
std::vector<char> getPerm1(PMTree& obj, int pos);
std::vector<char> getPerm2(PMTree& obj, int pos);
size_t fact(int n);

#endif  // INCLUDE_TREE_H_
