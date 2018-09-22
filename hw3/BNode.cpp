//	Authors: Joel Beckmeyer, Daniel Parker
//	Date: 2018-09-22
//	Purpose: To implement a node that can store any type

#include "BNode.h"

using namespace std;

template <class T>
class BNode {

	BNode(T newKey) {
		key = newKey;
	}

	BNode<T> * getParent() {
		return parent;
	}

	BNode<T> * getRight() {
		return right;
	}

	BNode<T> * getLeft() {
		return left;
	}

	void setParent(BNode<T> * newParent) {
		parent = newParent;
	}

	void setRight(BNode<T> * newRight) {
		right = newRight;
	}

	void setLeft(BNode<T> * newLeft) {
		left = newLeft;
	}
}
