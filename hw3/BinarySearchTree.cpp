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
		BNode<T> * y = getMinimum(subroot->getRight());
		if (y->getParent() != val) {
			transplant(y, y->getRight());
			y->setRight(val->getRight());
			y->getRight()->setParent(y);
		}

		transplant(val, y);
		y->setLeft(val->getLeft());
		y->getLeft()->setParent(y);
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
	if (x == sentinel || k == x->getKey()) {
		return x;
	}

	if (k < x->getKey()) {
		return search(x->getLeft(), k);
	} else {
		return search(x->getRight(), k);
	}
}

template<class T>
BNode<T>* BinarySearchTree<T>::getSuccessor(BNode<T>* subRoot) {
	BNode<T> * x = subRoot;
	if (x->getRight() != sentinel) {
		return x->getMinimum();
	}

	BNode<T> * y = x.getParent();
	while (y != sentinel && x != y->getLeft()) {
		x = y;
		y = y->getParent();
	}
	return y;
}

template<class T>
BNode<T>* BinarySearchTree<T>::getPredecessor(BNode<T>* subRoot) {
	BNode<T> * x = subRoot;
	if (x->getRight() != sentinel) {
		return xgetMaximum();
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
void transplant(BNode<T> * candidate, BNode<T> * donor) {
	BNode<T> * parent = candidate.getParent();

	// connect candidate parent and donor: determine whether candidate is left or right child
	if (candidate == parent->getRight()) {
		parent->setRight(donor);
	} else {
		parent->setLeft(donor);
	}
	donor->setParent(parent);

	// connect candidate children and donor children
	donor->setLeft(candidate->getLeft());
	donor->setRight(candidate->getRight());

}
