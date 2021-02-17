//
// Created by Rina Karnauch on 12/06/2020.
//

#include "MlpNetwork.h"

/**
* a function to get the digit from the img
* @param input: the matrix of img
* @return: digit object
*/
Digit MlpNetwork::operator()(const Matrix &input)
{
	Matrix mat = Matrix(input);

	mat = (_R1)(mat);
	mat = (_R2)(mat);
	mat = (_R3)(mat);
	mat = (_R4)(mat);

	float prob = -0.1f;
	int num = 0;
	for (int i = 0; i < 10; i++)
	{
		if (mat[i] > prob)
		{
			prob = mat[i];
			num = i;
		}
	}

	Digit d;
	d.probability = prob;
	d.value = num;

	return d;
}
