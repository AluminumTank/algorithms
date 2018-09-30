/* SUMMARY: An implementation of a binary search tree.
 *
 * AUTHOR: Daniel Parker, Joel Beckmeyer
 * DATE: Sept 22, 2018
 *
 */
#include "RBNode.h"
#include "BinarySearchTree.h"

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

private:
	void insertFixup(RBNode<T> * subRoot, RBNode<T> * z);
	void leftRotate(RBNode<T> * x);
	void rightRotate(RBNode<T> * y);

	void removeFixUp(RBNode<T> * subRoot, RBNode<T> * x);
};



template<class T>
RedBlackTree<T>::RedBlackTree() {
	delete this->sentinel;
	this->sentinel = new RBNode<T>(NULL, BLACK);
	this->sentinel->setLeft(this->sentinel);
	this->sentinel->setParent(this->sentinel);
	this->sentinel->setRight(this->sentinel);
	this->root = this->sentinel;
}

template<class T>
RedBlackTree<T>::~RedBlackTree() {
	delete this->root;
}



template<class T>
void RedBlackTree<T>::insertNode(RBNode<T>* subRoot, T val) {
	RBNode<T> z(val, RED);
	BinarySearchTree<T>::insertNode(subRoot, &z);
	insertFixup(subRoot, &z);
}



template<class T>
void RedBlackTree<T>::insertFixup(RBNode<T>* subRoot, RBNode<T>* z) {
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
}



template<class T>
void RedBlackTree<T>::removeNode(RBNode<T> * subRoot, RBNode<T> * z) {
	if (z != this->sentinel) {
		RBNode<T> * y;
		// we find the position of z
		RBNode<T> * parent = z->getParent();
		bool isRoot = parent == this->sentinel;
		bool isLeft = (parent->getLeft() == z);

		RBNode<T> * x = static_cast<RBNode<T> *>(BinarySearchTree<T>::removeNode(subRoot, z));
		// z's position is now y's position, so we find y
		if (isRoot) {
			y = getRoot();
		}
		else if (isLeft) {
			y = parent->getLeft();
		}
		else {
			y = parent->getRight();
		}

		if (y->getColor() == BLACK) {
			removeFixUp(subRoot, x);
		}
		if (x != y) {
			y->setColor(z->getColor());
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
void RedBlackTree<T>::removeFixUp(RBNode<T> * subRoot, RBNode<T> * x) {
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
					w = x->getParent()->getRight();
				}
				else {
					w = x->getParent()->getLeft();
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
		}
		else {
			RBNode<T> * w = x->getParent()->getLeft();
			// case 1
			if (w->getColor() == RED) {
				w->setColor(BLACK);
				x->getParent()->setColor(RED);
				rightRotate(x->getParent());

				// reset w to be x's sibling
				if (x->getParent()->getLeft() == x) {
					w = x->getParent()->getLeft();
				}
				else {
					w = x->getParent()->getRight();
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
