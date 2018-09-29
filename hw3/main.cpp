//	Authors: Joel Beckmeyer, Daniel Parker
//	Date: 2018-09-22
//	Purpose: To test the BinarySearchTree and BNode classes

#include "BinarySearchTree.h"
#include "BNode.h"
#include <stdio.h>
#include <cstddef>

using namespace std;

int main() {
	BinarySearchTree<int> tree;

	// test insert & search
	BNode<int> * root = tree.getRoot();
	tree.insertNode(root, 64);
	if(tree.search(root, 64) == NULL) {
		printf("insert failed");
	}

	// test search
	if(tree.search(root, 102) != tree.getSentinel()) {
		printf("search failed");
	}
}
