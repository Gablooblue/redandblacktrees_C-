#include <iostream>
using namespace std;

class Node {
public:
  Node(int, char);
  Node(int, char, Node*, Node*, Node*);
  void printTree(Node*, int);
  Node* grandParent();
  Node* uncle();
  Node* sibling();
  Node* left;
  Node* right;
  Node* parent;
  char child();
  char color;
  int value;
  bool hasChildren();
};
