//*******************************************
//    Project: Machine Learning "Hello World!"
//    Developed by Iron Tony
//    on 01.05.2020
//    Version 3.2
//*******************************************

#pragma once

#include <xutility>

class Matrix;

Matrix preprocessFeatures(const double* data);
Matrix preprocessTargets(const double* data);
std::pair<Matrix, Matrix> createFeaturesTargets(const double* data);