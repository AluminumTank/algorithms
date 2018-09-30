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

using namespace std;

bool propertyOne(RBNode<int> * subTree);
bool propertyFour(RBNode<int> * subTree);
int propertyFive(RBNode<int> * subTree);

int main() {
	BinarySearchTree<int> tree;

	// test insert & search
	BNode<int> * root = tree.getRoot();
	tree.insertNode(root, 64);
	if(tree.search(root, 64) == NULL) {
		printf("insert failed\n");
	}
	else {
		printf("Insert succeded\n");
	}

	// test search
	if(tree.search(root, 102) != tree.getSentinel()) {
		printf("search failed\n");
	}
	else {
		printf("search succeded\n");
	}

	RedBlackTree<int> rbTree;
	int tmp = 1;
	while (isRedBlack(rbTree) == "", tmp != 0) {
		cout << "Enter an integer: ";
		cin >> tmp;
		// if number is greater than 0, we insert it; if it is less than zero, we
		// remove the corresponding node that has value of |tmp|
		if (tmp > 0) {
			rbTree.insertNode(rbTree.getRoot(), tmp);
		} else if (tmp < 0) {
			rbTree.removeNode(rbTree.search(rbTree.getRoot(), -tmp));
		}
	}

	cout << isRedBlack(rbTree);

	return 0;
}

string isRedBlack(RedBlackTree<int> tree) {
	// property 1
	if (!propertyOne(tree.getRoot())) {
		return "Property 1: not every node is red or black";
	}
	// property 2
	if (tree.getRoot()->getColor() != BLACK) {
		return "Property 2: root node is not black";
	}

	// property 3
	if (tree.getRoot()->getParent()->getColor() != BLACK) {
		return "Property 3: every leaf is not black";
	}

	// property 4
	if (!propertyFour(tree.getRoot())) {
		return "Property 4: not every red node has both black children";
	}

	// property 5
	if (propertyFive(tree.getRoot() == -1)) {
		return "Property 5: black height of all paths is not equal";
	}
	return "";
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
