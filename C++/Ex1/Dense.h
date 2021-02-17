//
// Created by Rina Karnauch on 12/06/2020.
//

#ifndef EX1_DENSE_H
#define EX1_DENSE_H

#include "Activation.h"
#include "Matrix.h"

// MACROS
#define ACT_ERR 3

#include <iostream>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::ostream;
using std::istream;

/**
 * a class of Dense level
 */
class Dense
{
private:
	Matrix _w;
	Matrix _bias;
	Activation _act;

	friend class Matrix;

	friend class Activation;

	friend void _typeError();

public:

	//C'TORS:
	/**
	 * constructor
	 * @param w: weights feild
	 * @param bias: bias feild
	 * @param actType: act type feild
	 */
	Dense(const Matrix &w, const Matrix &bias, const Activation &actType);

	// METHODS:
	/**
	 * get weights getter
	 * @return: the weights feild
	 */
	Matrix getWeights() const;

	/**
	 * gt bias getter
	 * @return: the bias field
	 */
	Matrix getBias() const;

	/**
	 * get activation field
	 * @return: activation filed
	 */
	Activation getActivation() const;

	// OPERATORS:

	/**
	 * operator () to the dense object
	 * @param x: the matrix x we applying densing on
	 * @return: a matrix
	 */
	Matrix operator()(Matrix &x);
};


#endif //EX1_DENSE_H
