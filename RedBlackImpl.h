
#ifndef RedBlackImpl_h
#define RedBlackImpl_h

#include <iostream>

enum Color {
	RED, BLACK
};

struct RbkNode {
	int data;
	Color color;
	RbkNode *leftSide;
	RbkNode *rightSide;
	RbkNode *parentNode;

	explicit RbkNode(int val) :
			data(val), color(RED), leftSide(nullptr), rightSide(nullptr), parentNode(
					nullptr) {
	}
};

class RedBlackImpl {

public:
	RbkNode *rbkRoot;
	RedBlackImpl() :
			rbkRoot(nullptr) {
	}
	;
	void rotatingLeft(RbkNode *rl);
	void rotatingRight(RbkNode *rr);
	void rebalanceAfterInsert(RbkNode *ai);
	void swapNode(RbkNode *u, RbkNode *v);
	void nodeDeletion(RbkNode *del);
	void rebalanceTreeAfterDelete(RbkNode *rebal);
	RbkNode* min(RbkNode *node);
	void printTree(RbkNode *root, int space);
	void removeAll();
	void removeAllNodes(RbkNode *rn);

	void insert(int val);
	void deleteElement(int val);
	void print();
	RbkNode* getRoot();
	void inorderTraversal();
	void tranverse(RbkNode *node);
	RbkNode* searchKey(RbkNode *node, int val);
	bool searchTree(int ser);
};

#endif /* RedBlackImpl_h */
