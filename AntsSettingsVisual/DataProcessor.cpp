#include "PCH.h"
#include "AlgorythmsEntry.h"

AlgorythmSettings currentSettings;

bool doesPheromonsMustBeCleared = false;

SharedData sharedData;

OutputData outputCandidate;
AlgorythmSettings settingsCandidate;
bool doMutate;

void SharedPrecalculationOrder1(OutputData* data, const int& N, SharedData& sharedData)
{

	sharedData.wishToGoIn = std::vector<std::vector<double>>(N, std::vector<double>(N, 0));

	for (int i(0); i < N; i++)
	{
		for (int j(0); j < N; j++)
		{
			sharedData.wishToGoIn[i][j] =
				pow(sharedData.inputCpy->model[i][j], sharedData.currentSettingsCpy.lengthEffect)
				*
				pow(data->pheromons[i][j], sharedData.currentSettingsCpy.pheromonesEffect);
		}
	}

	sharedData.wishToRow = std::vector<double>(N, 0);

	for (int i(0); i < N; i++)
	{
		for (int j(0); j < N; j++)
		{
			sharedData.wishToRow[i] += sharedData.wishToGoIn[i][j];
		}
	}

	sharedData.antWay = std::vector<std::vector<int>>(sharedData.currentSettingsCpy.AntsNumber);
	sharedData.antWayLength = std::vector<double>(sharedData.currentSettingsCpy.AntsNumber, 1);

	sharedData.scoutAntWay = std::vector<std::vector<int>>(sharedData.currentSettingsCpy.ScoutsNumber);
	sharedData.scoutAntWayLength = std::vector<double>(sharedData.currentSettingsCpy.ScoutsNumber, 1);

}

void SharedPostcalculationOrder3(OutputData* data, const int& N, SharedData& sharedData)
{
	for (int i(0); i < data->pheromons.size(); i++)
	{
		for (int j(0); j < data->pheromons.size(); j++)
		{
			data->pheromons[i][j] *= sharedData.currentSettingsCpy.EvaporationCoefficient;
		}
	}


}

void SharedPostcalculationOrder5(OutputData* data, const int& N, SharedData& sharedData)
{
	data->iteration++;

	double maxPheromon;
	int maxPheromonIndex;


	double oldBestWayLength = 1;
	double newBestWayLength = 1;

	std::vector<int> newBestWay;
	
	newBestWay.reserve(sharedData.currentSettingsCpy.MaxTransitionsNumber + 1);
	newBestWay.push_back(0);

	for (int i(1); i < sharedData.currentSettingsCpy.MaxTransitionsNumber; i++)
	{
		maxPheromon = 0;
		maxPheromonIndex = 0;
		for (int j(0); j < N; j++)
		{
			if (output.load()->pheromons[newBestWay[i - 1]][j] > maxPheromon)
			{
				maxPheromon = output.load()->pheromons[newBestWay[i - 1]][j];
				maxPheromonIndex = j;
			}
		}

		newBestWay.push_back(maxPheromonIndex);

		newBestWayLength *= sharedData.inputCpy->model[newBestWay[i - 1]][newBestWay[i]];

		if (maxPheromonIndex == 0)
		{
			break;
		}
	}

	if (newBestWay[newBestWay.size() - 1] != 0)
	{

		newBestWayLength *= sharedData.inputCpy->model[newBestWay[newBestWay.size() - 1]][0];

		newBestWay.push_back(0);

	}

	for (int i(1); i < data->bestWay.size(); i++)
	{
		oldBestWayLength *= sharedData.inputCpy->model[data->bestWay[i - 1]][data->bestWay[i]];
	}

	if (newBestWayLength / (newBestWay.size() - 1.) > oldBestWayLength / (data->bestWay.size() - 1.))
	{
		data->bestWayLength = newBestWayLength;
		data->bestWay = newBestWay;
	}
	else
	{
		data->bestWayLength = oldBestWayLength;
	}

}

void IndividualCalculationOrder2(OutputData* data, const int& N, const int& number, SharedData& sharedData)
{ 

	std::vector<double> chanceToGo(N, 0);
	std::vector<double> notVisited(N, 0);

	double wishToRowLocal;

	double roulette;
	double tempRandom;

	int lim = sharedData.currentSettingsCpy.AntsNumber / sharedData.currentSettingsCpy.ColoniesNumber * (number + 1);

	for (int i(sharedData.currentSettingsCpy.AntsNumber / sharedData.currentSettingsCpy.ColoniesNumber * number); i < lim; i++)
	{
		sharedData.antWay[i].reserve(sharedData.currentSettingsCpy.MaxTransitionsNumber + 1);

		sharedData.antWay[i].push_back(0);

		for (int j(0); j < notVisited.size(); j++)
		{
			notVisited[j] = true;
		}

		for (int j(1); j < sharedData.currentSettingsCpy.MaxTransitionsNumber; j++)
		{

			wishToRowLocal = sharedData.wishToRow[sharedData.antWay[i][j - 1]];

			for (int k(0); k < j; k++)
			{
				wishToRowLocal -= sharedData.wishToGoIn[sharedData.antWay[i][j - 1]][sharedData.antWay[i][k]];
			}

			for (int k(0); k < chanceToGo.size(); k++)
			{
				if (notVisited[k])
				{
					chanceToGo[k] = sharedData.wishToGoIn[sharedData.antWay[i][j - 1]][k] / wishToRowLocal;
				}
				else
				{
					chanceToGo[k] = 0;
				}
			}

			roulette = 0.;

			tempRandom = sharedData.dis->operator()(*sharedData.gen);

			for (int k(0); k < chanceToGo.size(); k++)
			{
				roulette += chanceToGo[k];
				if (roulette >= tempRandom)
				{
					sharedData.antWay[i].push_back(k);
					break;
				}
			}

			if (sharedData.antWay[i].size() < j + 1)
			{
				sharedData.antWay[i].push_back(chanceToGo.size() - 1);
			}

			sharedData.antWayLength[i] *= sharedData.inputCpy->model[sharedData.antWay[i][j - 1]][sharedData.antWay[i][j]];

			if (sharedData.antWay[i][j] == 0)
			{
				break;
			}

		}

		if (sharedData.antWay[i][sharedData.antWay[i].size() - 1] != 0)
		{
			sharedData.antWay[i].push_back(0);

			sharedData.antWayLength[i] *= 
				sharedData.inputCpy->
					model	[sharedData.antWay[i][sharedData.antWay[i].size() - 2]]
							[sharedData.antWay[i][sharedData.antWay[i].size() - 1]];

		}

	}


	lim = sharedData.currentSettingsCpy.ScoutsNumber / sharedData.currentSettingsCpy.ColoniesNumber * (number + 1);

	std::vector<double> scoutWishToGoIn(N, 0);

	for (int i(sharedData.currentSettingsCpy.ScoutsNumber / sharedData.currentSettingsCpy.ColoniesNumber * number); i < lim; i++)
	{
		sharedData.scoutAntWay[i].reserve(sharedData.currentSettingsCpy.MaxTransitionsNumber + 1);

		sharedData.scoutAntWay[i].push_back(0);

		for (int j(0); j < notVisited.size(); j++)
		{
			notVisited[j] = true;
		}

		for (int j(1); j < sharedData.currentSettingsCpy.MaxTransitionsNumber; j++)
		{
			wishToRowLocal = 0;

			for (int k(0); k < scoutWishToGoIn.size(); k++)
			{
				if (notVisited[k])
				{
					scoutWishToGoIn[k] =
						pow(sharedData.inputCpy->model[sharedData.scoutAntWay[i][j - 1]][k], sharedData.currentSettingsCpy.ScoutsRandomness);
				}
				else
				{
					scoutWishToGoIn[k] = 0;
				}

				wishToRowLocal += scoutWishToGoIn[k];
			}

			for (int k(0); k < chanceToGo.size(); k++)
			{
				if (notVisited[k])
				{
					chanceToGo[k] = scoutWishToGoIn[k] / wishToRowLocal;
				}
				else
				{
					chanceToGo[k] = 0;
				}
			}

			roulette = 0.;
			tempRandom = sharedData.dis->operator()(*sharedData.gen);

			for (int k(0); k < chanceToGo.size(); k++)
			{
				roulette += chanceToGo[k];
				if (roulette >= tempRandom)
				{
					sharedData.scoutAntWay[i].push_back(k);
					break;
				}
			}

			if (sharedData.scoutAntWay[i].size() < j + 1)
			{
				sharedData.scoutAntWay[i].push_back(chanceToGo.size() - 1);
			}

			sharedData.scoutAntWayLength[i] *= 
				sharedData.inputCpy->model
					[sharedData.scoutAntWay[i][j - 1]]
					[sharedData.scoutAntWay[i][j]];

			if (sharedData.scoutAntWay[i][j] == 0)
			{
				break;
			}

		}

		if (sharedData.scoutAntWay[i][sharedData.scoutAntWay[i].size() - 1] != 0)
		{
			sharedData.scoutAntWay[i].push_back(0);

			sharedData.scoutAntWayLength[i] *= 
				sharedData.inputCpy->model
					[sharedData.scoutAntWay[i][sharedData.scoutAntWay[i].size() - 2]]
					[sharedData.scoutAntWay[i][sharedData.scoutAntWay[i].size() - 1]];

		}

	}
}

void IndividualCalculationOrder4(OutputData* data, const int& N, const int& number, SharedData& sharedData)
{
	double pheromonsLeave;

	double bestResult = 0;
	int bestResultIndex = 0;

	int lim = sharedData.currentSettingsCpy.AntsNumber / sharedData.currentSettingsCpy.ColoniesNumber * (number + 1);

	for (int i(sharedData.currentSettingsCpy.AntsNumber / sharedData.currentSettingsCpy.ColoniesNumber * number); i < lim; i++)
	{

		pheromonsLeave = sharedData.currentSettingsCpy.lengthToPheromonEffect * sharedData.antWayLength[i];

		for (int j(1); j < sharedData.antWay[i].size(); j++)
		{
			data->pheromons[sharedData.antWay[i][j - 1]][sharedData.antWay[i][j]] += pheromonsLeave;
		}

	}
	
	
	lim = sharedData.currentSettingsCpy.ScoutsNumber / sharedData.currentSettingsCpy.ColoniesNumber * (number + 1);

	for (int i(sharedData.currentSettingsCpy.ScoutsNumber / sharedData.currentSettingsCpy.ColoniesNumber * number); i < lim; i++)
	{

		pheromonsLeave = sharedData.currentSettingsCpy.lengthToPheromonEffect * sharedData.scoutAntWayLength[i];

		for (int j(1); j < sharedData.scoutAntWay[i].size(); j++)
		{
			data->pheromons[sharedData.scoutAntWay[i][j - 1]][sharedData.scoutAntWay[i][j]] += pheromonsLeave;
		}

	}
}

void ProcessDataEntry()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));

	doMutate = false;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(0.0, 1.0);

	sharedData.rd = &rd;
	sharedData.gen = &gen;
	sharedData.dis = &dis;

	OutputData data1;
	OutputData data2;

	OutputData *front;
	OutputData *background;

	{

		int aVeryLot = 200;

		data1.pheromons.resize(aVeryLot);
		for (int i(0); i < data1.pheromons.size(); i++)
		{

			data1.pheromons[i].resize(aVeryLot);
			for (int j(0); j < data1.pheromons.size(); j++)
			{
				if (i == j)
				{
					data1.pheromons[i][j] = 0.;
				}
				else {
					data1.pheromons[i][j] = 0.5;
				}
			}
		}

		int aVeryBigWay = 200;

		data1.bestWay.reserve(aVeryBigWay);

		data1.iteration = 0;

	}

	data2 = data1;

	front = &data1;
	background = &data2;

	while (input == nullptr)
	{
		continue;
	}

	output = front;

	int N, j;

	InputData* local_input;

	while (doContinue)
	{

//		sharedData.inputCpy = *input.load(std::memory_order_acquire);

//		 = std::make_shared<InputData>(*input.load(std::memory_order_acquire));

		auto inputCpy = std::atomic_load(&input); // �������� ������
		if (inputCpy) {
			sharedData.inputCpy = std::make_shared<InputData>(*inputCpy); // ������� ����
		}

		N = sharedData.inputCpy->size;

		sharedData.currentSettingsCpy = currentSettings;

		background->pheromons = front->pheromons;

		background->iteration = front->iteration;
		
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

			background->iteration = 0;

			doesPheromonsMustBeCleared = false;
		}

		SharedPrecalculationOrder1(background, N, sharedData);

		std::vector<std::thread*> threads(sharedData.currentSettingsCpy.ColoniesNumber);

		for (int i(0); i < threads.size(); i++)
		{
			threads[i] = new std::thread(IndividualCalculationOrder2, background, N, i, std::ref(sharedData));
		}

		for (int i(0); i < threads.size(); i++)
		{
			threads[i]->join();
		}

		SharedPostcalculationOrder3(background, N, sharedData);

		for (int i(0); i < threads.size(); i++)
		{
			delete threads[i];
			threads[i] = new std::thread(IndividualCalculationOrder4, background, N, i, std::ref(sharedData));
		}

		for (int i(0); i < threads.size(); i++)
		{
			threads[i]->join();
			delete threads[i];
		}

		SharedPostcalculationOrder5(background, N, sharedData);

		output.store(background, std::memory_order_release);

		background = front;

		front = output.load(std::memory_order_acquire);

		if (doMutate)
		{
			currentSettings = settingsCandidate;

			data1 = outputCandidate;
			data2 = data1;

			doMutate = false;
		}

	}
}