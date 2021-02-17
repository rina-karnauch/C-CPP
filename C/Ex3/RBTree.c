//
// Created by Rina Karnauch on 19/05/2020.
//

#include <stdio.h>
#include "RBTree.h"
#include <stdlib.h>
#include <stdbool.h>

#ifdef TA_EX3_STRUCTS_H
#include "Structs.h"
#endif

#define START_SIZE 0
#define A 31
#define BA 321
#define BB 322
#define CC 33
#define D 34
#define E 35
#define CASE1 1
#define CASE2 2
#define CASE3 3
#define CASE4 4

/**
 * a function to make a new node
 * @param data data inside the new node
 * @return pointer to the node
 */
Node *newNode(void *data)
{
	Node *newN = NULL;
	newN = (Node *) malloc(sizeof(Node));

	if (newN == NULL)
	{
		free(newN);
		newN = NULL;
		return NULL;
	}

	newN->data = data;
	newN->color = RED;
	newN->parent = NULL;
	newN->left = NULL;
	newN->right = NULL;

	return newN;
}

/**
 * find the right place to insert in Binary Search Tree
 * @param root root of subtree
 * @param data data to be inserted
 * @param compFunc comparison functions
 * @return finds where the data should be in the tree
 */
Node *findPlace(RBTree *tree, const void *data, CompareFunc compFunc)
{
	Node *current = tree->root;

	while (current != NULL)
	{
		int result = compFunc(data, current->data);
		if (result < 0)
		{
			if (current->left == NULL)
			{
				return current;
			}
			current = current->left;
		}
		else if (result > 0)
		{
			if (current->right == NULL)
			{
				return current;
			}
			current = current->right;
		}
		else if (result == 0)
		{
			return current;
		}
	}
	return NULL;
}

/**
 * a function to find the uncle
 * @param current: current son we talk about
 * @return a pointer to the uncle
 */
Node *findUncle(Node *current)
{

	Node *parent = current->parent;
	if (parent == NULL)
	{
		return NULL;
	}
	if (parent->left == current)
	{
		return parent->right;
	}
	if (parent->right == current)
	{
		return parent->left;
	}
	return NULL;
}

/**
 * a function to put the node inside of the tree
 * @param tree: the tree root we insert inside
 * @param newN: the new Node to insert
 * @parem compFunc: the function we compare with
 * @return: the pointer to the new node place, NULL for failure.
 */
Node *insertToBST(RBTree *tree, CompareFunc compFunc, void *data)
{
	Node *root = tree->root;
	if (root == NULL)
	{
		Node *n = newNode(data);
		if (n == NULL)
		{
			free(n);
			return NULL; // we have a problem
		}
		tree->root = n;
		return n;
	}

	Node *n = newNode(data);
	if (n == NULL)
	{
		free(n);
		return NULL;
	}

	Node *findParent = findPlace(tree, data, compFunc);

	if (compFunc(data, findParent->data) < 0)
	{
		findParent->left = n;
		n->parent = findParent;
	}
	else if (compFunc(data, findParent->data) > 0)
	{
		findParent->right = n;
		n->parent = findParent;
	}
	return n;
}

/**
 * a function to identifity our situation at case 4
 * @param N: the node
 * @return the case number
 */
int case4Indentifior(const Node *N)
{
	Node *P = N->parent;
	Node *G = P->parent;
	if (P->right == N && G->left == P)
	{
		return CASE1;
	}
	else if (P->left == N && G->right == P)
	{
		return CASE2;
	}
	else if (P->left == N && G->left == P)
	{
		return CASE3;
	}
	else if ((P->right == N && G->right == P))
	{
		return CASE4;
	}
	else
	{
		return false; // 0
	}
}

/**
 * a function to return the color of the node
 * @param n the node
 * @return the color
 */
Color colorFinder(const Node *n)
{
	if (n == NULL)
	{
		return BLACK;
	}
	if (n->color == BLACK)
	{
		return BLACK;
	}
	if (n->color == RED)
	{
		return RED;
	}
	return BLACK;
}

/**
 * function to do the right rotation
 * @param rotated : node to rotate
 */
void rightRotation(Node *y)
{
	if (y == NULL)
	{
		return;
	}
	Node *xSubRight = NULL;
	Node *x = y->left;
	if (x != NULL)
	{
		xSubRight = x->right;
	}
	Node *yParent = y->parent;

	x->right = y;
	y->left = xSubRight;

	y->parent = x;
	if (xSubRight != NULL)
	{
		xSubRight->parent = y;
	}

	if (yParent != NULL)
	{
		if (yParent->right == y)
		{
			yParent->right = x;
			x->parent = yParent;
		}
		else if (yParent->left == y)
		{
			yParent->left = x;
			x->parent = yParent;
		}
	}
}

/**
 * function to do the left roation
 * @param rotated: node to rotate
 */
void leftRotation(Node *x)
{
	if (x == NULL)
	{
		return;
	}

	Node *ySubLeft = NULL;
	Node *y = x->right;

	if (y != NULL)
	{
		ySubLeft = y->left;
	}
	Node *xParent = x->parent;

	y->left = x;
	x->right = ySubLeft;

	x->parent = y;
	if (ySubLeft != NULL)
	{
		ySubLeft->parent = x;
	}

	if (xParent != NULL)
	{
		if (xParent->right == x)
		{
			xParent->right = y;
			y->parent = xParent;
		}
		else if (xParent->left == x)
		{
			xParent->left = y;
			y->parent = xParent;
		}
	}
}

/**
 * a function to check and correct the tree
 * @param N : current node
 * @param root : root of the tree
 * @param tree : the tree
 * @return : SUCCESS 1 or FAILURE 0
 */
int checkAndCorrect(Node *N, Node *root, RBTree *tree)
{
	if (root == N)
	{
		root->color = BLACK;
		return true; // 1
	}

	if (N->parent->color == BLACK)
	{
		return true; // 1
	}

	Node *P = N->parent;
	Node *U = findUncle(P);
	Node *G = P->parent;

	Color cP = colorFinder(P);
	Color cU = colorFinder(U);

	if (cP == RED && cU == RED)
	{
		// case 3
		P->color = BLACK;
		U->color = BLACK;
		if (G != NULL)
		{
			G->color = RED;
			checkAndCorrect(G, root, tree);
		}
		else
		{
			checkAndCorrect(P, root, tree);
		}
	}

	if (cP == RED && cU == BLACK)
	{
		// case 4
		switch (case4Indentifior(N))
		{
			case 0:
				// undescribed problem,
				return false; // 0
			case 1:
				// N is right son of left son
				leftRotation(P);
				// we receive a right linked list
				// now N is parent and P is child
				rightRotation(G);
				if (G == tree->root)
				{
					tree->root = N;
					N->parent = NULL;
				}
				N->color = BLACK;
				G->color = RED;
				break;
			case 2:
				// N is left son of right son
				rightRotation(P);
				// we receive a left linked list
				// now N is parent and P is child
				leftRotation(G);
				if (G == tree->root)
				{
					tree->root = N;
					N->parent = NULL;
				}
				N->color = BLACK;
				G->color = RED;
				break;
			case 3:
				// N is left son of left son
				rightRotation(G);
				if (G == root)
				{
					tree->root = P;
					P->parent = NULL;
				}
				// now N is Parent and P is child
				P->color = BLACK;
				G->color = RED;
				break;
			case 4:
				// N is right son of right son
				leftRotation(G);
				if (G == root)
				{
					tree->root = P;
					P->parent = NULL;
				}
				// now N is Parent and P is child
				P->color = BLACK;
				G->color = RED;
				break;
		}
	}
	return true; //1
}

/**
 * add an item to the tree
 * @param tree: the tree to add an item to.
 * @param data: item to add to the tree.
 * @return: 0 on failure, other on success. (if the item is already in the tree - failure).
 */
int insertToRBTree(RBTree *tree, void *data)
{
	if (data == NULL)
	{
		return false; // 0
	}
	if (tree == NULL)
	{
		return false; // 0
	}
	if (RBTreeContains(tree, data))
		/* we already have it in */
	{
		return false; // 0
	}
	else
		/* we need to insert */
	{
		CompareFunc compFunc = tree->compFunc;
		Node *n = insertToBST(tree, compFunc, data);

		Node *root = tree->root;

		if (n == NULL)
		{
			return false; // 0
		}

		tree->size = tree->size + 1;
		int cF = checkAndCorrect(n, root, tree);

		if (!cF)
		{
			return false;
		}

	}

	return true; // 1
}

/**
 * a function to find the brother of the current Node
 * @param current: current
 * @return: the node
 */
Node *brotherFinder(const Node *current)
{
	Node *p = current->parent;
	if (p == NULL)
	{
		return NULL;
	}
	if (p->right == current)
	{
		return p->left;
	}
	return p->right;
}

/**
 * function to swap colors
 * @param nodeA first node
 * @param nodeB second node
 */
void swapColors(Node *nodeA, Node *nodeB)
{
	Color cA = nodeA->color;
	Color cB = nodeB->color;

	nodeB->color = cA;
	nodeA->color = cB;

}

/**
 * a function to get the leftmost node from a subtree
 * @param current: current node
 * @return the leftmost node
 */
Node *leftMost(Node *current)
{
	while (current->left != NULL)
	{
		current = current->left;
	}
	return current;
}

/**
 * function to find successor
 * @param from the successor of the from node
 * @return the node of comparison
 */
Node *successorFinder(Node *from)
{
	/* easy case, we have right subtree */
	if (from->right != NULL)
	{
		return leftMost(from->right);
	}

	/* no right one to M? only on child, which is smaller, no successor. DB on the right*/

	return NULL;
}

/**
 * deleting from BST
 * @param root : the current root where we delete from
 * @param data the data we delete
 * @param compFunc: comparison fucntion
 * @return the new root of the tree
 */
void deleteLeafBST(Node **node, FreeFunc freeD)
{
	Node *parent = (*node)->parent;

	if (parent == NULL)
	{
		freeD((*node)->data);
		free(*node);
		*node = NULL;
	}
	else if (parent->right == (*node))
	{
		parent->right = NULL;
		(*node)->parent = NULL;
		freeD((*node)->data);
		free(*node);
		*node = NULL;
	}
	else if (parent->left == (*node))
	{
		parent->left = NULL;
		(*node)->parent = NULL;
		freeD((*node)->data);
		free(*node);
		*node = NULL;
	}
}

/**
 * a function to switch M and S if they exists
 * @param M: current node to delete.
 * @param S: left most child in the right subtree of M.
 */
void swapMandS(Node *M, Node *S)
{
	void *dataM = M->data;
	M->data = S->data;
	S->data = dataM;
}

/**
 * a function to send back the far Node
 * @param S: the brother of deleted node
 * @param P: the parent of S and deleted
 * @return
 */
Node *farNode(const Node *S, const Node *P)
{
	if (P->right == S)
	{
		return S->right;
	}
	else
	{
		return S->left;
	}
}

/**
 * function to send back the closer Node
 * @param S: the brother of deleted node
 *  * @param P: the parent of S and deleted
 * @return: the farthest son of the brother
 */
Node *closeNode(const Node *S, const Node *P)
{

	if (P->right == S)
	{
		return S->left;
	}
	else
	{
		return S->right;
	}

}

/**
 * function to check what to do if M is black and C is Black according
 * to the orders that we got.
 * @param C: the son of deleted node.
 * @param P: the parent of deleted node.
 * @param S: the brother of deleted node.
 * @return number of sub option
 */
int sectionBChecker(const Node *C, const Node *P, const Node *S, RBTree *tree)
{
	if (C == tree->root)
	{
		return A;
	}

	Node *sRight = NULL;
	Node *sLeft = NULL;

	if (S != NULL)
	{
		sRight = S->right;
		sLeft = S->left;
	}

	if (colorFinder(S) == BLACK && colorFinder(sRight) == BLACK && colorFinder(sLeft) == BLACK)
	{
		if (colorFinder(P) == RED)
		{
			return BA;
		}
		if (colorFinder(P) == BLACK)
		{
			return BB;
		}
	}
	else if (colorFinder(S) == RED)
	{
		return CC;
	}
	else if (colorFinder(S) == BLACK)
	{
		if (colorFinder(farNode(S, P)) == BLACK && colorFinder(closeNode(S, P)) == RED)
		{
			return D;
		}
		if (colorFinder(farNode(S, P)) == RED)
		{
			return E;
		}
	}
	return false; // 0
}

/**
 * a function to recursivly fix the tree
 * @param C: son of deleted node
 * @param P: parent of deleted node
 * @param S: brother of deleted node
 * @param tree: the tree
 */
void recurHelper(Node *C, Node *P, Node *S, RBTree *tree)
{

	switch (sectionBChecker(C, P, S, tree))
	{
		case A:
			/* C is now root, we can finish */
		{
			return;
		}

		case BA:
			/* P is red, C is black, and sright and sleft are black*/
		{
			P->color = BLACK;
			S->color = RED;
			return;
		}
		case BB:
			/* P is black, C is black, and sright and sleft are black*/
		{
			/*P->color = BLACK;
			S->color = RED;*/

			S->color = RED;
			C = P;
			S = brotherFinder(C);
			P = C->parent;

			//
			return recurHelper(C, P, S, tree);
			//
		}
		case CC:
			/* S is red, C is black, and sright and sleft are black*/
		{
			Node *Sn = NULL;
			S->color = BLACK;
			P->color = RED;
			if (P->right == S)
			{
				leftRotation(P);
				//
				Sn = P->right;
				P->parent = S;
				if (tree->root == P)
				{
					tree->root = S;
					S->parent = NULL;
				}
			}
			else
			{
				rightRotation(P);
				//
				Sn = P->left;
				P->parent = S;
				if (tree->root == P)
				{
					tree->root = S;
					S->parent = NULL;
				}
			}
			// c now is the son of P and p is the son of S.
			//
			return recurHelper(C, P, Sn, tree);
			//
		}
		case D:
			/* S is black, sFar is black and sClose is Red*/
		{
			//
			S->color = RED;
			Node *sC = closeNode(S, P);
			sC->color = BLACK;
			if (P->right == S)
			{
				rightRotation(S);
			}
			else
			{
				leftRotation(S);
			}
			return recurHelper(C, P, sC, tree);
		}
		case E:
			/* S is black, sFar is Red */
		{
			Node *sF = farNode(S, P);
			swapColors(S, P);

			if (P->right == S)
			{
				leftRotation(P);

				if (tree->root == P)
				{
					tree->root = S;
					S->parent = NULL;
				}
			}
			else
			{
				rightRotation(P);

				if (tree->root == P)
				{
					tree->root = S;
					S->parent = NULL;
				}
			}

			sF->color = BLACK;
			return;
		}
	}
}

/**
 * a function to handle when M is black
 * @param M: black node, successor if got any ones, after swapping.
 * M got or 1 child or 0 childs.
 * @param C: the one possible child of M.
 * @param P: the parent of M.
 * @param S: the other son of P, brother of M.
 * @param tree: the tree.
 */
void handleBlack(Node *M, Node *C, Node *P, Node *S, RBTree *tree)
{

	FreeFunc freeD = tree->freeFunc;

	if (colorFinder(C) == RED)
	{
		swapMandS(M, C);
		deleteLeafBST(&C, freeD);
		M->color = BLACK;
		return;
	}

	C = M;

	if (tree->root == C)
	{
		deleteLeafBST(&M, freeD);
		tree->root = NULL;
		return;
	}

	// c is always black

	recurHelper(C, P, S, tree);
	deleteLeafBST(&M, freeD);

}

/**
 * a function to find current's only son
 * @param current: the node we look for its son
 * @return the son
 */
Node *sonFinder(Node *current)
{
	if (current->left != NULL)
	{
		return current->left;
	}

	if (current->right != NULL)
	{
		return current->right;
	}
	else
	{
		return NULL;
	}
}

int deleteFromRBTree(RBTree *tree, void *data)
{

	if (tree == NULL)
	{
		return false; // 0
	}
	if ((tree->root) == NULL)
		/* we got nothing inside */
	{
		return false; // 0
	}

	CompareFunc compFunc = tree->compFunc;

	if (RBTreeContains(tree, data))
		/* if the value is in the tree we delete it */
	{
		tree->size = tree->size - 1;
		Node *M = findPlace(tree, data, compFunc); // to delete

		if (M->right != NULL && M->left != NULL)
			/* we got two children- we got successor
			 * we swap them */
		{
			Node *Successor = successorFinder(M);
			swapMandS(Successor, M);
			/* now we got M inside successor and successor inside M */
			M = Successor;
			Successor = NULL;
		}

		Node *P = M->parent;
		Node *C = sonFinder(M);
		Node *S = brotherFinder(M);
		FreeFunc freeD = tree->freeFunc;

		switch (colorFinder(M))
		{
			case RED:
				deleteLeafBST(&M, freeD);
				C = NULL;
				S = NULL;
				return true; // 1
			case BLACK:
				handleBlack(M, C, P, S, tree);
		}

		return true; // 1
	}
	else
		/* if the value is not in the tree */
	{
		return false; // 0
	}

}

/**
 * check whether the tree RBTreeContains this item.
 * @param tree: the tree to add an item to.
 * @param data: item to check.
 * @return: 0 if the item is not in the tree, other if it is.
 */
int RBTreeContains(const RBTree *tree, const void *data)
{
	if (tree == NULL)
	{
		// tree is empty
		return false; // 0
	}
	CompareFunc compFunc = tree->compFunc;
	Node *current = tree->root;
	while (current != NULL)
	{
		int result = compFunc(data, current->data);

		if (result < 0)
		{
			current = current->left;
		}

		else if (result > 0)
		{
			current = current->right;
		}

		else if (result == 0)
		{
			// we have found it!
			return true; // 1
		}
	}

	/*if we reaeched here, we haven't fount it */
	return false; // 0

}

/**
 * a function to do the function on the tree by inorder  traversal
 * @param node: the node we do it on
 * @param func: the function we apply
 */
int inOrder(Node *node, forEachFunc func, void *args)
{
	if (node == NULL)
	{
		return true; // 1
	}

	if (!(func(node->data, args)))
	{
		return false; // 0
	}

	return inOrder(node->left, func, args) && inOrder(node->right, func, args);

}

/**
 * Activate a function on each item of the tree. the order is an ascending order. if one of the activations of the
 * function returns 0, the process stops.
 * @param tree: the tree with all the items.
 * @param func: the function to activate on all items.
 * @param args: more optional arguments to the function (may be null if the given function support it).
 * @return: 0 on failure, other on success.
 */
int forEachRBTree(const RBTree *tree, forEachFunc func, void *args)
{
	if (tree == NULL)
	{
		return false; // 0
	}

	Node *node = tree->root;

	return inOrder(node, func, args);
}

/**
 * a function to free the current node we want to free
 * @param current: node we are freeing
 */
void freeNodes(Node **current, FreeFunc freeD)
{
	if (current != NULL)
	{
		Node *left = (*current)->left;
		Node *right = (*current)->right;

		if (left != NULL)
		{
			freeNodes(&left, freeD);
		}
		if (right != NULL)
		{
			freeNodes(&right, freeD);
		}

		freeD((*current)->data);
		free(*current);
		*current = NULL;
	}

}

/**
 * free all memory of the data structure.
 * @param tree: pointer to the tree to free.
 */
void freeRBTree(RBTree **tree)
{
	Node *current;
	current = (*tree)->root;
	FreeFunc freeD = (*tree)->freeFunc;

	if (current != NULL)
	{
		freeNodes(&current, freeD);
	}

	free(*tree);
	*tree = NULL;
}

/**
 * constructs a new RBTree with the given CompareFunc.
 * comp: a function two compare two variables.
 */
RBTree *newRBTree(CompareFunc compFunc, FreeFunc freeFunc)
{
	RBTree *tree = NULL;

	/* the object of the tree */
	tree = (RBTree *) malloc(sizeof(RBTree));

	if (tree == NULL)
	{
		freeFunc(&tree);
		return NULL;
	}

	tree->size = START_SIZE;
	tree->compFunc = compFunc;
	tree->freeFunc = freeFunc;
	tree->root = NULL;

	return tree;

}
