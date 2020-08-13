//*******************************************
//    Project: Machine Learning "Hello World!"
//    Developed by Iron Tony
//    on 01.05.2020
//    Version 3.2
//*******************************************

#include <fstream>
#include <string>      
#include <sstream>
#include "Utils.h"
#include "Matrix.h"

std::pair<size_t, size_t> maxValueIndex(const Matrix& m)
{
	std::pair<size_t, size_t> max = std::make_pair(0, 0);
	
	for (size_t i = 0; i < m.rows(); ++i)
	{
		for (size_t j = 0; j < m.cols(); ++j)
		{
			if (m(i, j) > m(max.first, max.second))
			{
				max.first = i;
				max.second = j;
			}
		}
	}

	return max;
}

void readCSVFile(const char* fileName, double** buffer, const size_t quantity)
{
	std::ifstream file(fileName, std::ios_base::in);
	if (!file.is_open())
	{
		std::cout << "File not found" << std::endl;
		return;
	}

	std::string line;
	for (size_t i = 0; i < quantity; ++i)
	{
		std::getline(file, line);
		std::stringstream ss(line);

		size_t j = 0;
		while (std::getline(ss, line, ',')) {
			buffer[i][j++] = std::stod(line);
		}
	}
}

void deserialize(Matrix& m, const char* const path)
{
	std::ifstream file(path, std::ios::in);
	if (!file.is_open())
	{
		std::cout << "File not found: " << path << std::endl;
		return;
	}

	for (size_t i = 0; i < m.rows(); ++i)
		for (size_t j = 0; j < m.cols(); ++j)
			file >> m(i, j);

	file.close();
}

void serialize(Matrix& m, const char* path)
{
	std::ofstream file(path, std::ios::out);
	if (!file.is_open())
	{
		std::cout << "File not found: " << path << std::endl;
		return;
	}

	for (size_t i = 0; i < m.rows(); ++i)
		for (size_t j = 0; j < m.cols(); ++j)
			file << m(i, j) << ' ';
}