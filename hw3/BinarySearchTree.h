/**
 * SUMMARY: An implementation of a binary search tree.
 *
 * AUTHOR: Daniel Parker
 * DATE: Sept 22, 2018
 * 
**/
#include "BNode.h"

template <class T>
class BinarySearchTree {
public:
	BinarySearchTree() {}
	~BinarySearchTree();
	void insertNode(BNode<T> * subRoot, T val);
	void removeNode(BNode<T> * subRoot, BNode<T> * val);
	BNode<T> * getMinimum();
	BNode<T> * getMaximum();
	BNode<T> * search(T Key);
	BNode<T> * getSuccessor(BNode<T> * subRoot);
	BNode<T> * getPredecessor(BNode<T> * subRoot);
	BNode<T> * getRoot();
	BNode<T> * getSentinel();

private:
	BNode<T> * root = NULL;
	BNode<T> * sentinel = new BNode<T>(NULL);
};