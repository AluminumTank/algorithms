/* SUMMARY: An implementation of a binary search tree.
 *
 * AUTHOR: Daniel Parker, Joel Beckmeyer
 * DATE: Sept 22, 2018
 *
 */
#include "RBNode.h"
#include "BinarySearchTree.h"
#include <iostream>

template <class T>
class RedBlackTree : public BinarySearchTree<T>{
public:
	RedBlackTree();
	~RedBlackTree() {}

	RBNode<T> * getMinimum(BNode<T>* subRoot);
	RBNode<T> * getMaximum(BNode<T>* subRoot);
	RBNode<T> * getPredecessor(BNode<T>* subRoot);
	RBNode<T> * getSuccessor(BNode<T>* subRoot);
	RBNode<T> * getSentinel();
	RBNode<T> * getRoot();
	RBNode<T> * search(BNode<T> * subRoot, T Key);

	void insertNode(RBNode<T> * subRoot, T val);
	void removeNode(RBNode<T> * subRoot, RBNode<T> * val);
	void print(RBNode<T> * subroot, int space);

private:
	void insertFixup(RBNode<T> * subRoot, RBNode<T> * z);
	void removeFixup(RBNode<T> * subRoot, RBNode<T> * x);
	void leftRotate(RBNode<T> * x);
	void rightRotate(RBNode<T> * y);
};

template<class T>
RedBlackTree<T>::RedBlackTree() {
	this->sentinel = new RBNode<T>(NULL, BLACK);
	this->sentinel->setLeft(this->sentinel);
	this->sentinel->setParent(this->sentinel);
	this->sentinel->setRight(this->sentinel);
	this->root = this->sentinel;
}

// similarly to in RBNode.h, we found it useful to cast each of the functions
// from BinarySearchTree to return RBNode pointers instead of BNode pointers
template<class T>
RBNode<T> * RedBlackTree<T>::getMinimum(BNode<T>* subRoot)
{
	return static_cast<RBNode<T> *>(BinarySearchTree<T>::getMinimum(subRoot));
}

template<class T>
RBNode<T> * RedBlackTree<T>::getMaximum(BNode<T>* subRoot)
{
	return static_cast<RBNode<T> *>(BinarySearchTree<T>::getMaximum(subRoot));
}

template<class T>
RBNode<T> * RedBlackTree<T>::getPredecessor(BNode<T>* subRoot)
{
	return static_cast<RBNode<T> *>(BinarySearchTree<T>::getPredecessor(subRoot));
}

template<class T>
RBNode<T> * RedBlackTree<T>::getSuccessor(BNode<T>* subRoot)
{
	return static_cast<RBNode<T> *>(BinarySearchTree<T>::getSuccessor(subRoot));
}

template<class T>
RBNode<T> * RedBlackTree<T>::getSentinel()
{
	return static_cast<RBNode<T> *>(BinarySearchTree<T>::getSentinel());
}

template<class T>
RBNode<T> * RedBlackTree<T>::getRoot() {
	return static_cast<RBNode<T> *>(this->root);
}

template<class T>
RBNode<T> * RedBlackTree<T>::search(BNode<T>* subRoot, T Key)
{
	return static_cast<RBNode<T> *>(BinarySearchTree<T>::search(subRoot, Key));
}

// given a value by the user, constructs a node with that value and inserts
// that node into the underlying BinarySearchTree
template<class T>
void RedBlackTree<T>::insertNode(RBNode<T>* subRoot, T val) {
	RBNode<T> * z = new RBNode<T>(val, RED);
	z->setRight(this->sentinel);
	z->setLeft(this->sentinel);
	z->setParent(this->sentinel);
	BinarySearchTree<T>::insertNode(subRoot, z);
	insertFixup(subRoot, z);
}

// removes the given node
template<class T>
void RedBlackTree<T>::removeNode(RBNode<T> * subRoot, RBNode<T> * z) {
	// we don't want to try to remove the sentinel
	if (z != this->sentinel) {
		// we need to figure out what y will be
		RBNode<T> * y = z;
		bool color = y->getColor();
		bool hadTwoChildren = false;
		// if z has two children, y will be z's successor
		if (z->getLeft() != this->sentinel && z->getRight() != this->sentinel) {
			y = getSuccessor(z);
			color = y->getColor();
			hadTwoChildren = true;
		}

		// we remove the node from the underlying BST
		RBNode<T> * x = static_cast<RBNode<T> *>(BinarySearchTree<T>::removeNode(subRoot, z));

		// if y was the successor of z, we set y.color to z.color
		if (hadTwoChildren) {
			y->setColor(z->getColor());
		}

		// if y was black, we must do a RedBlackTree fixup
		if (color == BLACK) {
			removeFixup(subRoot, x);
		}
	}
}

// prints the tree values and colors in a left-to-right style, with lines to
// indicate different levels of the tree. Root is at far left, leaves 
// are at far right
template<class T>
void RedBlackTree<T>::print(RBNode<T>* subroot, int space) {
	if (subroot != this->sentinel) {
		print(subroot->getRight(), space + 1);
		for (int i = 0; i < space; i++) {
			cout << "   |";
		}
		cout << subroot->getKey();
		if (subroot->getColor() == BLACK) {
			cout << "B" << endl;
		}
		else {
			cout << "R" << endl;
		}
		print(subroot->getLeft(), space + 1);
	}
}

// rebalances the tree so that all five RBTree properties are satisfied after
// a node is inserted
template<class T>
void RedBlackTree<T>::insertFixup(RBNode<T>* subRoot, RBNode<T>* z) {
	while (z->getParent()->getColor() == RED) {
		// If z's parent is a left child
		if (z->getParent()->getParent()->getLeft() == z->getParent()) {
			RBNode<T> * y = z->getParent()->getParent()->getRight();
			if (y->getColor() == RED) { // Case 1
				z->getParent()->setColor(BLACK);
				y->setColor(BLACK);
				z->getParent()->getParent()->setColor(RED);
				z = z->getParent()->getParent();
			}
			else {
				// Case 2
				if (z == z->getParent()->getRight()) {
					z = z->getParent();
					leftRotate(z);
				}
				//Case 3
				z->getParent()->setColor(BLACK);
				z->getParent()->getParent()->setColor(RED);
				rightRotate(z->getParent()->getParent());
			}
		}
		// If z's parent is a right child
		else {
			RBNode<T> * y = z->getParent()->getParent()->getLeft();
			if (y->getColor() == RED) { // Case 1
				z->getParent()->setColor(BLACK);
				y->setColor(BLACK);
				z->getParent()->getParent()->setColor(RED);
				z = z->getParent()->getParent();
			}
			else {
				// Case 2
				if (z == z->getParent()->getLeft()) {
					z = z->getParent();
					rightRotate(z);
				}
				//Case 3
				z->getParent()->setColor(BLACK);
				z->getParent()->getParent()->setColor(RED);
				leftRotate(z->getParent()->getParent());
			}
		}
	}
	static_cast<RBNode<T>*>(this->getRoot())->setColor(BLACK);
}

// rebalances the tree so that all five RBTree properties are satisfied after
// a node is removed
template<class T>
void RedBlackTree<T>::removeFixup(RBNode<T> * subRoot, RBNode<T> * x) {
	while (x != this->root && x->getColor() == BLACK) {
		cout << endl;
		print(subRoot, 0);
		// if x is a left child
		if (x->getParent()->getLeft() == x) {
			RBNode<T> * w = x->getParent()->getRight();
			// case 1
			if (w->getColor() == RED) {
				w->setColor(BLACK);
				x->getParent()->setColor(RED);
				leftRotate(x->getParent());

				// reset w to be x's sibling
				w = x->getParent()->getRight();
			}

			// case 2
			if (w->getLeft()->getColor() == BLACK && w->getRight()->getColor() == BLACK) {
				w->setColor(RED);
				x = x->getParent();
			}

			// case 3
			else {
				if (w->getRight()->getColor() == BLACK) {
					w->getLeft()->setColor(BLACK);
					w->setColor(RED);
					rightRotate(w);
					w = x->getParent()->getRight();
				}

				// case 4
				w->setColor(x->getParent()->getColor());
				x->getParent()->setColor(BLACK);
				w->getRight()->setColor(BLACK);
				leftRotate(x->getParent());
				x = getRoot();
			}
		}
		// if x is a right child
		else {
			RBNode<T> * w = x->getParent()->getLeft();
			// case 1
			if (w->getColor() == RED) {
				w->setColor(BLACK);
				x->getParent()->setColor(RED);
				rightRotate(x->getParent());

				// reset w to be x's sibling
				w = x->getParent()->getLeft();
			}

			// case 2
			if (w->getRight()->getColor() == BLACK && w->getLeft()->getColor() == BLACK ) {
				w->setColor(RED);
				x = x->getParent();
			}

			// case 3
			else {
				if (w->getLeft()->getColor() == BLACK) {
					w->getRight()->setColor(BLACK);
					w->setColor(RED);
					leftRotate(w);
					w = x->getParent()->getLeft();
				}

				// case 4
				w->setColor(x->getParent()->getColor());
				x->getParent()->setColor(BLACK);
				w->getLeft()->setColor(BLACK);
				rightRotate(x->getParent());
				x = getRoot();
			}
		}
	}

	x->setColor(BLACK);
	static_cast<RBNode<T> *>(this->sentinel)->setColor(BLACK);
}

// implements a left rotate as described in the text
template<class T>
void RedBlackTree<T>::leftRotate(RBNode<T>* x) {
	RBNode<T> * y = x->getRight();
	x->setRight(y->getLeft());
	if (y->getLeft() != this->sentinel) {
		y->getLeft()->setParent(x);
	}
	y->setParent(x->getParent());
	if (x->getParent() == this->sentinel) {
		this->root = y;
	}
	else if (x->getParent()->getLeft() == x) {
		// If x is left child
		x->getParent()->setLeft(y);
	}
	else {
		// if x is right child
		x->getParent()->setRight(y);
	}
	y->setLeft(x);
	x->setParent(y);
}

// implements a right rotate as described in the text
template<class T>
void RedBlackTree<T>::rightRotate(RBNode<T>* y) {
	RBNode<T> * x = y->getLeft();
	y->setLeft(x->getRight());
	if (x->getRight() != this->sentinel) {
		x->getRight()->setParent(y);
	}
	x->setParent(y->getParent());
	if (y->getParent() == this->sentinel) {
		this->root = x;
	}
	// If x is left child
	else if (y->getParent()->getRight() == y) {
		y->getParent()->setRight(x);
	}
	// if x is right child
	else {
		y->getParent()->setLeft(x);
	}
	x->setRight(y);
	y->setParent(x);
}
