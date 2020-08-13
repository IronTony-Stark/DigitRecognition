//*******************************************
//    Project: Machine Learning "Hello World!"
//    Developed by Iron Tony
//    on 01.05.2020
//    Version 3.2
//*******************************************

#include <random>
#include "Matrix.h"

Matrix::Matrix(const size_t rows, const size_t cols)
	: _rows(rows), _cols(cols), _arr(new double[rows * cols] { 0 })
{}

Matrix::Matrix(const Matrix& m)
	: _rows(m.rows()), _cols(m.cols()), _arr(new double[m.rows() * m.cols()])
{
	for (size_t i = 0; i < rows(); ++i)
		for (size_t j = 0; j < cols(); ++j)
			this->operator()(i, j) = m(i, j);
}

Matrix::Matrix(Matrix&& m) noexcept
	: _rows(m.rows()), _cols(m.cols()), _arr(m.arr())
{
	m._arr = nullptr;
}

Matrix& Matrix::operator=(const Matrix& m)
{
	_rows = m.rows();
	_cols = m.cols();

	delete[] _arr;

	_arr = new double[_rows * _cols];
	for (size_t i = 0; i < rows(); ++i)
		for (size_t j = 0; j < cols(); ++j)
			this->operator()(i, j) = m(i, j);

	return *this;
}

Matrix& Matrix::operator=(Matrix&& m) noexcept
{
	_rows = m.rows();
	_cols = m.cols();

	delete[] _arr;
	_arr = m.arr();
	m._arr = nullptr;

	return *this;
}

Matrix::~Matrix()
{
	delete[] _arr;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
	for (size_t i = 0; i < m.rows(); ++i)
	{
		for (size_t j = 0; j < m.cols(); ++j)
		{
			os << m(i, j) << " ";
		}
		os << std::endl;
	}

	return os;
}

std::ostream& operator<<(std::ostream& os, const Matrix::IndexOutOfBounds& iob)
{
	os << "Index Out Of Bounds{row: " << iob._row << ", col: " << iob._col << "}";

	return os;
}

double Matrix::operator()(const size_t i, const size_t j) const
{
	if (i >= _rows || j >= _cols)
		throw IndexOutOfBounds(i, j);
	
	return _arr[i * _cols + j];
}

double& Matrix::operator()(const size_t i, const size_t j)
{
	if (i >= _rows || j >= _cols)
		throw IndexOutOfBounds(i, j);

	return _arr[i * _cols + j];
}

Matrix& Matrix::operator+=(const Matrix& m)
{
	if (rows() != m.rows() || cols() != m.cols())
		throw std::invalid_argument("+= Matrices have different dimensions");
	
	for (size_t i = 0; i < rows(); ++i)
		for (size_t j = 0; j < cols(); ++j)
			this->operator()(i, j) += m(i, j);

	return *this;
}

Matrix transposed(const Matrix& m)
{
	Matrix res(m.cols(), m.rows());
	
	for (size_t i = 0; i < res.rows(); ++i)
		for (size_t j = 0; j < res.cols(); ++j)
			res(i, j) = m(j, i);

	return res;
}

void fillRandom(Matrix& m, float lowerBound, float upperBound)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	const std::uniform_real_distribution<double> randomReal(lowerBound, upperBound);

	for (size_t i = 0; i < m.rows(); ++i)
	{
		for (size_t j = 0; j < m.cols(); ++j)
		{
			m(i, j) = randomReal(generator);
		}
	}
}
