#pragma once
#include "PCHNames.h"

extern bool doContinue;

void GetDataEntry();

void ProcessDataEntry();

void AlgorythmsEntry();

void AlgotythmsJoin();

struct InputData {

	int size;

	std::vector<std::vector<double>> model;

};

struct OutputData {

	double bestWayLength;

	std::vector<int> bestWay;

	std::vector<std::vector<double>> pheromons;

};

extern InputData* input;

extern OutputData* output;

struct AlgorythmSettings
{
	double lengthEffect = 1.;
	double pheromonesEffect = 2.5;
	double lengthToPheromonEffect = 0.3;
	double EvaporationCoefficient = 0.8;
	int MaxTransitionsNumber = 5;
	int AntsNumber = 90;
	int ScoutsNumber = 9;
	int ColoniesNumber = 1;
};

extern AlgorythmSettings currentSettings;

extern bool doesPheromonsMustBeCleared;

extern int lastIteration;