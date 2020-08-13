//*******************************************
//    Project: Machine Learning "Hello World!"
//    Developed by Iron Tony
//    on 01.05.2020
//    Version 3.2
//*******************************************

#pragma once

#include <iostream>

class Matrix
{
public:
	struct IndexOutOfBounds;
	
	explicit Matrix(size_t rows, size_t cols);
	Matrix(const Matrix&);
	Matrix(Matrix&&) noexcept;
	Matrix& operator=(const Matrix&);
	Matrix& operator=(Matrix&&) noexcept;
	~Matrix();
	
	size_t rows() const { return _rows; }
	size_t cols() const { return _cols; }
	double* arr() const { return _arr; }
	
	double operator()(const size_t i, const size_t j) const;
	double& operator()(const size_t i, const size_t j);

	Matrix& operator+=(const Matrix& m);

private:
	size_t _rows, _cols;
	double* _arr;
};

struct Matrix::IndexOutOfBounds final : std::exception
{
	size_t _row;
	size_t _col;

	explicit IndexOutOfBounds(const size_t row, const size_t col) : _row(row), _col(col) {}
	
	char const* what() const override { return "IndexOutOfBounds Exception"; }
};

std::ostream& operator<<(std::ostream& os, const Matrix& m);
std::ostream& operator<<(std::ostream& os, const Matrix::IndexOutOfBounds& iob);

Matrix transposed(const Matrix& m);

void fillRandom(Matrix&, float lowerBound, float upperBound);
