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
	void insertNode(BNode<T> * subRoot, T val) override;
	void removeNode(BNode<T> * subRoot, BNode<T> * val) override;

private:

	void removeFixUp(BNode<T> * T, RBNode<T> * x);

	BNode<T> * sentinel = new BNode<T>(NULL);
	BNode<T> * root = sentinel;
};


template<class T>
inline RedBlackTree<T>::~RedBlackTree() {
	delete sentinel;
	delete root;
}

template<class T>
void RedBlackTree<T>::insertNode(BNode<T>* subRoot, T val) {
	
	BinarySearchTree<T>::insertNode(subroot, val);
}

template<class T>
void RedBlackTree<T>::removeNode(RBNode<T> * subRoot, RBNode<T> * z) {
	RBNode<T> * y;
	// we find the position of z
	RBNode<T> * parent = z->getParent();
	bool isRoot = parent == sentinel;
	bool isLeft = (parent->getLeft() == z);

	RBNode<T> * x = removeNode(subRoot, z);
	// z's position is now y's position, so we find y
	if (isRoot) {
		y = getRoot();
	} else if (isLeft) {
		y = parent->getLeft();
	} else {
		y = parent->getRight();
	}

	if (y->getColor == BLACK) {
		removeFixUp(subRoot, x);
	}
	if (x != y) {
		y->setColor(z->getColor());
	}
}

template<class T>
void RedBlackTree<T>::removeFixUp(RBNode<T> * T, RBNode<T> * x) {
	while (x != getRoot() && x->getColor() == BLACK) {

		// if x is a left child
		if (x->getParent()->getLeft() == x) {
			RBNode<T> * w = x->getParent()->getRight();
			// case 1
			if (w->getColor() == RED) {
				w->setColor(BLACK);
				x->getParent()->setColor(RED);
				leftRotate(x->getParent());

				// reset w to be x's sibling
				if (x->getParent()->getRight() == x) {
					w = x->getParent->getRight();
				} else {
					w = x->getParent->getLeft();
				}
			}

			// case 2
			if (w->getLeft()->getColor() == BLACK && w->getRight()->getColor() == BLACK) {
				w->setColor(RED);
				x = x->getParent();
			}

			// case 3
			else if (w->getRight()->getColor() == BLACK) {
				w->getLeft()->setColor(BLACK);
				w->setColor(RED);
				rightRotate(w);
			}

			// case 4
			w->setColor(x->getParent()->getColor());
			x->getParent()->setColor(BLACK);
			w->getRight()->setColor(BLACK);
			leftRotate(x->getParent());
			x = getRoot();
		} else {
			RBNode<T> * w = x->getParent()->getLeft();
			// case 1
			if (w->getColor() == RED) {
				w->setColor(BLACK);
				x->getParent()->setColor(RED);
				rightRotate(x->getParent());

				// reset w to be x's sibling
				if (x->getParent()->getLeft() == x) {
					w = x->getParent->getLeft();
				} else {
					w = x->getParent->getRight();
				}
			}

			// case 2
			if (w->getRight()->getColor() == BLACK && w->getLeft()->getColor() == BLACK) {
				w->setColor(RED);
				x = x->getParent();
			}

			// case 3
			else if (w->getLeft()->getColor() == BLACK) {
				w->getRight()->setColor(BLACK);
				w->setColor(RED);
				leftRotate(w);
			}

			// case 4
			w->setColor(x->getParent()->getColor());
			x->getParent()->setColor(BLACK);
			w->getLeft()->setColor(BLACK);
			rightRotate(x->getParent());
			x = getRoot();
		}
	}

	x->setColor(BLACK);
}
