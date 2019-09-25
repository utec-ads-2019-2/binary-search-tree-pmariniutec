#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"
#include <stdexcept>

template <typename T> 
class Iterator {
  private:
	Node<T> *current;

  public:
	Iterator() : current(nullptr) { }

	Iterator(Node<T> *node) : current(node) { }

	Iterator<T>& operator=(const Iterator<T> &other) {          
	  this->current = other.current;
	  return *this;
	}

	bool operator!=(Iterator<T> other) {
	  return current->data != other.current->data;
	}

	Iterator<T>& operator++() {

	  if(this->current == nullptr) {
		return *this;
	  }

	  if((this->current == this->current->left) && (this->current->right != nullptr)) {
		this->current = this->current->right;
	  } else {
		this->current = this->current->left;
		return *this;
	  }
	  while(true) {
		if(this->current->left != nullptr) {
		  this->current = this->current->left;
		} else if(this->current->right != nullptr) {
		  this->current = this->current->right;
		} else {
		  return *this;
		}
	  }
	}

	Iterator<T>& operator--() {

	}

	T operator*() {
	  if (current == nullptr)
		throw std::runtime_error("Range error");
	  return current->data;
	}
};

#endif
