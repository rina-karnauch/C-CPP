//
// MlpNetwork H file
//

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include <iostream>
#include "Digit.h"
#include "Dense.h"

#define MLP_SIZE 4

const MatrixDims imgDims = {28, 28};
const MatrixDims weightsDims[] = {{128, 784},
								  {64,  128},
								  {20,  64},
								  {10,  20}};
const MatrixDims biasDims[] = {{128, 1},
							   {64,  1},
							   {20,  1},
							   {10,  1}};

/**
 * class of the MlpNetwork we create
 */
class MlpNetwork
{
private:

	Dense _R1;
	Dense _R2;
	Dense _R3;
	Dense _R4;

public:

	/**
	 * a constructor
	 * @param weights: the weights array
	 * @param biases: the biases array
	 */
	MlpNetwork(const Matrix (&weights)[MLP_SIZE], const Matrix (&biases)[MLP_SIZE]) :
			_R1(weights[0], biases[0], Activation(Relu)),
			_R2(weights[1], biases[1], Activation(Relu)),
			_R3(weights[2], biases[2], Activation(Relu)),
			_R4(weights[3], biases[3], Activation(Softmax))
	{};

	// METHODS:

	/**
	 * a function to get the digit from the img
	 * @param input: the matrix of img
	 * @return: digit object
	 */
	Digit operator()(const Matrix &input);

};


#endif // MLPNETWORK_H
