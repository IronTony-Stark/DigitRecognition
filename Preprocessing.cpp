//*******************************************
//    Project: Machine Learning "Hello World!"
//    Developed by Iron Tony
//    on 01.05.2020
//    Version 3.2
//*******************************************

#include "Preprocessing.h"
#include "Constants.h"
#include "Matrix.h"

Matrix preprocessFeatures(const double* data)
{
	Matrix res(INPUT_NODES, 1);

	for (size_t i = 0; i < INPUT_NODES; ++i)
		res(i, 0) = data[i + 1] / 255 * 0.99 + 0.01;

	return res;
}

Matrix preprocessTargets(const double* data)
{
	Matrix res(OUTPUT_NODES, 1);

	for (size_t i = 0; i < OUTPUT_NODES; ++i)
		res(i, 0) = 0.01;

	res(data[0], 0) = 0.99;

	return res;
}

std::pair<Matrix, Matrix> createFeaturesTargets(const double* data)
{
	return std::make_pair(preprocessFeatures(data), preprocessTargets(data));
}