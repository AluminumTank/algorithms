/**
 * SUMMARY: An implementation of a binary search tree.
 *
 * AUTHOR: Daniel Parker
 * DATE: Sept 22, 2018
 *
**/
#ifndef _BINARYSEARCHTREE_H_
#define _BINARYSEARCHTREE_H_
#include "BNode.h"
#include <cstddef>

using namespace std;

template <class T>
class BinarySearchTree {
public:
	BinarySearchTree() {}
	~BinarySearchTree();
	void insertNode(BNode<T> * subRoot, T val);
	void removeNode(BNode<T> * subRoot, BNode<T> * val);
	BNode<T> * getMinimum(BNode<T> * subRoot);
	BNode<T> * getMaximum(BNode<T> * subRoot);
	BNode<T> * search(BNode<T> * subRoot, T Key);
	BNode<T> * getSuccessor(BNode<T> * subRoot);
	BNode<T> * getPredecessor(BNode<T> * subRoot);
	BNode<T> * getRoot();
	BNode<T> * getSentinel();
	void transplant(BNode<T> * candidate, BNode<T> * donor);

private:
	BNode<T> * sentinel = new BNode<T>(NULL);
	BNode<T> * root = sentinel;
};

#include "BinarySearchTree.cpp"
#endif
