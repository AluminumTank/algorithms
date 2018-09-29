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
void RedBlackTree<T>::removeNode(BNode<T>* subRoot, BNode<T>* val) {
	
}
