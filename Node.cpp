#include <iostream>
#include <algorithm>
#include "Node.h"

int Node::getData() const {
  return data;
} 

NodeInterface * Node::getLeftChild() const {
  return leftChild;
}

NodeInterface * Node::getRightChild() const {
  return rightChild;
}

int Node::getHeight() {
	int leftHeight = 0;
	int rightHeight = 0;

	if (leftChild != NULL) {
		leftHeight = leftChild->getHeight();
	}
	if (rightChild != NULL) {
		rightHeight = rightChild->getHeight();
	}
	return max(leftHeight, rightHeight) + 1;
}


int Node::getBalance() {
	int right;
	int left;
	if (rightChild != NULL) {
		right = rightChild->getHeight();
	}
	else
	right = 0;

	if (leftChild != NULL) {
		left = leftChild->getHeight();
	}
	else
	left = 0;
	return right - left;
}