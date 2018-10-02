//	Authors: Joel Beckmeyer, Daniel Parker
//	Date: 2018-09-22
//	Purpose: To test the BinarySearchTree and BNode classes

#include "BinarySearchTree.h"
#include "RedBlackTree.h"
#include "BNode.h"
#include "RBNode.h"
#include <stdio.h>
#include <cstddef>
#include <iostream>
#include <string>
#include <limits>

using namespace std;

bool propertyOne(RBNode<int> * subTree);
bool propertyFour(RBNode<int> * subTree);
int propertyFive(RBNode<int> * subTree);
string isRedBlack(RedBlackTree<int> * tree);
void BSTTest(BinarySearchTree<int> * tree);
void RBTTest(RedBlackTree<int> * tree);




int main() {
	int response = 0;
	while (response != 3) {
		cout << "Which type of tree would you like to test? BSTree(0), RBTree(1), Input/Output Tests(2), or Exit(3)\n";
		cin >> response;
		if (response == 0) {
			BinarySearchTree<int> bsTree;
			cout << "Usage: \n";
			cout << " - Insert: Use a positive integer\n";
			cout << " - Remove: Use a negative integer\n";
			cout << " - Exit: Use zero\n";
			response = 1;
			while (response != 0) {
				cout << "Input: ";
				cin >> response;
				if (response > 0) {
					bsTree.insertNode(bsTree.getRoot(), response);
				}
				else if (response < 0) {
					bsTree.removeNode(bsTree.getRoot(), bsTree.search(bsTree.getRoot(), -response));
				}
				bsTree.print(bsTree.getRoot(), 0);
			}
		}
		else if (response == 1) {
			RedBlackTree<int> rbTree;
			cout << "Usage: \n";
			cout << " - Insert: Use a positive integer\n";
			cout << " - Remove: Use a negative integer\n";
			cout << " - Exit: Use zero\n";
			response = 1;
			while (response != 0 && isRedBlack(&rbTree).size() == 0) {
				cout << "Input: ";
				cin >> response;
				if (response > 0) {
					rbTree.insertNode(rbTree.getRoot(), response);
				}
				else if (response < 0) {
					rbTree.removeNode(rbTree.getRoot(), rbTree.search(rbTree.getRoot(), -response));
				}
				rbTree.print(rbTree.getRoot(), 0);
			}
			cout << isRedBlack(&rbTree) << endl;
		}
		else if (response == 2) {
			response = 0;
			while (response != 2) {
				cout << "Would you like to see the BinarySearchTree Test(0), the RedBlackTree Test(1), or Exit(2)?" << endl;
				cin >> response;
				if (response == 0) {
					BinarySearchTree<int> bsTree;
					BSTTest(&bsTree);
				}
				else if (response == 1) {
					RedBlackTree<int> rbTree;
					RBTTest(&rbTree);
				}
			}
		} 
		else if(response == 3) {
			cout << "Thanks for testing the code.\n";
		}
		else {
			cout << "That was not a valid input.\n";
		}
		cout << flush;
	}


	return 0;
}

string isRedBlack(RedBlackTree<int> *tree) {
	// property 1
	if (!propertyOne(tree->getRoot())) {
		return "Property 1: not every node is red or black";
	}
	// property 2
	if (tree->getRoot()->getColor() != BLACK) {
		return "Property 2: root node is not black";
	}

	// property 3
	if (tree->getRoot()->getParent()->getColor() != BLACK) {
		return "Property 3: every leaf is not black";
	}

	// property 4
	if (!propertyFour(tree->getRoot())) {
		return "Property 4: not every red node has both black children";
	}

	// property 5
	if (propertyFive(tree->getRoot()) == -1) {
		return "Property 5: black height of all paths is not equal";
	}
	return string();
}

bool propertyOne(RBNode<int> * subTree) {
	if (subTree->getKey() == NULL) {
		return true;
	}

	return propertyOne(subTree->getLeft()) && propertyOne(subTree->getRight())
		&& (subTree->getColor() == RED || subTree->getColor() == BLACK);
}

bool propertyFour(RBNode<int> * subTree) {
	if (subTree->getKey() == NULL) {
		return true;
	}

	if (subTree->getColor() == RED) {
		return subTree->getRight()->getColor() == BLACK
			&& subTree->getLeft()->getColor() == BLACK && propertyFour(subTree->getLeft())
			&& propertyFour(subTree->getRight());
	} else {
		return propertyFour(subTree->getLeft()) && propertyFour(subTree->getRight());
	}
}

int propertyFive(RBNode<int> * subTree) {
	if (subTree->getKey() == NULL) {
		return 1;
	}
	int leftHeight = propertyFive(subTree->getLeft());
	int rightHeight = propertyFive(subTree->getRight());

	if (leftHeight != rightHeight || leftHeight == -1 || rightHeight == -1) {
		return -1;
	} else if (subTree->getColor() == BLACK) {
		return 1 + leftHeight;
	} else {
		return leftHeight;
	}
}

void BSTTest(BinarySearchTree<int> * tree) {
	tree->insertNode(tree->getRoot(), 50);
	tree->insertNode(tree->getRoot(), 100);
	tree->insertNode(tree->getRoot(), 1);
	tree->insertNode(tree->getRoot(), 1);
	tree->insertNode(tree->getRoot(), 1);
	tree->insertNode(tree->getRoot(), 1);
	tree->insertNode(tree->getRoot(), 1);
	tree->insertNode(tree->getRoot(), 75);
	tree->insertNode(tree->getRoot(), 25);
	tree->insertNode(tree->getRoot(), 99);
	tree->print(tree->getRoot(), 0);
	cout << "\nInserting 80, 40, and 20:";
	tree->insertNode(tree->getRoot(), 80);
	tree->insertNode(tree->getRoot(), 40);
	tree->insertNode(tree->getRoot(), 20);
	cout << endl;
	tree->print(tree->getRoot(), 0);
	cout << "\nRemoving 1, 1, 75, and 98:";
	tree->removeNode(tree->getRoot(), tree->search(tree->getRoot(), 1));
	tree->removeNode(tree->getRoot(), tree->search(tree->getRoot(), 1));
	tree->removeNode(tree->getRoot(), tree->search(tree->getRoot(), 75));
	tree->removeNode(tree->getRoot(), tree->search(tree->getRoot(), 98));
	cout << endl;
	tree->print(tree->getRoot(), 0);
}

void RBTTest(RedBlackTree<int> * tree) {
	tree->insertNode(tree->getRoot(), 50);
	tree->insertNode(tree->getRoot(), 100);
	tree->insertNode(tree->getRoot(), 1);
	tree->insertNode(tree->getRoot(), 1);
	tree->insertNode(tree->getRoot(), 1);
	tree->insertNode(tree->getRoot(), 1);
	tree->insertNode(tree->getRoot(), 1);
	tree->insertNode(tree->getRoot(), 75);
	tree->insertNode(tree->getRoot(), 25);
	tree->insertNode(tree->getRoot(), 99);
	tree->print(tree->getRoot(), 0);
	cout << "\nInserting 80, 40, and 20:";
	tree->insertNode(tree->getRoot(), 80);
	tree->insertNode(tree->getRoot(), 40);
	tree->insertNode(tree->getRoot(), 20);
	cout << endl;
	tree->print(tree->getRoot(), 0);
	cout << "\nRemoving 1, 1, 75, and 98:";
	tree->removeNode(tree->getRoot(), tree->search(tree->getRoot(), 1));
	tree->removeNode(tree->getRoot(), tree->search(tree->getRoot(), 1));
	tree->removeNode(tree->getRoot(), tree->search(tree->getRoot(), 75));
	tree->removeNode(tree->getRoot(), tree->search(tree->getRoot(), 98));
	cout << endl;
	tree->print(tree->getRoot(), 0);
}
