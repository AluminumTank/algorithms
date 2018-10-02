//	Authors: Joel Beckmeyer, Daniel Parker
//	Date: 2018-09-22
//	Purpose: To specify a node that can store any type

#ifndef _BNODE_H_
#define _BNODE_H_

#include <cstddef>

using namespace std;

template <class T>
class BNode {
	public:
		BNode() {}
		BNode(T newKey);

		BNode<T> * getParent();
		BNode<T> * getRight();
		BNode<T> * getLeft();

		void setParent(BNode<T> * newParent);
		void setRight(BNode<T> * newRight);
		void setLeft(BNode<T> * newLeft);

		T getKey();

	private:
		BNode<T> * parent = NULL;
		BNode<T> * right = NULL;
		BNode<T> * left = NULL;
		T key = NULL;
};



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

#endif
