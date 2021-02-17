//
// Created by Rina Karnauch on 12/06/2020.
//

#include "Activation.h"
#include "Matrix.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::ostream;
using std::istream;
using std::exp;

// MSGS:
#define ACTYPE_ERR "Activation Type is not valid"

// FRIENDS WITH BENS:

/**
 * error in activation type
 */
void _typeError()
{
	cerr << ACTYPE_ERR << endl;
	exit(EXIT_FAILURE);
}


/**
 * a function to return the exp sum at the softmax equation
 * @param m: the matrix
 * @return the sum
 */
float _sumSoftMax(const Matrix &m)
{
	int rows = m._dim.rows;
	int cols = m._dim.cols;

	float sum = 0.0f;

	for (int i = 0; i < rows * cols; i++)
	{
		sum = sum + (float) exp(m[i]);
	}

	return sum;
}

// C'TORS:
/**
 * a constructor for activation
 * @param actType: the act type
 */
Activation::Activation(ActivationType actType) : _actType(actType)
{
	if (actType != Relu && actType != Softmax)
	{
		_typeError();
	}
}

/**
 * getter for activation type
 * @return activation type
 */
ActivationType Activation::getActivationType()
{
	return _actType;
}

/**
 * a function to apply the activation function on a matrix objec
 * @param m: matrix
 * @return: a new matrix
 */
Matrix Activation::operator()(const Matrix &m)
{
	Matrix mNew = Matrix(m);

	int rows = mNew._dim.rows;
	int cols = mNew._dim.cols;

	if (_actType == Relu)
	{
		for (int i = 0; i < rows * cols; i++)
		{
			if (mNew[i] < 0)
			{
				mNew[i] = 0;
			}
		}
	}
	else if (_actType == Softmax)
	{
		float sum = _sumSoftMax(mNew);
		sum = float(1 / sum);
		for (int i = 0; i < rows * cols; i++)
		{
			mNew[i] = float(sum * ((float) exp(mNew[i])));
		}
	}
	else
	{
		_typeError();
	}

	return mNew;
}