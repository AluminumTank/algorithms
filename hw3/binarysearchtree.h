/**
 * SUMMARY: An implementation of a binary search tree.
 *
 * AUTHOR: Daniel Parker
 * 
 * 
**/
#include "BNode.h"

template <class T>
class BinarySearchTree {
public:
	BinarySearchTree() {}
	~BinarySearchTree();
	Insert(BNode<T> * SubRoot, T val);
	Delete(BNode<T> * SubRoot, BNode<T> * val);
	BNode<T> * Minimum();
	BNode<T> * Maximum();
	BNode<T> * Search(T Key);
	BNode<T> * Successor(BNode<T> * SubRoot);
	BNode<T> * Predecessor(BNode<T> * SubRoot);
	BNode<T> * GetRoot();
private:
	BNode<T> * Root = NULL;
	BNode<T> * Sentinal = new BNode<T>(NULL);
};