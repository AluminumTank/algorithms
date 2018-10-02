//	Authors: Joel Beckmeyer, Daniel Parker
//	Date: 2018-09-22
//	Purpose: To specify a node that can store any type
#ifndef _RBNODE_H_
#define _RBNODE_H_
#include <cstddef>
#include "BNode.h"

#define RED false
#define BLACK true

using namespace std;

template <class T>
class RBNode : public BNode<T> {
public:
	RBNode() {}
	RBNode(T newKey, int newColor);

	RBNode<T> * getParent();
	RBNode<T> * getRight();
	RBNode<T> * getLeft();

	int getColor();

	void setColor(int newColor);

private:
	bool color = RED;
};

template <class T>
RBNode<T>::RBNode(T newKey, int newColor) : BNode<T>(newKey) {
	this->color = newColor;
}

// for the following functions, we found it useful to interact with the tree
// without having to cast every time. Our solution was to redefine each of the
// functions as a cast of the underlying BNode pointer
template<class T>
RBNode<T>* RBNode<T>::getParent() {
	return static_cast<RBNode<T> *>(BNode<T>::getParent());
}

template<class T>
RBNode<T>* RBNode<T>::getRight() {
	return static_cast<RBNode<T> *>(BNode<T>::getRight());
}

template<class T>
RBNode<T>* RBNode<T>::getLeft() {
	return static_cast<RBNode<T> *>(BNode<T>::getLeft());
}

template <class T>
int RBNode<T>::getColor() {
	return color;
}

template <class T>
void RBNode<T>::setColor(int newColor) {
	color = newColor;
}

#endif
