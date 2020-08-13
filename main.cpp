//*******************************************
//    Project: Machine Learning "Hello World!"
//    Developed by Iron Tony
//    on 01.05.2020
//    Version 3.2
//*******************************************

#include <iostream>
#include "Matrix.h"
#include "NeuralNetwork.h"
#include "Preprocessing.h"
#include "Utils.h"

using namespace std;

const size_t INPUT_NODES = 784; // Image size in pixels
const size_t HIDDEN_NODES = 100;
const size_t OUTPUT_NODES = 10;
const float LEARNING_RATE = 0.3f;

const char* const TRAIN_DATA_PATH = "mnist_train_100.csv";
const char* const TEST_DATA_PATH = "mnist_test_10.csv";

const char* const FILE_WIH = "model_wih.txt";
const char* const FILE_WHO = "model_who.txt";

const size_t NUM_TRAINING_EXAMPLES = 100;
const size_t NUM_TEST_EXAMPLES = 10;
const size_t NUM_EPOCHS = 3;

int main()
{
	auto* nn = new NeuralNetwork(INPUT_NODES, HIDDEN_NODES, OUTPUT_NODES, createFeaturesTargets, LEARNING_RATE);
	nn->loadModel(FILE_WIH, FILE_WHO); // Loading previously trained model
	
	auto** trainingData = new double* [NUM_TRAINING_EXAMPLES];
	for (size_t i = 0; i < NUM_TRAINING_EXAMPLES; ++i)
		trainingData[i] = new double[INPUT_NODES + 1];
	readCSVFile(TRAIN_DATA_PATH, trainingData, NUM_TRAINING_EXAMPLES);

	// cout << "Learning..." << endl;
	// nn->train(trainingData, NUM_TRAINING_EXAMPLES, NUM_EPOCHS);
	// nn->saveModel(FILE_WIH, FILE_WHO);
	// cout << "Finished" << endl;

	auto** testData = new double* [NUM_TEST_EXAMPLES];
	for (size_t i = 0; i < NUM_TEST_EXAMPLES; ++i)
		testData[i] = new double[INPUT_NODES + 1];
	
	readCSVFile(TEST_DATA_PATH, testData, NUM_TEST_EXAMPLES);
	const pair<float, bool*> result = nn->test(testData, NUM_TEST_EXAMPLES);
	
	cout << "Correct prediction rate: " << result.first << endl;
	cout << "Predictions results: ";
	for (size_t i = 0; i < NUM_TEST_EXAMPLES; ++i)
		cout << result.second[i] << " ";
	cout << "\n\n";
	
	for (size_t i = 0; i < NUM_TEST_EXAMPLES; ++i)
	{
		cout << "----------------------------------" << endl;
		const pair<Matrix, Matrix> featuresTargets = createFeaturesTargets(testData[i]);
		Matrix prediction = nn->predict(featuresTargets.first);
		Matrix correct = featuresTargets.second;
		
		cout << "Prediction: " << maxValueIndex(prediction).first << endl;
		cout << prediction << endl;
		cout << "Correct: " << maxValueIndex(correct).first << endl;
		cout << correct << endl;
	}

	delete[] result.second;
	for (size_t i = 0; i < NUM_TEST_EXAMPLES; ++i)
		delete[] testData[i];
	delete[] testData;
	for (size_t  i = 0; i < NUM_TRAINING_EXAMPLES; ++i)
		delete[] trainingData[i];
	delete[] trainingData;
	delete nn;
	
    return 0;
}

