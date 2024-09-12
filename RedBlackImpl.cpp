#include "RedBlackImpl.h"

using std::cout;
using std::endl;

RbkNode* RedBlackImpl::getRoot() {
	return rbkRoot;
}

void RedBlackImpl::insert(int val) {
	if (rbkRoot == nullptr) {
		rbkRoot = new RbkNode(val);
		rbkRoot->color = BLACK;
	} else {
		RbkNode *newKey = new RbkNode(val);
		RbkNode *y_node = nullptr;
		RbkNode *x_node = rbkRoot;

		while (x_node != nullptr) {
			y_node = x_node;
			if (val < (*x_node).data)
				x_node = (*x_node).leftSide;
			else if (val > (*x_node).data)
				x_node = (*x_node).rightSide;
			else {
				cout << val << " is already contained in tree." << endl;
				delete newKey;
				return;
			}
		}

		(*newKey).parentNode = y_node;
		if (val < (*y_node).data)
			(*y_node).leftSide = newKey;
		else
			(*y_node).rightSide = newKey;

		rebalanceAfterInsert(newKey);
	}
}
void RedBlackImpl::rebalanceAfterInsert(RbkNode *val) {
	while (val != rbkRoot && (*val).parentNode->color == RED) {
		if ((*val).parentNode == (*val).parentNode->parentNode->leftSide) {
			RbkNode *y_node = (*val).parentNode->parentNode->rightSide;
			if (y_node != nullptr && (*y_node).color == RED) {
				(*val).parentNode->color = BLACK;
				(*y_node).color = BLACK;
				(*val).parentNode->parentNode->color = RED;
				val = (*val).parentNode->parentNode;
			} else {
				if (val == (*val).parentNode->rightSide) {
					val = (*val).parentNode;
					rotatingLeft(val);
				}
				(*val).parentNode->color = BLACK;
				(*val).parentNode->parentNode->color = RED;
				rotatingRight((*val).parentNode->parentNode);
			}
		} else {
			RbkNode *y = (*val).parentNode->parentNode->leftSide;
			if (y != nullptr && (*y).color == RED) {
				(*val).parentNode->color = BLACK;
				(*y).color = BLACK;
				(*val).parentNode->parentNode->color = RED;
				val = (*val).parentNode->parentNode;
			} else {
				if (val == (*val).parentNode->leftSide) {
					val = (*val).parentNode;
					rotatingRight(val);
				}
				(*val).parentNode->color = BLACK;
				(*val).parentNode->parentNode->color = RED;
				rotatingLeft((*val).parentNode->parentNode);
			}
		}
	}
	rbkRoot->color = BLACK;

}

void RedBlackImpl::rotatingLeft(RbkNode *x_node) {
	if (x_node == nullptr || (*x_node).rightSide == nullptr)
		return;

	RbkNode *y_node = (*x_node).rightSide;
	(*x_node).rightSide = (*y_node).leftSide;
	if ((*y_node).leftSide != nullptr)
		(*y_node).leftSide->parentNode = x_node;
	(*y_node).parentNode = (*x_node).parentNode;
	if ((*x_node).parentNode == nullptr)
		rbkRoot = y_node;
	else if (x_node == (*x_node).parentNode->leftSide)
		(*x_node).parentNode->leftSide = y_node;
	else
		(*x_node).parentNode->rightSide = y_node;
	(*y_node).leftSide = x_node;
	(*x_node).parentNode = y_node;
}

void RedBlackImpl::rotatingRight(RbkNode *y_node) {
	if (y_node == nullptr || (*y_node).leftSide == nullptr)
		return;

	RbkNode *x_node = (*y_node).leftSide;
	(*y_node).leftSide = (*x_node).rightSide;
	if ((*x_node).rightSide != nullptr)
		(*x_node).rightSide->parentNode = y_node;
	(*x_node).parentNode = (*y_node).parentNode;
	if ((*y_node).parentNode == nullptr)
		rbkRoot = x_node;
	else if (y_node == (*y_node).parentNode->leftSide)
		(*y_node).parentNode->leftSide = x_node;
	else
		(*y_node).parentNode->rightSide = x_node;
	(*x_node).rightSide = y_node;
	(*y_node).parentNode = x_node;
}

void RedBlackImpl::inorderTraversal() {
	if (rbkRoot == nullptr) {
		cout << "The tree is empty." << endl;
		return;
	}

	tranverse(rbkRoot);
	cout << endl;
}

void RedBlackImpl::tranverse(RbkNode *node) {
	if (node == nullptr) {
		return;
	}

	tranverse(node->leftSide);
	cout << node->data << " ";
	tranverse(node->rightSide);
}

void RedBlackImpl::print() {
	if (rbkRoot == nullptr) {
		cout << "The tree is empty." << endl;
		return;
	}
	printTree(rbkRoot, 0);
}

void RedBlackImpl::printTree(RbkNode *rootNode, int val) {
	constexpr int COUNT = 3;

	if (rootNode == nullptr) {
		return;
	}

	val += COUNT;
	printTree((*rootNode).rightSide, val);
	cout << endl;
	for (int i = COUNT; i < val; i++)
		cout << " ";
	cout << (*rootNode).data << "(" << (((*rootNode).color == RED) ? "Red" : "Black")
			<< ")" << endl;
	printTree((*rootNode).leftSide, val);
}

void RedBlackImpl::deleteElement(int val) {
	RbkNode *z = rbkRoot;
	while (z != nullptr) {
		if (val < (*z).data)
			z = (*z).leftSide;
		else if (val > (*z).data)
			z = (*z).rightSide;
		else {
			nodeDeletion(z);
			return;
		}
	}
	cout << val << " not found in the tree." << endl;
}

void RedBlackImpl::removeAll() {
	cout << "Deleting all the elements in the tree" << endl;
	if (rbkRoot != NULL) {
		removeAllNodes(rbkRoot);
	}
	cout << endl;
}

void RedBlackImpl::removeAllNodes(RbkNode *x) {
	if (x == nullptr) {
		rbkRoot = NULL;
		return;
	}
	removeAllNodes(x->leftSide);
	removeAllNodes(x->rightSide);
	delete x;

}

void RedBlackImpl::nodeDeletion(RbkNode *z_node) {
	if (z_node == nullptr)
		return;

	RbkNode *y_node = z_node;
	RbkNode *x_node = nullptr;
	Color y_original_color = (*y_node).color;

	if ((*z_node).leftSide == nullptr) {
		x_node = (*z_node).rightSide;
		swapNode(z_node, (*z_node).rightSide);
	} else if ((*z_node).rightSide == nullptr) {
		x_node = (*z_node).leftSide;
		swapNode(z_node, (*z_node).leftSide);
	} else {
		y_node = min((*z_node).rightSide);
		y_original_color = (*y_node).color;
		x_node = (*y_node).rightSide;

		if ((*y_node).parentNode == z_node) {
			if (x_node != nullptr)
				(*x_node).parentNode = y_node;
		} else {
			if (x_node != nullptr)
				(*x_node).parentNode = (*y_node).parentNode;
			swapNode(y_node, (*y_node).rightSide);
			if ((*y_node).rightSide != nullptr)
				(*y_node).rightSide->parentNode = y_node;
			(*y_node).rightSide = (*z_node).rightSide;
			if ((*y_node).rightSide != nullptr)
				(*y_node).rightSide->parentNode = y_node;
		}
		swapNode(z_node, y_node);
		(*y_node).leftSide = (*z_node).leftSide;
		if ((*y_node).leftSide != nullptr)
			(*y_node).leftSide->parentNode = y_node;
		(*y_node).color = (*z_node).color;
	}

	if (y_original_color == BLACK && x_node != nullptr)
		rebalanceTreeAfterDelete(x_node);

	delete z_node;
}

void RedBlackImpl::swapNode(RbkNode *a, RbkNode *b) {
	if ((*a).parentNode == nullptr)
		rbkRoot = b;
	else if (a == (*a).parentNode->leftSide)
		(*a).parentNode->leftSide = b;
	else
		(*a).parentNode->rightSide = b;
	if (b != nullptr)
		(*b).parentNode = (*a).parentNode;
}

void RedBlackImpl::rebalanceTreeAfterDelete(RbkNode *x_val) {
	while (x_val != rbkRoot && x_val != nullptr && (*x_val).color == BLACK) {
		if (x_val == (*x_val).parentNode->leftSide) {
			RbkNode *w_val = (*x_val).parentNode->rightSide;
			if ((*w_val).color == RED) {
				(*w_val).color = BLACK;
				(*x_val).parentNode->color = RED;
				rotatingLeft((*x_val).parentNode);
				w_val = (*x_val).parentNode->rightSide;
			}
			if (((*w_val).leftSide == nullptr || (*w_val).leftSide->color == BLACK)
					&& ((*w_val).rightSide == nullptr || (*w_val).rightSide->color == BLACK)) {
				(*w_val).color = RED;
				x_val = (*x_val).parentNode;
			} else {
				if ((*w_val).rightSide == nullptr || (*w_val).rightSide->color == BLACK) {
					if ((*w_val).leftSide != nullptr)
						(*w_val).leftSide->color = BLACK;
					(*w_val).color = RED;
					rotatingRight(w_val);
					w_val = (*x_val).parentNode->rightSide;
				}
				(*w_val).color = (*x_val).parentNode->color;
				(*x_val).parentNode->color = BLACK;
				if ((*w_val).rightSide != nullptr)
					(*w_val).rightSide->color = BLACK;
				rotatingLeft((*x_val).parentNode);
				x_val = rbkRoot;
			}
		} else {
			RbkNode *rbk_w = (*x_val).parentNode->leftSide;
			if ((*rbk_w).color == RED) {
				(*rbk_w).color = BLACK;
				(*x_val).parentNode->color = RED;
				rotatingRight((*x_val).parentNode);
				rbk_w = (*x_val).parentNode->leftSide;
			}
			if (((*rbk_w).rightSide == nullptr || (*rbk_w).rightSide->color == BLACK)
					&& ((*rbk_w).leftSide == nullptr || (*rbk_w).leftSide->color == BLACK)) {
				(*rbk_w).color = RED;
				x_val = (*x_val).parentNode;
			} else {
				if ((*rbk_w).leftSide == nullptr || (*rbk_w).leftSide->color == BLACK) {
					if ((*rbk_w).rightSide != nullptr)
						(*rbk_w).rightSide->color = BLACK;
					(*rbk_w).color = RED;
					rotatingLeft(rbk_w);
					rbk_w = (*x_val).parentNode->leftSide;
				}
				(*rbk_w).color = (*x_val).parentNode->color;
				(*x_val).parentNode->color = BLACK;
				if ((*rbk_w).leftSide != nullptr)
					(*rbk_w).leftSide->color = BLACK;
				rotatingRight((*x_val).parentNode);
				x_val = rbkRoot;
			}
		}
	}
	if (x_val != nullptr)
		(*x_val).color = BLACK;
}

RbkNode* RedBlackImpl::min(RbkNode *node) {
	while ((*node).leftSide != nullptr)
		node = (*node).leftSide;
	return node;
}

bool RedBlackImpl::searchTree(int val) {
	RbkNode *node = searchKey(this->rbkRoot, val);
	if (node == NULL) {
		cout << "No elements found" << endl;
		return 0;
	} else {
		cout << "Element found : ";
		cout << val << (node->color == RED ? " Red" : " Black") << endl;
		return 1;
	}
}

RbkNode* RedBlackImpl::searchKey(RbkNode *rbkNode, int val) {
	if (rbkNode == NULL || val == rbkNode->data) {
		return rbkNode;
	}

	if (val < rbkNode->data) {
		return searchKey(rbkNode->leftSide, val);
	}
	return searchKey(rbkNode->rightSide, val);
}

