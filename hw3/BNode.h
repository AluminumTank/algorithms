//	Authors: Joel Beckmeyer, Daniel Parker
//	Date: 2018-09-22
//	Purpose: To specify a node that can store any type

template <class T>
class BNode {
	public:
		BNode();
		BNode(T key);

		BNode<T> getParent();
		BNode<T> getRight();
		BNode<T> getLeft();

		BNode<T> setParent();
		BNode<T> setRight();
		BNode<T> setLeft();

	private:
		BNode<T> * parent;
		BNode<T> * right;
		BNode<T> * left;
}
