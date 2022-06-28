#include "NodeInterface.h"
#include "Node.h"
#include "AVL.h"
#include <algorithm>
#include <sstream>
#include <queue>
#include <string>
using namespace std;

string go(Node* bst) {
    queue<NodeInterface*> readQ;
    stringstream nodeReader_ss;
    int depth = 0;

    if (bst == NULL) {
        return "BST is empty\n";
    }
    readQ.push(bst);
    while (!readQ.empty()) {
        int i = readQ.size();
        nodeReader_ss << depth << ":  ";
        for (; i > 0; i--) {
            NodeInterface* nextNode = readQ.front();
            nodeReader_ss << nextNode->getData() << " ";
            if (nextNode->getLeftChild() != NULL) {
              readQ.push(nextNode->getLeftChild());
            }
            if (nextNode->getRightChild() != NULL) {
              readQ.push(nextNode->getRightChild());
            }
            readQ.pop();
        }
        nodeReader_ss << "\n";
        depth++;
    }
    return nodeReader_ss.str();
}

NodeInterface * AVL::getRootNode() const {
	return root;
}

bool AVL::add(int data) {
	recAdd(root, data);
}

bool AVL::recAdd(Node*& n, int value) {
	if (n == NULL) {
		n = new Node(value);
		n->height = 0;
		return true;
	}
	if (n->data == value) {
		return false;
	}
	if (n->data > value) {
		bool fluff = recAdd(n->leftChild, value);
		if (fluff == true) {
			if (n->getBalance() > 1) {
				balanceLeft(n);
      }
			if (n->getBalance() < -1) {
				balanceRight(n);
      }
		}
		return fluff;
	}
	if (n->data < value) {
		bool fluff2 = recAdd(n->rightChild, value);
		if (fluff2 == true) {
			if (n->getBalance() > 1) {
				balanceLeft(n);
      }
			if (n->getBalance() < -1) {
				balanceRight(n);
      }
		}
		return fluff2;
	}
	if (n->getBalance() > 1) {
		balanceLeft(n);
  }
	if (n->getBalance() < -1) {
		balanceRight(n);
  }
	return false;
}

bool AVL::remove(int data) {
		bool fluff5;
		fluff5 = recRemove(root, data);
		balance(root);
		return fluff5;
}

bool AVL::recRemove(Node*& n, int value) {
	if (n == NULL) {
		return false;
	}
	if (n->data > value) {
		bool fluff3 = recRemove(n->leftChild, value);

		balance(n);

		return fluff3;
	}
	if (n->data < value) {
		bool fluff4 = recRemove(n->rightChild, value);
		balance(n);
		return fluff4;
	}

	if (n->rightChild == NULL && n->leftChild == NULL) {
		delete n;
		n = NULL;
		return true;
	}

	if (n->rightChild == NULL || n->leftChild == NULL) {
		Node* temp;
		temp = n->leftChild;
		if (n->leftChild == NULL) {
			temp = n->rightChild;
		}
		delete n;
		n = temp;
		balance(n);
		return true;
	}
	Node* temp = fosterParent(n->leftChild);
	temp->leftChild = n->leftChild;
	temp->rightChild = n->rightChild;
	delete n;
	n = temp;
	return true;
}

Node* AVL::fosterParent(Node*& n) {
	if (n->rightChild == NULL) {
		Node* temp = n;
		n = n->leftChild;
		return temp;
	}
	Node* temp = fosterParent(n->rightChild);
	balance(n);
	return temp;
}

void AVL::clear() {
	recClear(root);
	root = NULL;
}
void AVL::recClear(Node*& n) {
	if (n == NULL) {
		return;
	}

	if (n->leftChild != NULL) {
		recClear(n->leftChild);
	}
	if (n->rightChild != NULL) {
		recClear(n->rightChild);
	}
	delete n;
	return;
}


void AVL::balanceRight(Node*& n) {
	if (n == NULL)
		return;
		if (n->leftChild->getBalance() >= 1) {
			rotateLeft(n->leftChild);
		}
		rotateRight(n);
}

void AVL::balanceLeft(Node*& n) {
	if (n == NULL)
		return;
		if (n->rightChild->getBalance() <= -1) {
			rotateRight(n->rightChild);
		}
		rotateLeft(n);
}


void AVL::rotateRight(Node*& n) {
	Node* temp = n->leftChild;
	n->leftChild = temp->rightChild;
	temp->rightChild = n;
	n = temp;
}

void AVL::rotateLeft(Node*& n) {
	Node* temp = n->rightChild;
	n->rightChild = temp->leftChild;
	temp->leftChild = n;
	n = temp;
}

void AVL::balance(Node*& n) {
	if (n == NULL) {
		return;
  }
	if (n->getBalance() > 1) {
		balanceLeft(n);
  }
	else if (n->getBalance() < -1) {
		balanceRight(n);
  }
		balance(n->leftChild);
		balance(n->rightChild);
}