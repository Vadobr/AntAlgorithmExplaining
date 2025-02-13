#include "AlgorythmsEntry.h"

bool doContinue;

InputData* input;

OutputData* output;

std::thread *DataReader;
std::thread *DataProcessor;

void AlgorythmsEntry()
{
	doContinue = true;

	input = nullptr;
	output = nullptr;

	DataReader = new std::thread(GetDataEntry);
	DataProcessor = new std::thread(ProcessDataEntry);

}

void AlgotythmsJoin()
{
	doContinue = false;

	DataReader->join();
	DataProcessor->join();

	delete DataReader;
	delete DataProcessor;
}
