//
// Created by Rina Karnauch on 12/06/2020.
//

#include "Dense.h"
#include "Activation.h"
#include "Matrix.h"



// C'TORS:

/**
 * constructor
 * @param w: weights feild
 * @param bias: bias feild
 * @param actType: act type feild
 */
Dense::Dense(const Matrix &w, const Matrix &bias, const Activation &actType) : _w(w), _bias(bias),
																			   _act
																					   (actType)
{};

// Methods

/**
 * get activation field
 * @return: activation filed
 */
Activation Dense::getActivation() const
{
	return _act;
}

/**
 * gt bias getter
 * @return: the bias field
 */
Matrix Dense::getBias() const
{
	return _bias;
}

/**
 * get weights getter
 * @return: the weights feild
 */
Matrix Dense::getWeights() const
{
	return _w;
}

/**
 * operator () to the dense object
 * @param x: the matrix x we applying densing on
 * @return: a matrix
 */
Matrix Dense::operator()(Matrix &x)
{

	Matrix mul = (_w) * (x);
	mul = mul + _bias;

	Activation a = _act;
	mul = (a)(mul);
	return mul;
}