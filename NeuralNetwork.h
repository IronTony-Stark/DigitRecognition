//*******************************************
//    Project: Machine Learning "Hello World!"
//    Developed by Iron Tony
//    on 01.05.2020
//    Version 3.2
//*******************************************

#pragma once

#include "Math.h"
#include "Matrix.h"

class NeuralNetwork
{
	using ActFn = Matrix (*)(const Matrix&);
	using PreprocessFn = std::pair<Matrix, Matrix> (*)(const double* input);
	
public:
	NeuralNetwork(size_t inputNodes, size_t hiddenNodes, size_t outputNodes, 
		PreprocessFn prepFn, float learningRate = 0.1, ActFn = sigmoid);
	~NeuralNetwork() = default;
	
	void train(double** data, size_t examplesNum, size_t epochs = 1);
	const Matrix predict(const Matrix& features) const;
	
	std::pair<float, bool*> test(double** data, size_t examplesNum) const;
	
	void saveModel(const char* wihPath, const char* whoPath);
	void loadModel(const char* wihPath, const char* whoPath);

	NeuralNetwork(const NeuralNetwork&) = delete;
	NeuralNetwork& operator=(const NeuralNetwork&) = delete;
	NeuralNetwork(NeuralNetwork&&) = delete;
	NeuralNetwork& operator=(NeuralNetwork&&) = delete;
	
private:
	size_t _iNodes, _hNodes, _oNodes;
	Matrix _weightsInputHidden, _weightsHiddenOutput;
	float _lr;
	ActFn _actFn;
	PreprocessFn _prepFn;
	
	void train(const Matrix& features, const Matrix& targets);
};

