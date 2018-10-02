/**
 * SUMMARY: An implementation of a binary search tree.
 *
 * AUTHOR: Daniel Parker, Joel Beckmeyer
 * DATE: October 1, 2018
 *
**/

#ifndef _BINARYSEARCHTREE_H_
#define _BINARYSEARCHTREE_H_

#include "BNode.h"
#include <cstddef>
#include <iostream>

using namespace std;

template <class T>
class BinarySearchTree {
public:
	BinarySearchTree();
	~BinarySearchTree();

	BNode<T> * getMinimum(BNode<T> * subRoot);
	BNode<T> * getMaximum(BNode<T> * subRoot);
	BNode<T> * getSuccessor(BNode<T> * subRoot);
	BNode<T> * getPredecessor(BNode<T> * subRoot);
	BNode<T> * getRoot();
	BNode<T> * getSentinel();

	void insertNode(BNode<T> * subRoot, T val);
	BNode<T> * search(BNode<T> * subRoot, T Key);
	BNode<T> * removeNode(BNode<T> * subRoot, BNode<T> * val);
	void transplant(BNode<T> * candidate, BNode<T> * donor);
	void print(BNode<T> * subroot, int space);

protected:
	void insertNode(BNode<T> * subRoot, BNode<T> * z);
	BNode<T> * sentinel = new BNode<T>(NULL);
	BNode<T> * root = sentinel;
};



template<class T>
BinarySearchTree<T>::BinarySearchTree() {
	// set up the sentinel
	sentinel->setLeft(sentinel);
	sentinel->setParent(sentinel);
	sentinel->setRight(sentinel);
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree() {
	delete sentinel;
}

// to find minimum, we traverse the left sub-tree until we hit sentinel
template<class T>
BNode<T>* BinarySearchTree<T>::getMinimum(BNode<T> * subRoot) {
	BNode<T> * x = subRoot;
	while (x->getLeft() != sentinel) {
		x = x->getLeft();
	}
	return x;
}

// to find maximum, we traverse the right sub-tree until we hit sentinel
template<class T>
BNode<T>* BinarySearchTree<T>::getMaximum(BNode<T> * subRoot) {
	BNode<T> * x = subRoot;
	while (x->getRight() != sentinel) {
		x = x->getRight();
	}
	return x;
}

// returns the successor to a given node
template<class T>
BNode<T>* BinarySearchTree<T>::getSuccessor(BNode<T>* subRoot) {
	BNode<T> * x = subRoot;
	// if x has a right sub-tree, the successor is the minimum of that sub-tree
	if (x->getRight() != sentinel) {
		return getMinimum(x->getRight());
	}

	// otherwise, the successor is the parent of the first ancestor we encounter
	// that is a left child
	BNode<T> * y = x->getParent();
	while (y != sentinel && x == y->getLeft()) {
		x = y;
		y = y->getParent();
	}
	return y;
}

// returns the predecessor to a given node
template<class T>
BNode<T>* BinarySearchTree<T>::getPredecessor(BNode<T>* subRoot) {
	BNode<T> * x = subRoot;
	// if x has a left sub-tree, the predecessor is the maximum of that sub-tree
	if (x->getRight() != sentinel) {
		return x->getMaximum();
	}

	// otherwise, the successor is the parent of the first ancestor we encounter
	// that is a right child
	BNode<T> * y = x->getParent();
	while (y != sentinel && x != y->getRight()) {
		x = y;
		y = y->getParent();
	}
	return y;
}

// returns the root node
template<class T>
BNode<T>* BinarySearchTree<T>::getRoot() {
	return root;
}

// returns the sentinel node (T.nil)
template<class T>
BNode<T>* BinarySearchTree<T>::getSentinel() {
	return sentinel;
}

// this insert node is used by the user to pass a value to be inserted. This
// saves the user from having to construct a node.
template<class T>
void BinarySearchTree<T>::insertNode(BNode<T>* subRoot, T val) {
	BNode<T> * z = new BNode<T>(val);
	z->setRight(sentinel);
	z->setLeft(sentinel);
	z->setParent(sentinel);
	insertNode(subRoot, z);
}

// searches for a value in the tree. Returns sentinel if the value could not
// be found in a node
template<class T>
BNode<T>* BinarySearchTree<T>::search(BNode<T> * subRoot, T key) {
	BNode<T> * x = subRoot;
	// if we find the key or have hit the bottom of the tree, return
	if (x == sentinel || key == x->getKey()) {
		return x;
	}

	// otherwise, binary search for the value
	if (key < x->getKey()) {
		return search(x->getLeft(), key);
	}
	else {
		return search(x->getRight(), key);
	}
}

// removes the given node, and returns the child of y
template<class T>
BNode<T> * BinarySearchTree<T>::removeNode(BNode<T> * subRoot, BNode<T> * val) {
	if (val != sentinel) {
		BNode<T> * x;
		// case 1
		if (val->getLeft() == sentinel) {
			x = val->getRight();
			transplant(val, x);
		}
		// case 2
		else if (val->getRight() == sentinel) {
			x = val->getLeft();
			transplant(val, x);
		}
		else {
			BNode<T> * y = getMinimum(val->getRight());
			x = y->getRight();

			// case 4
			if (y->getParent() == val) {
				x->setParent(y);
			}
			else {
				transplant(y, y->getRight());
				y->setRight(val->getRight());
				y->getRight()->setParent(y);
			}

			// case 3
			transplant(val, y);
			y->setLeft(val->getLeft());
			y->getLeft()->setParent(y);
		}

		return x;
	}
	else {
		return sentinel;
	}
}

// this is a helper function for removeNode. It takes two nodes, removes one from
// the tree, and places the other in the place of the old one
template<class T>
void BinarySearchTree<T>::transplant(BNode<T> * candidate, BNode<T> * donor) {
	BNode<T> * parent = candidate->getParent();
	if (parent == sentinel) {
		root = donor;
	}
	// connect candidate parent and donor: determine whether candidate is left or right child
	else if (candidate == parent->getRight()) {
		parent->setRight(donor);
	}
	else {
		parent->setLeft(donor);
	}
	donor->setParent(parent);
}

// prints the tree values in a left-to-right style, with lines to indicate different
// levels of the tree. Root is at far left, leaves are at far right
template<class T>
void BinarySearchTree<T>::print(BNode<T>* subroot, int space) {
	if (subroot != sentinel) {
		print(subroot->getRight(), space + 1);
		for (int i = 0; i < space; i++) {
			cout << "   |";
		}
		cout << subroot->getKey() << endl;
		print(subroot->getLeft(), space + 1);
	}
}

// this insert node is used internally to insert an already constructed node
template<class T>
void BinarySearchTree<T>::insertNode(BNode<T>* subRoot, BNode<T> * z) {
	// if the tree is not empty
	if (root != sentinel) {
		BNode<T> * y = sentinel;
		BNode<T> * x = subRoot;
		// decend the tree until we hit a sentinel
		while (x != sentinel) {
			y = x;
			if (z->getKey() < x->getKey()) {
				x = x->getLeft();
			}
			else {
				x = x->getRight();
			}
		}

		// hook up z
		z->setParent(y);
		if (y == sentinel) {
			subRoot = z;
		}
		else if (z->getKey() < y->getKey()) {
			y->setLeft(z);
		}
		else {
			y->setRight(z);
		}
	}
	else {
		root = z;
		z->setParent(sentinel);
		z->setLeft(sentinel);
		z->setRight(sentinel);
	}
}

#endif
