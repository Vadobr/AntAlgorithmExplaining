#pragma once
#include "PCHNames.h"

extern bool doContinue;

void GetDataEntry();

void ProcessDataEntry();

void EvolutionEntry();

void AlgorythmsEntry();

void AlgotythmsJoin();

struct InputData {

	int size;

	std::vector<std::vector<double>> model;
	
	InputData();
	InputData(const InputData& other);
	InputData& operator=(const InputData& other);
	InputData(InputData&& other) noexcept;
	InputData& operator=(InputData&& other) noexcept;

};

struct OutputData {

	double bestWayLength;

	std::vector<int> bestWay;

	std::vector<std::vector<double>> pheromons;

	int iteration;

	OutputData();
	OutputData(const OutputData& other);
	OutputData& operator=(const OutputData& other);
	OutputData(OutputData&& other) noexcept;
	OutputData& operator=(OutputData&& other) noexcept;

};

extern std::atomic <InputData*> input;

extern std::atomic <OutputData*> output;

struct AlgorythmSettings
{
	double lengthEffect = 1.;
	double pheromonesEffect = 1.;
	double lengthToPheromonEffect = 0.01;
	double EvaporationCoefficient = 0.99;
	int MaxTransitionsNumber = 5;
	int AntsNumber = 1000;
	int ScoutsNumber = 100;
	int ColoniesNumber = 1;
	double ScoutsRandomness = 2.;
	double GenerationPopulation = 0.;
	int iterationsNumberToMutate = 100;
	int generation = 0;
};

extern AlgorythmSettings currentSettings;

extern bool doesPheromonsMustBeCleared;

struct SharedData
{
	std::random_device* rd;
	std::mt19937* gen;
	std::uniform_real_distribution<double>* dis;

	InputData inputCpy;
	AlgorythmSettings currentSettingsCpy;

	std::vector<std::vector<double>> wishToGoIn;

	std::vector<std::vector<int>> antWay;
	std::vector<double> antWayLength;

	std::vector<std::vector<int>> scoutAntWay;
	std::vector<double> scoutAntWayLength;

	std::vector<double> wishToRow;
};

void SharedPrecalculationOrder1(OutputData* data, const int& N, SharedData& sharedData);
void SharedPostcalculationOrder3(OutputData* data, const int& N, SharedData& sharedData);
void SharedPostcalculationOrder5(OutputData* data, const int& N, SharedData& sharedData);
void IndividualCalculationOrder2(OutputData* data, const int& N, const int& number, SharedData& sharedData);
void IndividualCalculationOrder4(OutputData* data, const int& N, const int& number, SharedData& sharedData);

extern AlgorythmSettings generationZeroSettings;

extern OutputData outputCandidate;
extern AlgorythmSettings settingsCandidate;
extern bool doMutate;

extern bool skipGenerationZero;
extern bool skipCurrentGeneration;