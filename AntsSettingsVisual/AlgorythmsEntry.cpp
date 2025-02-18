#include "PCH.h"
#include "AlgorythmsEntry.h"

bool doContinue;

std::shared_ptr<InputData> input;

std::atomic <OutputData*> output;

std::thread* DataReader;
std::thread* DataProcessor;;
std::thread* Evolutioneer;

void AlgorythmsEntry()
{
	doContinue = true;

	input = nullptr;
	output = nullptr;

	DataReader = new std::thread(GetDataEntry);
	DataProcessor = new std::thread(ProcessDataEntry);
	Evolutioneer = new std::thread(EvolutionEntry);

}

void AlgotythmsJoin()
{
	doContinue = false;

	DataReader->join();
	DataProcessor->join();
	Evolutioneer->join();

	delete DataReader;
	delete DataProcessor;
	delete Evolutioneer;
}


InputData::InputData()
{
	size = 0;
}

InputData::InputData(const InputData& other) = default;

InputData& InputData::operator=(const InputData& other)
{
	if (this != &other) {
		size = other.size;
		model = other.model;
	}
	return *this;
}

InputData::InputData(InputData&& other) noexcept
	: size(other.size), model(std::move(other.model)) 
{
}

InputData& InputData::operator=(InputData&& other) noexcept {
	if (this != &other) {
		size = other.size;
		model = std::move(other.model);
	}
	return *this;
}

OutputData::OutputData()
{
	bestWayLength = -1;

	bestWay = {0, 1, 0};

	iteration = 0;
}

OutputData::OutputData(const OutputData& other) = default;

OutputData& OutputData::operator=(const OutputData& other)
{
	if (this != &other) {
		bestWayLength = other.bestWayLength;
		bestWay = other.bestWay;
		pheromons = other.pheromons;
		iteration = other.iteration;
	}
	return *this;
}

OutputData::OutputData(OutputData&& other) noexcept
	: bestWayLength(other.bestWayLength), bestWay(std::move(other.bestWay)),
	pheromons(std::move(other.pheromons)), iteration(other.iteration) 
{
}

OutputData& OutputData::operator=(OutputData&& other) noexcept {
	if (this != &other) {
		bestWayLength = other.bestWayLength;
		bestWay = std::move(other.bestWay);
		pheromons = std::move(other.pheromons);
		iteration = other.iteration;
	}
	return *this;
}
