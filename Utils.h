//*******************************************
//    Project: Machine Learning "Hello World!"
//    Developed by Iron Tony
//    on 01.05.2020
//    Version 3.2
//*******************************************

#pragma once

#include <utility>

class Matrix;

std::pair<size_t, size_t> maxValueIndex(const Matrix&);
void readCSVFile(const char* fileName, double** buffer, const size_t quantity);
void deserialize(Matrix& m, const char* path);
void serialize(Matrix& m, const char* path);
