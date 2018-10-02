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
	~RedBlackTree();
	void insertNode(RBNode<T> * subRoot, T val);
	void removeNode(RBNode<T> * subRoot, RBNode<T> * val);

	RBNode<T> * getMinimum(BNode<T>* subRoot);
	RBNode<T> * getMaximum(BNode<T>* subRoot);
	RBNode<T> * getPredecessor(BNode<T>* subRoot);
	RBNode<T> * getSuccessor(BNode<T>* subRoot);
	RBNode<T> * getRoot();
	RBNode<T> * getSentinel();

	RBNode<T> * search(BNode<T> * subRoot, T Key);
	void print(RBNode<T> * subroot, int space);


private:
	void insertFixup(RBNode<T> * subRoot, RBNode<T> * z);
	void leftRotate(RBNode<T> * x);
	void rightRotate(RBNode<T> * y);

	void removeFixup(RBNode<T> * subRoot, RBNode<T> * x);
};



template<class T>
RedBlackTree<T>::RedBlackTree() {
	this->sentinel = new RBNode<T>(NULL, BLACK);
	this->sentinel->setLeft(this->sentinel);
	this->sentinel->setParent(this->sentinel);
	this->sentinel->setRight(this->sentinel);
	this->root = this->sentinel;
}

template<class T>
RedBlackTree<T>::~RedBlackTree() {
	
}



template<class T>
void RedBlackTree<T>::insertNode(RBNode<T>* subRoot, T val) {
	RBNode<T> * z = new RBNode<T>(val, RED);
	z->setRight(this->sentinel);
	z->setLeft(this->sentinel);
	z->setParent(this->sentinel);
	BinarySearchTree<T>::insertNode(subRoot, z);
	insertFixup(subRoot, z);
}



template<class T>
void RedBlackTree<T>::insertFixup(RBNode<T>* subRoot, RBNode<T>* z) {
	cout << z->getParent()->getColor() << endl;
	while (z->getParent()->getColor() == RED) {
		if (z->getParent()->getParent()->getLeft() == z->getParent()) { // If z's parent is a left child
			RBNode<T> * y = z->getParent()->getParent()->getRight();
			if (y->getColor() == RED) { // Case 1
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
			RBNode<T> * y = z->getParent()->getParent()->getLeft();
			if (y->getColor() == RED) { // Case 1
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
	static_cast<RBNode<T>*>(this->getRoot())->setColor(BLACK);
}



template<class T>
void RedBlackTree<T>::removeNode(RBNode<T> * subRoot, RBNode<T> * z) {
	if (z != this->sentinel) {
		RBNode<T> * y = z;
		bool color = y->getColor();
		bool hadTwoChildren = false;
		// if z has two children, y will be z's successor
		if (z->getLeft() != this->sentinel && z->getRight() != this->sentinel) {
			y = getSuccessor(z);
			color = y->getColor();
			hadTwoChildren = true;
		}
		RBNode<T> * x = static_cast<RBNode<T> *>(BinarySearchTree<T>::removeNode(subRoot, z));
		
		if (hadTwoChildren) {
			y->setColor(z->getColor());
		}

		if (color == BLACK) {
			removeFixup(subRoot, x);
		}
	}
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
	else if (x->getParent()->getLeft() == x) {// If x is left child
		x->getParent()->setLeft(y);
	}
	else { // if x is right child
		x->getParent()->setRight(y);
	}
	y->setLeft(x);
	x->setParent(y);
}



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
	else if (y->getParent()->getRight() == y) {// If x is left child
		y->getParent()->setRight(x);
	}
	else { // if x is right child
		y->getParent()->setLeft(x);
	}
	x->setRight(y);
	y->setParent(x);
}
