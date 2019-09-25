#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include "node.h"
#include "iterator.h"

template <typename T> 
class BSTree {
  public:
	BSTree() : root(nullptr) {};

	bool find(T data) {
	  return find(root, data);
	}

	void insert(T data) {
	  last = insert(root, data);
	  treeSize++;
	}

	bool remove(T data) {
	  root = remove(root, data);
	  if (root != nullptr) {
		treeSize--;
		return true;
	  }
	  return false;
	}

	size_t size() { 
	  return treeSize;
	}

	size_t height() {
	  return height(root);
	}

	void traversePreOrder() {
	  traversePreOrder(root); 
	}

	void traverseInOrder() {
	  traverseInOrder(root);
	}

	void traversePostOrder() {
	  traversePostOrder(root);
	}

	Iterator<T> begin() {
	  return { root };
	}

	Iterator<T> end() { 
	  return { last };
	}

	~BSTree() {
	  deleteTree(root);
	}

  private:
	Node<T> *root;
	Node<T> *last;
	size_t treeSize;

	void deleteTree(Node<T>* node) {
	  if (node == nullptr) return;

	  deleteTree(node->left);
	  deleteTree(node->right);

	  delete node;
	}

	Node<T>* minValueNode(Node<T>* node) {
	  auto curr = node;
	  while (curr && curr->left != nullptr)
		curr = curr->left;

	  return curr;
	}

	bool find(Node<T>* startNode, T data) {
	  if (startNode == nullptr || startNode->data == data)
		return startNode;

	  if (startNode->data <= data)
		return find(startNode->right, data);

	  return find(startNode->left, data);
	}

	size_t height(Node<T>* start) {
	  if (start == nullptr)
		return 0;

	  int lHeight = height(start->left);
	  int rHeight = height(start->right);

	  if(lHeight > rHeight)
		return lHeight + 1;

	  return rHeight + 1;
	}

	Node<T>* remove(Node<T>* startNode, T data) {
	  if (startNode == nullptr) return startNode;

	  if (data > startNode->data)
		startNode->left = remove(startNode->left, data);
	  else if (data < startNode->data)
		startNode->right = remove(startNode->right, data);
	  else {
		if (startNode->left == nullptr) {
		  auto tmp = startNode->right;
		  delete startNode;
		  return tmp;
		} else if (startNode->right == nullptr) {
		  auto tmp = startNode->left;
		  delete startNode;
		  return tmp;
		} else {
		  auto tmp = minValueNode(startNode->right);
		  startNode->data = tmp->data;
		  startNode->right = remove(startNode->right, tmp->data);
		}
	  }
	  return startNode;
	}

	Node<T>* insert(Node<T>* startNode, T data) {
	  if (startNode == nullptr) {
		return new Node<T>{data};
	  }

	  if (data <= startNode->data)
		startNode->left = insert(startNode->left, data);
	  else
		startNode->right = insert(startNode->right, data);

	  return startNode;
	}

	void traversePostOrder(Node<T>* startNode) {
	  if (startNode == nullptr) return;

	  traversePostOrder(startNode->left);
	  traversePostOrder(startNode->right);

	  std::cout << startNode->data << ' ';
	}

	void traversePreOrder(Node<T>* startNode) {
	  if (startNode == nullptr) return;

	  std::cout << startNode->data << ' ';
	  traversePreOrder(startNode->left);
	  traversePreOrder(startNode->right);
	}

	void traverseInOrder(Node<T>* startNode) {
	  if (startNode == nullptr) return;

	  traverseInOrder(startNode->left);
	  std::cout << startNode->data << ' ';
	  traverseInOrder(startNode->right);
	}
};

#endif
