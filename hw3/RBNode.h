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
	RBNode(T newKey, bool isBlack);

	bool getColor();

private:
	bool color = RED;
};

template <class T>
RBNode<T>::RBNode(T newKey, bool isBlack) : BNode(newKey) {
	color = isBlack;
}

template <class T>
void RBNode<T>::getColor() {
	return color;
}
