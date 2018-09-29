//	Authors: Joel Beckmeyer, Daniel Parker
//	Date: 2018-09-22
//	Purpose: To specify a node that can store any type
#ifndef _BNODE_H_
#define _BNODE_H_
#include <cstddef>
#include "BNode.h"

using namespace std;

template <class T>
class RBNode : public BNode<T> {
public:
	RBNode() {}
	RBNode(T newKey);

	RBNode<T> * getParent();
	RBNode<T> * getRight();
	RBNode<T> * getLeft();

	void setParent(RBNode<T> * newParent);
	void setRight(RBNode<T> * newRight);
	void setLeft(RBNode<T> * newLeft);

	T getKey();

private:
	RBNode<T> * parent = NULL;
	RBNode<T> * right = NULL;
	RBNode<T> * left = NULL;
	T key = NULL;
};