//*******************************************
//    Project: Machine Learning "Hello World!"
//    Developed by Iron Tony
//    on 01.05.2020
//    Version 3.2
//*******************************************

#pragma once

#include <cmath>
#include "Matrix.h"
#include "Constants.h"

inline double sigmoid(const double& x)
{
	return 1 / (1 + pow(EXP, -x));
}

Matrix sigmoid(const Matrix&);

Matrix dot(const Matrix&, const Matrix&);

Matrix operator*(const Matrix& a, const Matrix& b);
Matrix operator+(const Matrix& a, const Matrix& b);
Matrix operator-(const Matrix& a, const Matrix& b);

Matrix operator*(const double&, const Matrix&);
Matrix operator*(const Matrix&, const double&);
Matrix operator/(const double&, const Matrix&);
Matrix operator/(const Matrix&, const double&);
Matrix operator+(const double&, const Matrix&);
Matrix operator+(const Matrix&, const double&);
Matrix operator-(const double&, const Matrix&);
Matrix operator-(const Matrix&, const double&);
