#include "NodeInterface.h"
#include "Node.h"
#include "AVLInterface.h"
#include <string>

using namespace std;

class AVL : 
  public AVLInterface 
{
public:
		Node * root;

	AVL() {
		root = NULL;
	}
	~AVL() {clear();}

	NodeInterface * getRootNode() const;

	bool add(int data);

	bool recAdd(Node*& n, int value);

	bool remove(int data);

	bool recRemove(Node*& n, int value);

	void clear();

	void recClear(Node*& n);

	void balanceRight(Node*& n);

	void balanceLeft(Node*& n);

	void rotateRight(Node*& n);

	void rotateLeft(Node*& n);

	void balance(Node*& n);

	Node* fosterParent(Node*& n);
  
};
