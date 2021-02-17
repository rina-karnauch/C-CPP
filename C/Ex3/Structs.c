//
// Created by Rina Karnauch on 19/05/2020.
//

#include <string.h>
#include <stdlib.h>
#include "Structs.h"
#include <stdbool.h>

#define SMALLER -1
#define GREATER 1
#define EQUAL 0
#define ZERO 0



/**
 * a function to get minimum out of 2 numbers
 * @param n1
 * @param n2
 * @return the minimum out of them, or one of them if they are equal
 */
int min(int n1, int n2)
{
	if (n1 < n2)
	{
		return n1;
	}
	else
	{
		return n2;
	}
}

/**
 * CompFunc for Vectors, compares element by element, the vector that has the first larger
 * element is considered larger. If vectors are of different lengths and identify for the length
 * of the shorter vector, the shorter vector is considered smaller.
 * @param a - first vector
 * @param b - second vector
 * @return equal to 0 iff a == b. lower than 0 if a < b. Greater than 0 iff b < a.
 */
int vectorCompare1By1(const void *a, const void *b)
{
	Vector *A = (Vector *) (a);
	Vector *B = (Vector *) (b);

	int minimal = min(A->len, B->len);

	for (int i = 0; i < minimal; i++)
	{
		// we check all items till the "common place"
		if ((A->vector)[i] < (B->vector)[i])
		{
			return SMALLER;
		}

		else if ((A->vector)[i] > (B->vector)[i])
		{
			return GREATER;
		}
	}

	// we have some items equal, now lets check lengths.

	if (A->len < B->len)
	{
		return SMALLER;
	}
	else if (A->len > B->len)
	{
		return GREATER;
	}
	else
	{
		//if lengths are equal and we have arrived here it means all items are equal
		// means equality
		return EQUAL;
	}

}

/**
 * a function to find a norm of the vector
 * @param v: the array of doubles
 * @param len: the len of the vector
 * @return the nurm without the square of it
 */
double normFinder(const double *v, const int len)
{
	if (v == NULL)
	{
		return ZERO;
	}
	double sum = 0;
	for (int i = 0; i < len; i++)
	{
		sum = sum + ((v[i]) * (v[i]));
	}
	return sum;
}

/**
 * copy pVector to pMaxVector if : 1. The norm of pVector is greater then the norm of pMaxVector.
 * 								   2. pMaxVector->vector == NULL.
 * @param pVector pointer to Vector
 * @param pMaxVector pointer to Vector
 * @return 1 on success, 0 on failure (if pVector == NULL: failure).
 */
int copyIfNormIsLarger(const void *vector, void *maxVector)
{
	int v1Len = ((Vector *) vector)->len;
	double *vMax = ((Vector *) maxVector)->vector;
	double *vFirst = ((Vector *) vector)->vector;

	int result = vectorCompare1By1(vector, maxVector);

	if (result > 1 || maxVector == NULL)
	{
		vMax = realloc(vMax, v1Len * (sizeof(double)));
		if (vMax == NULL)
		{
			return false; // 0
		}
		for (int i = 0; i < v1Len; i++)
		{
			vMax[i] = vFirst[i];
		}

	}

	return true;
}

/**
 * a recursive helper function to apply func to each branch of the tree
 * to find the max norm
 * @param root: current root
 * @param func: function copyIfNormIsLarger
 * @param ptr: ptr to the current max
 * @return the ptr to the max.
 */
Node *recurHelperS(Node *root, forEachFunc func, Node *ptr)
{
	if (!func(root->data, ptr))
	{
		return ptr;
	}

	Vector *current = root->data;

	func(current, ptr);

	recurHelperS(root->left, func, ptr);
	recurHelperS(root->right, func, ptr);

	return ptr;
}

/**
 * @param tree a pointer to a tree of Vectors
 * @return pointer to a *copy* of the vector that has the largest norm (L2 Norm).
 */
Vector *findMaxNormVectorInTree(RBTree *tree)
{
	Node *ptr = tree->root;

	ptr = recurHelperS(tree->root, copyIfNormIsLarger, ptr);
	return ptr->data;

}

/**
 * a function to find the max out of two norms
 * @param a first one
 * @param b second one
 * @return 1 if a>b 0 elseways
 */
int maxNormOutOfTwo(const double a, const double b)
{
	if (a > b)
	{
		return true; // 1
	}
	else
	{
		return false; // 0
	}

}

/**
 * FreeFunc for vectors
*/
void freeVector(void *vector)
{
	((Vector *) (vector))->len = 0;
	double *vA = ((Vector *) (vector))->vector;
	free(vA);
	vA = NULL;
	free(vector);
	vector = NULL;

}

/**
 * FreeFunc for strings
 */
void freeString(void *s)
{
	free(s);
	s = NULL;
}

/**
 * ForEach function that concatenates the given word and \n to pConcatenated. pConcatenated is
 * already allocated with enough space.
 * @param word - char* to add to pConcatenated
 * @param pConcatenated - char*
 * @return 0 on failure, other on success
 */
int concatenate(const void *word, void *pConcatenated)
{
	char *ptrString = (char *) pConcatenated;
	char *wordString = (char *) word;

	int toCopyLen = (int) strlen(wordString) - 1;
	int len = (int) strlen(pConcatenated);

	ptrString[len - 1] = '\n';

	for (int i = len - 2; i >= 0; i--)
	{
		ptrString[i] = wordString[toCopyLen];
		toCopyLen = toCopyLen - 1;
	}

	return true; // 1
}

/**
 * CompFunc for strings (assumes strings end with "\0")
 * @param a - char* pointer
 * @param b - char* pointer
 * @return equal to 0 iff a == b. lower than 0 if a < b. Greater than 0 iff b < a. (lexicographic
 * order)
 * */
int stringCompare(const void *a, const void *b)
{
	return strcmp(a, b);
}