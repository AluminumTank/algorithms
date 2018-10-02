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

using namespace std;

bool propertyOne(RBNode<int> * subTree);
bool propertyFour(RBNode<int> * subTree);
int propertyFive(RBNode<int> * subTree);
string isRedBlack(RedBlackTree<int> * tree);


int main() {
	BinarySearchTree<int> tree;

	// test insert & search
	tree.insertNode(tree.getRoot(), 64);
	if(tree.search(tree.getRoot(), 64) == NULL) {
		printf("insert failed\n");
	}
	else {
		printf("Insert succeded\n");
	}

	// test search
	if(tree.search(tree.getRoot(), 102) != tree.getSentinel()) {
		printf("search failed\n");
	}
	else {
		printf("search succeded\n");
	}

	//for (int i = 0; i < 100; ++i) {
	//	
	//	if (i % 2 == 0) {
	//		tree.insertNode(tree.getRoot(), i / 2);
	//	}
	//	else {
	//		tree.insertNode(tree.getRoot(), -i / 2);
	//	}
	//	//tree.insertNode(tree.getRoot(), 20 - i);
	//}
	//

	//tree.print(tree.getRoot(), 0);

	RedBlackTree<int> rbTree;
	rbTree.insertNode(rbTree.getRoot(), 20);
	rbTree.insertNode(rbTree.getRoot(), 10);
	rbTree.insertNode(rbTree.getRoot(), 30);
	rbTree.insertNode(rbTree.getRoot(), 1);
	rbTree.insertNode(rbTree.getRoot(), 15);
	rbTree.insertNode(rbTree.getRoot(), 25);
	rbTree.insertNode(rbTree.getRoot(), 40);
	rbTree.insertNode(rbTree.getRoot(), 16);
	rbTree.insertNode(rbTree.getRoot(), 26);
	rbTree.print(rbTree.getRoot(), 0);
	int tmp = 1;
	while (isRedBlack(&rbTree).size() == 0 && tmp != 0) {
		cout << "Enter an integer: ";
		cin >> tmp;
		// if number is greater than 0, we insert it; if it is less than zero, we
		// remove the corresponding node that has value of |tmp|
		if (tmp > 0) {
			rbTree.insertNode(rbTree.getRoot(), tmp);
		} else if (tmp < 0) {
			rbTree.removeNode(rbTree.getRoot(), rbTree.search(rbTree.getRoot(), -tmp));
		}
		cout << endl;
		rbTree.print(rbTree.getRoot(), 0);
	}

cout << isRedBlack(&rbTree);
	string a;
	getline(cin, a);
	cout << a;
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
