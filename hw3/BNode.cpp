//	Authors: Joel Beckmeyer, Daniel Parker
//	Date: 2018-09-22
//	Purpose: To implement a node that can store any type

#include "BNode.h"

using namespace std;

template <class T>
BNode<T>::BNode(T newKey) {
	key = newKey;
}

template <class T>
BNode<T> * BNode<T>::getParent() {
	return parent;
}

template <class T>
BNode<T> * BNode<T>::getRight() {
	return right;
}

template <class T>
BNode<T> * BNode<T>::getLeft() {
	return left;
}

template <class T>
void BNode<T>::setParent(BNode<T> * newParent) {
	parent = newParent;
}

template <class T>
void BNode<T>::setRight(BNode<T> * newRight) {
	right = newRight;
}

template <class T>
void BNode<T>::setLeft(BNode<T> * newLeft) {
	left = newLeft;
}

template <class T>
T BNode<T>::getKey() {
	return key;
}
