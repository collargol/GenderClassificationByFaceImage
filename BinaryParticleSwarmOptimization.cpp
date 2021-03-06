#include <iostream>
#include <sstream>
#include <ctime>

#include "particle.h"
#include "algorithm.h"
#include "csvfilereaderwriter.h"

int main(int argc, char * argv[])
{
	std::string inputFilePath;
	std::string outputFilePath;
	size_t objFunctionIdentifier;
	std::stringstream strStream;
	if (argc > 1)
		strStream << argv[0];

	switch (argc)
	{
	default:
	case 1:
		inputFilePath = "gender_data.csv";
		outputFilePath = "solution.csv";
		objFunctionIdentifier = 0;
		break;
	case 2:
		strStream >> objFunctionIdentifier;
		inputFilePath = "gender_data.csv";
		outputFilePath = "solution.csv";
		break;
	case 3:
		strStream >> objFunctionIdentifier;
		inputFilePath = std::string(argv[1]);
		outputFilePath = "solution.csv";
		break;
	case 4:
		strStream >> objFunctionIdentifier;
		inputFilePath = std::string(argv[1]);
		outputFilePath = std::string(argv[2]);
		break;
	}
	std::cout << "inputFilePath: " << inputFilePath << std::endl;
	std::cout << "outputFilePath: " << outputFilePath << std::endl;

	srand(static_cast<unsigned int>(time(0)));

	CSVFileReaderWriter csvRW(inputFilePath, outputFilePath);
	std::unique_ptr<DataSet> dataset(csvRW.readCSV());
	size_t particlesNumber = 100;
	size_t iterations = 200;
	float maxVelocity = 6.f;

	Algorithm algorithm(particlesNumber, dataset->featuresNumber, iterations, dataset, objFunctionIdentifier, maxVelocity, 1.0f, 1.0f, 0.03f);
	algorithm.performOptimization();

	csvRW.writeSolutionCSV(algorithm.getSolution());
}

