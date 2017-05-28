#include <iostream>
#include "Node.h"
#include <windows.h>
using namespace std;

/*
a red and black tree is a binary search tree that satisfies the ff
1) a node is either red or black
2) the root is black
3) all leaves (NULL) are black
4) if a node is red, then both its children are black
5) every path from any node to any of its leaf descendants contain the same
    number of black nodes
*/

void printTree(Node*& tree, int indent);
Node* insertNode(Node*& tree, int val);
void updateParents(Node*& node);
void deleteNode(Node*& tree, int val);
void deleteCase2(Node*& tree, int val);
void deleteCase3(Node*& tree, int val);
Node* inOrderSuccessor(Node*& node);
Node* inOrderPredecessor(Node*& node);
void validate(Node*& node, Node*& tree);
void validatecase2(Node*& node, Node*& tree);
void validatecase3(Node*& node, Node*& tree);
void validatecase4(Node*& node, Node*& tree);
void validatecase5(Node*& node, Node*& tree);
void rotate(Node*& root, int direction);
Node* search(Node*& tree, int value);
void DBCase1(Node*& tree, Node*& node);
void DBCase2(Node*&tree, Node*& node);
void DBCase3(Node*& tree, Node*& node);

// saves the most recently added node
Node* bago = NULL;

int main() {
  Node* tree = NULL;
  int choice = 0;
  while (choice != 4) {
    //system("cls");
    printTree(tree, 0);
    cout << "Menu:" << endl;
    cout << "[1] Insert Node" << endl;
    cout << "[2] Delete Node" << endl;
//    cout << "[3] Rotate Node (for debugging lmao)" << endl;
    cout << "[4] Exit" << endl;
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1) {
      cout << "Enter new node value: ";
      int temp;
      cin >> temp;
      insertNode(tree, temp);
      updateParents(tree);
      validate(bago, tree);
    }
    if (choice == 2) {
      cout << "Pick a node to delete: ";
      int temp;
      cin >> temp;
      deleteNode(tree, temp);
    }
    if (choice == 3) {
      /*int nodeNum;
      int direction;
      cout << "Pick a node to rotate: ";
      cin >> nodeNum;
      cout << "Pick a direction to rotate (-1 or 1): ";
      cin >> direction;
      Node* root = search(tree, nodeNum);
      /*if (root == tree) rotate(tree, direction);
      else rotate(root, direction);*/
      continue;
    }
  }
}

void deleteNode(Node*& tree, int val) {
  Node* node = search(tree, val);
  // if the node does not exist then nothing needs to be deleted
  if (!node) return;
  cout << "attempting to delete " << node->value << endl;
  // if the node is a leaf then just remove it
  if (node->left == NULL && node->right == NULL) {
    cout << node->value << " has no children" << endl;
    Node* parent = node->parent;
    char childStatus = node->child();
    if (node == tree) {
      delete tree;
      tree = NULL;
    }
    else {
      delete node;
      node = NULL;
    }
    if (parent) {
      if (childStatus == 'l') parent->left = NULL;
      else parent->right = NULL;
    }
  } else {
    // node has more than 0 children
    cout << "case 2" << endl;
    deleteCase2(tree, val);
  }
}

void deleteCase2(Node*& tree, int val) {
  Node* node = search(tree, val);
  if (node->left == NULL) {
    if (node->right->color == 'r' || node->color == 'r') {
      if (node == tree) {
        tree = node->right;
        tree->color = 'b';
        tree->parent = NULL;
      } else {
        Node* parent = node->parent;
        if (node->child() == 'l') {
          parent->left = node->left;
          parent->left->color = 'b';
        } else {
          parent->right = node->right;
          parent->right->color = 'b';
        }
        delete node;
      }
    }
  } else if (node->right == NULL) {
    if (node->left-> color == 'r' || node->color == 'r') {
      if (node == tree) {
        tree = node->left;
        tree->color = 'b';
        tree->parent = NULL;
      } else {
        Node* parent = node->parent;
        if (node->child() == 'l') {
          parent->left = node->left;
          parent->left->color = 'b';
        } else {
          parent->right = node->right;
          parent->right->color = 'b';
        }
        delete node;
      }
    }
  } else {
    // node has more than 1 child
    cout << "case 3" << endl;
    deleteCase3(tree, val);
  }
}

// returns the left most node of the a node's right subtree
Node* inOrderSuccessor(Node*& node) {
  Node* cursor = node;
  cursor = cursor->right;
  if (!cursor) return NULL;
  while (cursor->left != NULL) {
    cursor = cursor->left;
  }
  return cursor;
}

// returns the right most node of a node's left subtree
Node* inOrderPredecessor(Node*& node) {
  Node* cursor = node;
  cursor = cursor->left;
  if (!cursor) return NULL;
  while (cursor->right != NULL) {
    cursor = cursor->right;
  }
  return cursor;
}

void deleteCase3(Node*& tree, int val) {
  Node* node = search(tree, val);
  Node* succ = inOrderSuccessor(node);

  if (!succ) succ = inOrderPredecessor(node);

  cout << succ->value << " is " << node->value << "'s next value" << endl;
  
  Node* parent = succ->parent;
  Node* nParent = node->parent;
  char nStat = node->child();
  char stat = succ->child();

  /*if(node->right->hasChildren())
  {
      cout << "RIGHT SDADS" << endl;
  }
    if(!node->right->hasChildren() && !node->left->hasChildren() || succ->color == 'r')
    {*/
      if (succ->left) cout << succ->value << "->left is currently " << succ->left->value << endl;
      else cout <<succ->value << "->left is currently NULL" << endl;
      if (node->left) cout << "it will be changed to " << node->left->value << endl;
      else cout << "it will be changed to NULL" << endl;
      if (node->left != succ) succ->left = node->left;
      if (succ->left) cout << succ->value << "->left is now " << succ->left->value << endl;
      else cout << succ->value << "->left is now NULL" << endl;

      if (succ->right) cout << succ->value << "->right is currently " << succ->right->value << endl;
      else cout << succ->value << "->right is currently NULL" << endl;
      if (node->right) cout << "it will be changed to " << node->right->value << endl;
      else cout << "it will be changed to NULL" << endl;
      if (node->right != succ) succ->right = node->right;
      if (succ->right) cout << succ->value << "->left is now " << succ->right->value << endl;
      else cout << succ->value << "->left is now NULL" << endl;

      succ->parent = nParent;
      succ->color = node->color;


      if (nParent != NULL) {
	if (nStat == 'l') nParent->left = succ;
	else if (nStat == 'r') nParent->right = succ;
      }
      if (parent) {
	if (stat == 'l') parent->left = NULL;
	else if (stat == 'r') parent->right = NULL;
      }
      if (tree == node) tree = succ;
      else delete node;
      
      if(succ->hasChildren())
      {
	if(succ->color == 'r')
	{
	    if(succ->right != NULL && succ->left != NULL)
	    {
		if(succ->left->color != succ->right->color)
		{
		    succ->left->color = 'b';
		    succ->right->color = 'b';
		}
	    }	
	}
      }
  //}

  /*if(node->color == 'b')
  {
      cout << "Checking for DB" << endl;
      DBCase1(tree,node);
  }*/

}

// rotates a node in a certain direction
void rotate(Node*& root, int direction) {
  // save original child status (whether it's a left or right child)
  // save original parent
  Node* ogParent = root->parent;
  char ogChildStatus = root->child();
  if (direction == 1) { // right rotation
    // assigns pivot to child opposite of rotation
    Node* pivot = root->left;
    // abort if pivot does not exist
    if (!pivot) return;
    // child opposite of rotation is changed to pivot's child in the direction
    // of rotation
    root->left = pivot->right;
    // pivot's child in the direction of rotation is changed to root node
    pivot->right = root;
    // update parents
    root->parent = pivot;
    pivot->parent = ogParent;
    // update pivot to take the place of root
    root = pivot;
    // update parent to point to root nodes replacement
    if (ogParent) {
      if (ogChildStatus == 'r') ogParent->right = pivot;
      else if (ogChildStatus == 'l') ogParent->left = pivot;
    }
  } else {
    Node* pivot = root->right;
    if (!pivot) return;
    root->right = pivot->left;
    pivot->left = root;
    root->parent = pivot;
    pivot->parent = ogParent;
    root = pivot;
    if (ogParent) {
      if (ogChildStatus == 'r') ogParent->right = pivot;
      else if (ogChildStatus == 'l') ogParent->left = pivot;
    }
  }
}

// updates the parents of a node's children to point to itself
void updateParents(Node*& node) {
  if (!node) return;
  // updates the children of the node's children as well (if they exist)
  if (node->left) {
    node->left->parent = node;
    updateParents(node->left);
  }
  if (node->right) {
    node->right->parent = node;
    updateParents(node->right);
  }
}

// inserts a new node BST style
Node* insertNode(Node*& tree, int val) {
  bago = new Node(val, 'r');

  if (!tree) {
    tree = bago;
  } else if (val < tree->value) {
    tree->left = insertNode(tree->left, val);
    tree->left->parent = tree;
  } else {
    tree->right = insertNode(tree->right, val);
    tree->right->parent = tree;
  }
  return tree;
}

// validates the node's color in relation to its relatives
void validate(Node*& node, Node*& tree) {
  if (node->parent) {
    cout << "case 2" << endl;
    // if it has a parent(not the root node) go to case 2
    validatecase2(node, tree);
  } else {
    // if its the root node, color it black
    node->color = 'b';
  }
}

void validatecase2(Node*& node, Node*& tree) {
  if (node->parent->color == 'b') {
    // if its parent is black then no violations are committed
    return;
  } else {
    cout << "case 3" << endl;
    // otherwise go to case 3
    validatecase3(node, tree);
  }
}

void validatecase3(Node*& node, Node*& tree) {
  Node* uncle = node->uncle();
  // if the node has an uncle and it is red
  if ((uncle != NULL) && (uncle->color == 'r')) {
    // change the node's parent and the node's uncle to black
    node->parent->color = 'b';
    uncle->color = 'b';
    // change the node's grandparent to red
    Node* grandpa = node->grandParent();
    grandpa->color = 'r';
    // validate the grandparent
    validate(grandpa, tree);
  } else {
    //printTree(tree, 0);
    cout << "case 4" << endl;
    // otherwise go to case 4
    validatecase4(node, tree);
  }
}

void validatecase4(Node*& node, Node*& tree) {
  Node* nodeParent = node->parent;
  // if the node is a right child and the parent is a left child
  /* i.e.
  g        g
   \      /
    p or p
   /      \
  n        n
  */
  if ((node->child() == 'r') && (node->parent->child() == 'l')) {
    // rotate the parent to the direction opposite of the node
    /*becomes
    g            g
     \          /
      n   or   n
       \      /
        p    p
    */
    if (nodeParent == tree) rotate(tree, -1);
    else rotate(nodeParent, -1);
    // evaluate the oldParent node
    node = node->left;
  } else if ((node->child() == 'l') && (node->parent->child() == 'r')) {
    if (nodeParent == tree) rotate(tree, 1);
    else rotate(nodeParent, 1);
    node = node->right;
  }
  //printTree(tree, 0);
  cout << "case 5" << endl;
  // go to case 5 regardless if that above rotation was made or not
  validatecase5(node, tree);
}

void validatecase5(Node*& node, Node*& tree) {
  Node* grandpa = node->grandParent();
  // change parent's color to black
  node->parent->color = 'b';
  // change grandpa's color to red
  grandpa->color = 'r';
  if (node->child() == 'l') {
    // rotate grandpa to the opposite direction of its childness(? left or right child)
    if (grandpa == tree) rotate(tree, 1);
    else rotate(grandpa, 1);
  } else {
    if (grandpa == tree) rotate(tree, -1);
    else rotate(grandpa, -1);
  }
  /* i.e
  g                p
   \              / \
    p   becomes  g   n
     \
      n
  */
}

// searches the tree for a node with a given value and returns it
Node* search(Node*& tree, int value) {
  if (!tree) return NULL;
  if (tree->value == value) return tree;
  if (value < tree->value) return search(tree->left, value);
  if (value > tree->value) return search(tree->right, value);
}

// prints the tree with root on the left expanding to the right
/*i.e.
         a
    c
         a
r
    c
*/
void printTree(Node*& tree, int indent) {
  if (tree == NULL) return;
  if (tree != NULL) {
    if (tree->right) printTree(tree->right, indent + 4);
    for (int i = 0; i < indent; i++) {
      cout << " ";
    }
    if (tree->color == 'r') {
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0c);
    } else {
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
    }
    cout << tree->value;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
    // if (tree->parent) cout << "<-" << tree->parent->value;
    cout << endl;
    if (tree->left) printTree(tree->left, indent + 4);
  }
}

/*
 * for db cases, checks which db case it is
 */
void DBCase1(Node*& tree,Node*& node)
{
    Node* succ = inOrderSuccessor(node);
    if(node->parent == NULL)
    {
	return;
    }
    else 
	DBCase2(tree, node);
}

void DBCase2(Node*&tree, Node*& node)
{
    
    if(node->sibling())
    {
	if(node->sibling()->color == 'r' )
	{
	    if(node->child() == 'l')
	    {
		cout << "LEFT BITCH";
		node->parent->color = 'r';
		node->sibling()->color = 'b';
		tree->parent = tree->right;
		tree->right->left = tree;
		tree = tree->right;
		tree->parent = NULL;
		tree->left->left = node;
		if(tree->right->left != NULL)
		    tree->left->right = tree->right->left;
	    }
	    else
	    {
		cout << "RIGHT BITCH";
		node->parent->color = 'r';
		node->sibling()->color = 'b';
		tree->parent = tree->left;
		tree->left->right= tree;
		tree = tree->left;
		tree->parent = NULL;
		tree->right->right= node;
		if(tree->left->right!= NULL)
		    tree->right->left= tree->left->right;
	    }
	}
    
    DBCase3(tree, node);
    }
}

void DBCase3(Node*& tree, Node*& node)
{
    if(node->parent->color == 'b' 
	    && node->sibling()->color == 'b'
	    && node->sibling()->left->color == 'b'
	    && node->sibling()->right->color == 'b'
	    )
    {
	node->sibling()->color = 'r';
    }
}
