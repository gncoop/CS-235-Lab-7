#ifndef NODE_H
#define NODE_H
#include <iostream>
#include "NodeInterface.h"

class Node :
	public NodeInterface
{

public:
	Node * leftChild;
	Node * rightChild;
	int data;
	int height;

	Node(int value) {
		height = 0;
		data = value;
		leftChild = NULL;
		rightChild = NULL;
	}
	~Node() {
	}

	int getData() const;

	NodeInterface * getLeftChild() const;

	NodeInterface * getRightChild() const;

	int getHeight();
	int getBalance();
};
#endif
