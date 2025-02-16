#include "PCH.h"
#include "AlgorythmsEntry.h"

bool doContinue;

InputData* input;

OutputData* output;

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
