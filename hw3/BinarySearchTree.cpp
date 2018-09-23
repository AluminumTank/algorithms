#include "BinarySearchTree.h"


template <class T>
BinarySearchTree<T>::~BinarySearchTree() {
	delete sentinel;
}

template<class T>
void BinarySearchTree<T>::insertNode(BNode<T>* subRoot, T val) {
	BNode<T> z(val);
	BNode<T> * y = sentinel;
	BNode<T> * x = subRoot;

	while (x != sentinel) {
		y = x;
		if (z.getKey() < x->getKey()) {
			x = x->getLeft();
		} 
		else {
			x = x->getRight();
		}
	}

	z.setParent(y);
	if (y == sentinel) {
		subroot = &z;
	}
	else if (z.getKey() < y->getKey()) {
		y->setLeft(z);
	}
	else {
		y->setRight(z);
	}
}

template<class T>
void BinarySearchTree<T>::removeNode(BNode<T>* subRoot, BNode<T>* val) {
	if (val->getLeft() == sentinel) {
		transplant(val, val->getRight());
	}
	else if (val->getRight() == sentinel) {
		transplant(val, val->getLeft());
	}
	else {
		BNode<T> * y = getMinimum(subroot);
	}
}

template<class T>
BNode<T>* BinarySearchTree<T>::getMinimum() {

	return nullptr;
}

template<class T>
BNode<T>* BinarySearchTree<T>::getMaximum() {

	return nullptr;
}

template<class T>
BNode<T>* BinarySearchTree<T>::search(T Key) {

	return nullptr;
}

template<class T>
BNode<T>* BinarySearchTree<T>::getSuccessor(BNode<T>* subRoot) {

	return nullptr;
}

template<class T>
BNode<T>* BinarySearchTree<T>::getPredecessor(BNode<T>* subRoot) {

	return nullptr;
}

template<class T>
BNode<T>* BinarySearchTree<T>::getRoot() {

	return nullptr;
}

template<class T>
BNode<T>* BinarySearchTree<T>::getSentinel() {

	return nullptr;
}
