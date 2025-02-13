#include "AlgorythmsEntry.h"

AlgorythmSettings currentSettings;

bool doesPheromonsMustBeCleared = false;

int lastIteration = 0;

void ProcessDataSingleTime(OutputData* data, const int& N)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<double> dis(0.0, 1.0); 

	InputData inputCpy = *input;

	AlgorythmSettings currentSettingsCpy = currentSettings;

	/*
	{
		data->bestWayLength = 3.333;

		data->bestWay.clear();

		data->bestWay.push_back(1);
		data->bestWay.push_back(2);
		data->bestWay.push_back(3);


		int j;
		for (int i(0); i < N; i++)
		{
			for (j = 0; j < i; j++)
			{
				data->pheromons[i][j] = inputCpy.model[i][j];
			}
			for (j = i + 1; j < N; j++)
			{
				data->pheromons[i][j] = inputCpy.model[i][j];
			}
		}

	}
	*/

	std::vector<std::vector<double>> wishToGoIn(N, std::vector<double>(N, 0));

	for (int i(0); i < N; i++)
	{
		for (int j(0); j < N; j++)
		{
			wishToGoIn[i][j] = 
				pow(inputCpy.model[i][j], currentSettingsCpy.lengthEffect) 
				* 
				pow(data->pheromons[i][j], currentSettingsCpy.pheromonesEffect);
		}
	}

	std::vector<double> wishToRow(N, 0);

	for (int i(0); i < N; i++)
	{
		for (int j(0); j < N; j++)
		{
			wishToRow[i] += wishToGoIn[i][j];
		}
	}

	currentSettingsCpy.MaxTransitionsNumber;

	std::vector<std::vector<int>> antWay(currentSettingsCpy.AntsNumber);
	std::vector<double> antWayLength(currentSettingsCpy.AntsNumber, 1);

	std::vector<double> chanceToGo(N, 0);
	std::vector<double> notVisited(N, 0);

	double wishToRowLocal;

	double roulette;
	double tempRandom;

	for (int i(0); i < antWay.size(); i++)
	{
		antWay[i].reserve(currentSettingsCpy.MaxTransitionsNumber + 1);

		antWay[i].push_back(0);

		for (int j(0); j < notVisited.size(); j++)
		{
			notVisited[j] = true;
		}

		for (int j(1); j < currentSettingsCpy.MaxTransitionsNumber; j++)
		{

			wishToRowLocal = wishToRow[antWay[i][j - 1]];

			for (int k(0); k < j; k++)
			{
				wishToRowLocal -= wishToGoIn[antWay[i][j - 1]][antWay[i][k]];
			}

			for (int k(0); k < chanceToGo.size(); k++)
			{
				if (notVisited[k])
				{
					chanceToGo[k] = wishToGoIn[antWay[i][j - 1]][k] / wishToRowLocal;
				}
				else
				{
					chanceToGo[k] = 0;
				}
			}

			roulette = 0.;
			tempRandom = dis(gen);

			for (int k(0); k < chanceToGo.size(); k++)
			{
				roulette += chanceToGo[k];
				if (roulette >= tempRandom)
				{
					antWay[i].push_back(k);
					break;
				}
			}

			if (antWay[i].size() < j + 1)
			{
				antWay[i].push_back(chanceToGo.size() - 1);
			}

			antWayLength[i] *= inputCpy.model[antWay[i][j - 1]][antWay[i][j]];

			if (antWay[i][j] == 0)
			{
				break;
			}

		}

		if (antWay[i][antWay[i].size() - 1] != 0)
		{
			antWay[i].push_back(0);

			antWayLength[i] += inputCpy.model[antWay[i][antWay[i].size() - 2]][antWay[i][antWay[i].size() - 2]];

		}

	}

	for (int i(0); i < data->pheromons.size(); i++)
	{
		for (int j(0); j < data->pheromons.size(); j++)
		{
			data->pheromons[i][j] *= currentSettingsCpy.EvaporationCoefficient;
		}
	}

	double pheromonsLeave;

	double bestResult = 0;
	int bestResultIndex = 0;

	for (int i(0); i < antWay.size(); i++)
	{

		pheromonsLeave = currentSettingsCpy.lengthToPheromonEffect * antWayLength[i];

		for (int j(1); j < antWay[i].size(); j++)
		{
			data->pheromons[antWay[i][j - 1]][antWay[i][j]] += pheromonsLeave;
		}

	}

	double maxPheromon;
	int maxPheromonIndex;

	data->bestWayLength = 1;

	data->bestWay.clear();
	data->bestWay.reserve(currentSettingsCpy.MaxTransitionsNumber + 1);
	data->bestWay.push_back(0);

	for (int i(1); i < currentSettingsCpy.MaxTransitionsNumber; i++)
	{
		maxPheromon = 0;
		maxPheromonIndex = 0;
		for (int j(0); j < N; j++)
		{
			if (output->pheromons[data->bestWay[i - 1]][j] > maxPheromon)
			{
				maxPheromon = output->pheromons[data->bestWay[i - 1]][j];
				maxPheromonIndex = j;
			}
		}

		data->bestWay.push_back(maxPheromonIndex);

		data->bestWayLength *= inputCpy.model[data->bestWay[i - 1]][data->bestWay[i]];

		if (maxPheromonIndex == 0)
		{
			break;
		}
	}

	if (data->bestWay[data->bestWay.size() - 1] != 0)
	{

		data->bestWayLength *= inputCpy.model[data->bestWay[data->bestWay.size() - 1]][0];

		data->bestWay.push_back(0);

	}

}

void ProcessDataEntry()
{

	OutputData data1;
	OutputData data2;

	OutputData *front;
	OutputData *background;

	{

		int aVeryLot = 100;

		data1.pheromons.resize(aVeryLot);
		for (int i(0); i < data1.pheromons.size(); i++)
		{
			data1.pheromons[i].resize(aVeryLot);
			for (int j(0); j < data1.pheromons.size(); j++)
			{
				data1.pheromons[i][j] = 0.5;
			}
		}
	}

	{

		int aVeryBigWay = 10;

		data1.bestWay.reserve(aVeryBigWay);

	}

	data2 = data1;

	front = &data1;
	background = &data2;

	while (input == nullptr);

	output = front;

	int N, j;

	lastIteration = 0;

	while (doContinue)
	{

		N = input->size;

		for (int i(0); i < N; i++)
		{
			for (j = 0; j < i; j++)
			{
				background->pheromons[i][j] = front->pheromons[i][j];
			}
			for (j = i + 1; j < N; j++)
			{
				background->pheromons[i][j] = front->pheromons[i][j];
			}
		}

		if (doesPheromonsMustBeCleared)
		{

			for (int i(0); i < N; i++)
			{
				for (j = 0; j < i; j++)
				{
					background->pheromons[i][j] = 0.5;
				}
				for (j = i + 1; j < N; j++)
				{
					background->pheromons[i][j] = 0.5;
				}
			}

			lastIteration = 0;

			doesPheromonsMustBeCleared = false;
		}

		ProcessDataSingleTime(background, N);

		output = background;

		background = front;

		front = output;

		lastIteration++;
	}
}