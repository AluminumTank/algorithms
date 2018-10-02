/**
 * SUMMARY: An implementation of a binary search tree.
 *
 * AUTHOR: Daniel Parker
 * DATE: Sept 22, 2018
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
	void insertNode(BNode<T> * subRoot, T val);
	BNode<T> * removeNode(BNode<T> * subRoot, BNode<T> * val);
	BNode<T> * getMinimum(BNode<T> * subRoot);
	BNode<T> * getMaximum(BNode<T> * subRoot);
	BNode<T> * search(BNode<T> * subRoot, T Key);
	BNode<T> * getSuccessor(BNode<T> * subRoot);
	BNode<T> * getPredecessor(BNode<T> * subRoot);
	BNode<T> * getRoot();
	BNode<T> * getSentinel();
	void transplant(BNode<T> * candidate, BNode<T> * donor);
	void print(BNode<T> * subroot, int space);

protected:
	void insertNode(BNode<T> * subRoot, BNode<T> * z);
	BNode<T> * sentinel = new BNode<T>(NULL);
	BNode<T> * root = sentinel;
};



template<class T>
BinarySearchTree<T>::BinarySearchTree() {
	sentinel->setLeft(sentinel);
	sentinel->setParent(sentinel);
	sentinel->setRight(sentinel);
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree() {
	delete sentinel;
}

template<class T>
void BinarySearchTree<T>::insertNode(BNode<T>* subRoot, T val) {
	BNode<T> * z = new BNode<T>(val);
	z->setRight(sentinel);
	z->setLeft(sentinel);
	z->setParent(sentinel);
	insertNode(subRoot, z);
}


// returns the child of Y
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

template<class T>
BNode<T>* BinarySearchTree<T>::getMinimum(BNode<T> * subRoot) {
	BNode<T> * x = subRoot;
	while (x->getLeft() != sentinel) {
		x = x->getLeft();
	}
	return x;
}

template<class T>
BNode<T>* BinarySearchTree<T>::getMaximum(BNode<T> * subRoot) {
	BNode<T> * x = subRoot;
	while (x->getRight() != sentinel) {
		x = x->getRight();
	}
	return x;
}

template<class T>
BNode<T>* BinarySearchTree<T>::search(BNode<T> * subRoot, T key) {
	BNode<T> * x = subRoot;
	if (x == sentinel || key == x->getKey()) {
		return x;
	}

	if (key < x->getKey()) {
		return search(x->getLeft(), key);
	}
	else {
		return search(x->getRight(), key);
	}
}

template<class T>
BNode<T>* BinarySearchTree<T>::getSuccessor(BNode<T>* subRoot) {
	BNode<T> * x = subRoot;
	if (x->getRight() != sentinel) {
		return getMinimum(x->getRight());
	}

	BNode<T> * y = x->getParent();
	while (y != sentinel && x == y->getLeft()) {
		x = y;
		y = y->getParent();
	}
	return y;
}

template<class T>
BNode<T>* BinarySearchTree<T>::getPredecessor(BNode<T>* subRoot) {
	BNode<T> * x = subRoot;
	if (x->getRight() != sentinel) {
		return x->getMaximum();
	}

	BNode<T> * y = x->getParent();
	while (y != sentinel && x != y->getRight()) {
		x = y;
		y = y->getParent();
	}
	return y;
}

template<class T>
BNode<T>* BinarySearchTree<T>::getRoot() {

	return root;
}

template<class T>
BNode<T>* BinarySearchTree<T>::getSentinel() {

	return sentinel;
}

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

template<class T>
void BinarySearchTree<T>::print(BNode<T>* subroot, int space) {
	if (subroot != sentinel) {
		print(subroot->getRight(), space + 1);
		for (int i = 0; i < space; i++) {
			cout << "   ";
		}
		cout << subroot->getKey() << endl;
		print(subroot->getLeft(), space + 1);
	}
}

template<class T>
void BinarySearchTree<T>::insertNode(BNode<T>* subRoot, BNode<T> * z) {
	if (root != sentinel) {
		BNode<T> * y = sentinel;
		BNode<T> * x = subRoot;
		while (x != sentinel) {
			y = x;
			if (z->getKey() < x->getKey()) {
				x = x->getLeft();
			}
			else {
				x = x->getRight();
			}
		}

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
