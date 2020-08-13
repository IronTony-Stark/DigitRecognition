//*******************************************
//    Project: Machine Learning "Hello World!"
//    Developed by Iron Tony
//    on 01.05.2020
//    Version 3.2
//*******************************************

#include "NeuralNetwork.h"
#include "Matrix.h"
#include "Math.h"
#include "Utils.h"

NeuralNetwork::NeuralNetwork(const size_t inputNodes, const size_t hiddenNodes, const size_t outputNodes,
	const PreprocessFn prepFn, const float learningRate, const ActFn actFn) :
	_iNodes(inputNodes), _hNodes(hiddenNodes), _oNodes(outputNodes),
	_weightsInputHidden(Matrix(_hNodes, _iNodes)),
	_weightsHiddenOutput(Matrix(_oNodes, _hNodes)),
	_lr(learningRate), _actFn(actFn), _prepFn(prepFn)
{
	fillRandom(_weightsInputHidden, -0.5, 0.5);
	fillRandom(_weightsHiddenOutput, -0.5, 0.5);
}

void NeuralNetwork::train(double** data, const size_t examplesNum, const size_t epochs)
{
	for (size_t i = 0; i < epochs; ++i)
	{
		for (size_t j = 0; j < examplesNum; ++j)
		{
			const std::pair<Matrix, Matrix> featuresTargets = _prepFn(data[j]);
			train(featuresTargets.first, featuresTargets.second);

		}
	}
}

const Matrix NeuralNetwork::predict(const Matrix& features) const
{
	const Matrix hiddenInputs = dot(_weightsInputHidden, features);
	const Matrix hiddenOutputs = _actFn(hiddenInputs);

	const Matrix finalInputs = dot(_weightsHiddenOutput, hiddenOutputs);
	return _actFn(finalInputs);
}

std::pair<float, bool*> NeuralNetwork::test(double** data, const size_t examplesNum) const
{
	size_t correctGuesses = 0;
	bool* guesses = new bool[examplesNum];
	
	for (size_t i = 0; i < examplesNum; ++i)
	{
		const std::pair<Matrix, Matrix> featuresTargets = _prepFn(data[i]);

		const size_t guess = maxValueIndex(predict(featuresTargets.first)).first;
		const size_t correct = maxValueIndex(featuresTargets.second).first;

		if (guess == correct)
		{
			++correctGuesses;
			guesses[i] = true;
		}
		else guesses[i] = false;
	}

	return std::make_pair(static_cast<float>(correctGuesses) / examplesNum, guesses);
}

void NeuralNetwork::saveModel(const char* wihPath, const char* whoPath)
{
	serialize(_weightsInputHidden, wihPath);
	serialize(_weightsHiddenOutput, whoPath);
}

void NeuralNetwork::loadModel(const char* const wihPath, const char* const whoPath)
{
	deserialize(_weightsInputHidden, wihPath);
	deserialize(_weightsHiddenOutput, whoPath);
}

void NeuralNetwork::train(const Matrix& features, const Matrix& targets)
{
	const Matrix hiddenInputs = dot(_weightsInputHidden, features);
	const Matrix hiddenOutputs = _actFn(hiddenInputs);

	const Matrix finalInputs = dot(_weightsHiddenOutput, hiddenOutputs);
	const Matrix finalOutputs = _actFn(finalInputs);

	const Matrix outputErrors = targets - finalOutputs;
	const Matrix hiddenErrors = dot(transposed(_weightsHiddenOutput), outputErrors);

	_weightsHiddenOutput += _lr * dot(outputErrors * finalOutputs * (1.0 - finalOutputs), transposed(hiddenOutputs));;
	_weightsInputHidden += _lr * dot(hiddenErrors * hiddenOutputs * (1.0 - hiddenOutputs), transposed(features));
}



