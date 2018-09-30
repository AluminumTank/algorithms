/**
 * SUMMARY: An implementation of a binary search tree.
 *
 * AUTHOR: Daniel Parker
 * DATE: Sept 22, 2018
 *
**/
#include "RBNode.h"
#include "BinarySearchTree.h"

template <class T>
class RedBlackTree : public BinarySearchTree<T>{
public:
	RedBlackTree() {}
	~RedBlackTree();
	void insertNode(RBNode<T> * subRoot, T val) override;
	void removeNode(RBNode<T> * subRoot, RBNode<T> * val) override;

private:
	void insertFixup(RBNode<T> * subRoot, RBNode<T> * z);
	void leftRotate(RBNode<T> * x);
	void rightRotate(RBNode<T> * y);
};


template<class T>
inline RedBlackTree<T>::~RedBlackTree() {
	delete sentinel;
	delete root;
}

template<class T>
void RedBlackTree<T>::insertNode(RBNode<T>* subRoot, T val) {
	RBNode<T> z(val, RED);
	BinarySearchTree<T>::insertNode(subroot, &z);
	insertFixup(subRoot, z&);
}

template<class T>
void RedBlackTree<T>::removeNode(RBNode<T>* subRoot, RBNode<T>* val) {
	
}

template<class T>
void RedBlackTree<T>::insertFixup(RBNode<T>* subRoot, RBNode<T>* z) {
	while (z->getParent()->getColor() == RED) {
		if (z->getParent()->getParent()->getLeft() == z->getParent()) { // If z's parent is a left child
			RBNode<T> y = z->getParent()->getParent()->getRight();
			if (y.getColor() == RED) { // Case 1
				z->getParent()->setColor(BLACK);
				y->setColor(BLACK);
				z->getParent()->getParent()->setColor(RED);
				z = z->getParent()->getParent();
			}
			else {
				if (z == z->getParent()->getRight()) { // Case 2
					z = z->getParent();
					leftRotate(z);
				}//Case 3
				z->getParent()->setColor(BLACK);
				z->getParent()->getParent()->setColor(RED);
				rightRotate(z->getParent()->getParent());
			}
		}
		else { // If z's parent is a right child
			RBNode<T> y = z->getParent()->getParent()->getLeft();
			if (y.getColor() == RED) { // Case 1
				z->getParent()->setColor(BLACK);
				y->setColor(BLACK);
				z->getParent()->getParent()->setColor(RED);
				z = z->getParent()->getParent();
			}
			else {
				if (z == z->getParent()->getLeft()) { // Case 2
					z = z->getParent();
					rightRotate(z);
				}//Case 3
				z->getParent()->setColor(BLACK);
				z->getParent()->getParent()->setColor(RED);
				leftRotate(z->getParent()->getParent());
			}
		}
	}
}

template<class T>
void RedBlackTree<T>::leftRotate(RBNode<T>* x) {
	RBNode<T> * y = x->getRight();
	y->setParent(x->getParent());
	if (x->getParent()->getLeft() == x) {// If x is left child
		x->getParent()->setLeft(y);
	}
	else { // if x is right child
		x->getParent()->setRight(y);
	}
	x->setRight(y->getLeft());
	x->getRight()->setParent(x);
	y->setLeft(x);
	x->setParent(y);

}

template<class T>
void RedBlackTree<T>::rightRotate(RBNode<T>* y) {
	RBNode<T> * x = y->getLeft();
	x->setParent(y->getParent());
	if (y->getParent()->getLeft() == y) { // y is left child
		y->getParent()->setLeft(x);
	}
	else { // y is right child
		y->getParent()->setRight(x);
	}
	y->setLeft(x->getRight());
	y->getRight()->setParent(y);
	x->setRight(y);
	y->setParent(x);
}
