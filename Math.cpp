//*******************************************
//    Project: Machine Learning "Hello World!"
//    Developed by Iron Tony
//    on 01.05.2020
//    Version 3.2
//*******************************************

#include <iostream>
#include "Math.h"

const double EXP = std::exp(1.0);

Matrix sigmoid(const Matrix& m)
{
	Matrix res(m.rows(), m.cols());

	for (size_t i = 0; i < res.rows(); ++i)
		for (size_t j = 0; j < res.cols(); ++j)
			res(i, j) = sigmoid(m(i, j));

	return res;
}

Matrix dot(const Matrix& a, const Matrix& b)
{
	if (a.cols() != b.rows())
		throw std::invalid_argument("a.cols() must be equal to b.rows");

	Matrix res(a.rows(), b.cols());

	for (size_t i = 0; i < res.rows(); ++i) {
		for (size_t j = 0; j < res.cols(); ++j) {
			double sum = 0;

			for (size_t k = 0; k < a.cols(); k++)
				sum += a(i, k) * b(k, j);

			res(i, j) = sum;
		}
	}

	return res;
}

Matrix operator*(const Matrix& a, const Matrix& b)
{
	if (a.rows() != b.rows() || a.cols() != b.cols())
		throw std::invalid_argument("+ Matrices have different dimensions");

	Matrix res(a.rows(), a.cols());

	for (size_t i = 0; i < res.rows(); ++i)
		for (size_t j = 0; j < res.cols(); ++j)
			res(i, j) = a(i, j) * b(i, j);

	return res;
}

Matrix operator+(const Matrix& a, const Matrix& b)
{
	if (a.rows() != b.rows() || a.cols() != b.cols())
		throw std::invalid_argument("+ Matrices have different dimensions");

	Matrix res(a.rows(), a.cols());

	for (size_t i = 0; i < res.rows(); ++i)
		for (size_t j = 0; j < res.cols(); ++j)
			res(i, j) = a(i, j) + b(i, j);

	return res;
}

Matrix operator-(const Matrix& a, const Matrix& b)
{
	if (a.rows() != b.rows() || a.cols() != b.cols())
		throw std::invalid_argument("- Matrices have different dimensions");

	Matrix res(a.rows(), a.cols());

	for (size_t i = 0; i < res.rows(); ++i)
		for (size_t j = 0; j < res.cols(); ++j)
			res(i, j) = a(i, j) - b(i, j);

	return res;
}

Matrix operator*(const double& x, const Matrix& m)
{
	Matrix res(m.rows(), m.cols());

	for (size_t i = 0; i < res.rows(); ++i)
		for (size_t j = 0; j < res.cols(); ++j)
			res(i, j) = x * m(i, j);

	return res;
}

Matrix operator*(const Matrix& m, const double& x)
{
	return x * m;
}

Matrix operator/(const double& x, const Matrix& m)
{
	Matrix res(m.rows(), m.cols());

	for (size_t i = 0; i < res.rows(); ++i)
		for (size_t j = 0; j < res.cols(); ++j)
			res(i, j) = x / m(i, j);

	return res;
}

Matrix operator/(const Matrix& m, const double& x)
{
	Matrix res(m.rows(), m.cols());

	for (size_t i = 0; i < res.rows(); ++i)
		for (size_t j = 0; j < res.cols(); ++j)
			res(i, j) = m(i, j) / x;

	return res;
}

Matrix operator+(const double& x, const Matrix& m)
{
	Matrix res(m.rows(), m.cols());

	for (size_t i = 0; i < res.rows(); ++i)
		for (size_t j = 0; j < res.cols(); ++j)
			res(i, j) = x + m(i, j);

	return res;
}

Matrix operator+(const Matrix& m, const double& x)
{
	return x + m;
}

Matrix operator-(const double& x, const Matrix& m)
{
	Matrix res(m.rows(), m.cols());

	for (size_t i = 0; i < res.rows(); ++i)
		for (size_t j = 0; j < res.cols(); ++j)
			res(i, j) = x - m(i, j);

	return res;
}

Matrix operator-(const Matrix& m, const double& x)
{
	Matrix res(m.rows(), m.cols());

	for (size_t i = 0; i < res.rows(); ++i)
		for (size_t j = 0; j < res.cols(); ++j)
			res(i, j) = m(i, j) - x;

	return res;
}
