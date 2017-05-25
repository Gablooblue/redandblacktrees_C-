#include <iostream>
#include "Node.h"
using namespace std;

// constructor using two givens, color and value
Node::Node(int val, char col) {
  left = NULL;
  right = NULL;
  parent = NULL;
  value = val;
  color = col;
}

// constructor using all givens
Node::Node(int val, char col, Node* kaliwa, Node* kanan, Node* magulang) {
  left = kaliwa;
  parent = magulang;
  right = kanan;
  value = val;
  color = col;
}

// returns which child of this object's parent is
char Node::child() {
  // no parent
  if (!parent) return 'n';
  // left child of its parent
  if (parent->left == this) return 'l';
  // right child of its parent
  else if (parent->right == this) return 'r';
}

// prints tree by printing its subtrees and its own value
void Node::printTree(Node* tree, int indent = 0) {
  // if tree is not empty
  if (tree != NULL) {
    // print right subtree w/ increased indent if it exists
    if (tree->right) printTree(tree->right, indent + 4);
    // print value of root node
    for (int i = 0; i < indent; i++) cout << " ";
    cout << tree->value << endl;
    // print left subtree if it exists
    if (tree->left) printTree(tree->left, indent + 4);
  }
}

// returns this Node's parent's parent
Node* Node::grandParent() {
  if (parent) {
    return parent->parent;
  } else return NULL;
}

// returns this Node's parent's sibling
Node* Node::uncle() {
  Node* grandpa = this->grandParent();
  if (grandpa == NULL) return NULL;
  if (parent == grandpa->left) return grandpa->right;
  else return grandpa->left;
}

// returns this Node's sibling
Node* Node::sibling() {
  // if this node does not have a parent then it does not have a sibling
  switch (this->child()) {
    case 'n': return NULL;
    break;
    case 'l': return parent->left;
    break;
    case 'r': return parent->right;
    break;
  }
}

bool Node::hasChildren()
{
    return(left != NULL || right != NULL);
}
