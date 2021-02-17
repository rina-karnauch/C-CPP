//
// Activation H file
//

#ifndef EX1_ACTIVATION_H
#define EX1_ACTIVATION_H

#include <iostream>
#include <cmath>
#include "Matrix.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::ostream;
using std::istream;

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
	Relu,
	Softmax
};

/**
 * a class of activation types RELU or SOFTMAX
 */
class Activation
{
private:

	ActivationType _actType;

	// FRIENDS + ADDED:

	/**
	 * error in activation type
	 */
	friend void _typeError();

	/**
	 * a function to return the exp sum at the softmax equation
	 * @param m: the matrix
	 * @return the sum
	 */
	friend float _sumSoftMax(const Matrix &m);

public:

	// C'TORS:
	/**
	 * a constructor for activation
	 * @param actType: the act type
	 */
	Activation(ActivationType actType);

	// METHODS:
	/**
	 * getter for activation type
	 * @return activation type
	 */
	ActivationType getActivationType();

	//OPERATORS:
	/**
	 * a function to apply the activation function on a matrix objec
	 * @param m: matrix
	 * @return: a new matrix
	 */
	Matrix operator()(const Matrix &m);

};

#endif //EX1_ACTIVATION_H
