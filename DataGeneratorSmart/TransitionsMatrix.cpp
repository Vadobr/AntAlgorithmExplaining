#include "TransitionsMatrix.h"

extern bool isGlobalStationary;

double number_error;

#define NO_ERRORS 8
#define DIVIDE_ON_ZERO 0

TransitionsMatrix::TransitionsMatrix()
{

	probabilitiesMatrix = nullptr;
	intensitiesMatrix = nullptr;

	probabilitiesMask = nullptr;
	intensitiesMask = nullptr;

	size = 0;

	copacity = 0;

	this->kolmagorovsModel = new KolmagorovsModel(this);

}

TransitionsMatrix::TransitionsMatrix(const int& N)
{

	this->kolmagorovsModel = new KolmagorovsModel(this);

	probabilitiesMatrix = new double* [N];
	intensitiesMatrix = new double* [N];

	probabilitiesMask = new bool* [N];
	intensitiesMask = new bool* [N];

	for (int i(0); i < N; i++) {

		probabilitiesMatrix[i] = new double [N];
		intensitiesMatrix[i] = new double[N];
		probabilitiesMask[i] = new bool [N];
		intensitiesMask[i] = new bool [N];

		for (int j(0); j < N; j++) {

			probabilitiesMatrix[i][j] = 0;
			intensitiesMatrix[i][j] = 0;

			probabilitiesMask[i][j] = false;
			intensitiesMask[i][j] = false;
		}


	}

	size = N;

	copacity = size;

}

TransitionsMatrix::~TransitionsMatrix()
{

	for (int i(0); i < copacity; i++) {

		delete[] probabilitiesMatrix[i];
		delete[] intensitiesMatrix[i];
		delete[] probabilitiesMask[i];
		delete[] intensitiesMask[i];
	}

	delete[] probabilitiesMatrix;
	delete[] intensitiesMatrix;
	delete[] probabilitiesMask;
	delete[] intensitiesMask;

	delete kolmagorovsModel;

}

void TransitionsMatrix::Resize(const int& N)
{
	if (N < copacity) {

		size = N;

	}
	else {

		double** newProbabilitiesMatrix = new double* [N];
		double** newIntensitiesMatrix = new double* [N];
		bool** newProbabilitiesMask = new bool* [N];
		bool** newIntensitiesMask = new bool* [N];
		std::string* newVerticesName = new std::string [N];

		std::string** newFunctionsMatrix = new std::string*[N];

		for (int i(0); i < N; i++) {

			newProbabilitiesMatrix[i] = new double[N];
			newIntensitiesMatrix[i] = new double[N];
			newProbabilitiesMask[i] = new bool[N];
			newIntensitiesMask[i] = new bool[N];
			newFunctionsMatrix[i] = new std::string[N];

			for (int j(0); j < N; j++) {

				newProbabilitiesMatrix[i][j] = 0;
				newIntensitiesMatrix[i][j] = 0;
				newProbabilitiesMask[i][j] = false;
				newIntensitiesMask[i][j] = false;
				newFunctionsMatrix[i][j] = "";
			}

			newVerticesName[i] = std::string("S") + std::to_string(i);

		}

		if (probabilitiesMatrix && intensitiesMatrix && intensitiesMatrix && intensitiesMask) {

			for (int i(0); i < size; i++) {

				newVerticesName[i] = verticesName[i];

				for (int j(0); j < size; j++) {

					newProbabilitiesMatrix[i][j] = probabilitiesMatrix[i][j];
					newIntensitiesMatrix[i][j] = intensitiesMatrix[i][j];
					newProbabilitiesMask[i][j] = probabilitiesMask[i][j];
					newIntensitiesMask[i][j] = intensitiesMask[i][j];
					newFunctionsMatrix[i][j] = functionsMatrix[i][j];
				}

				delete[] probabilitiesMatrix[i];
				delete[] intensitiesMatrix[i];
				delete[] probabilitiesMask[i];
				delete[] intensitiesMask[i];
				delete[] functionsMatrix[i];
			}

			delete[] probabilitiesMatrix;
			delete[] intensitiesMatrix;
			delete[] probabilitiesMask;
			delete[] intensitiesMask;
			delete[] verticesName;
			delete[] functionsMatrix;

		}

		probabilitiesMatrix = newProbabilitiesMatrix;
		intensitiesMatrix = newIntensitiesMatrix;
		probabilitiesMask = newProbabilitiesMask;
		intensitiesMask = newIntensitiesMask;
		verticesName = newVerticesName;
		functionsMatrix = newFunctionsMatrix;

		size = N;

		if (size > copacity)
			copacity = size;

	}

}

void TransitionsMatrix::SetIntensitiveElement(const double& value, const int& row, const int& column)
{
	intensitiesMask[row][column] = true;

	intensitiesMatrix[row][column] = value;
}

void TransitionsMatrix::SetVerticeName(const std::string& value, const int& verticeNumber)
{

	verticesName[verticeNumber] = value;

}

void TransitionsMatrix::SetFunctionOfElement(const std::string& value, const int& row, const int& column)
{

	functionsMatrix[row][column] = value;

}

std::vector <std::vector<double>> TransitionsMatrix::SolveAsKolmagorovsEquation(std::vector<double> beginProbabilities)
{

	kolmagorovsModel->Solve(beginProbabilities);

	return kolmagorovsModel->GetResults();
	
}

int TransitionsMatrix::Size()
{
	return size;
}

double TransitionsMatrix::GetDeltaTime()
{
	return kolmagorovsModel->GetDeltaTime();
}

std::string TransitionsMatrix::GetVerticeName(const int& verticeNumber)
{
	return verticesName[verticeNumber];
}

double TransitionsMatrix::GeteIntensitie(const int& i, const int& j)
{
	return intensitiesMatrix[i][j];
}

std::string TransitionsMatrix::GetFunctionOfElement(const int& i, const int& j)
{
	return functionsMatrix[i][j];
}

double TransitionsMatrix::GetBeginTime()
{
	return kolmagorovsModel->GetBeginTime();
}

double TransitionsMatrix::GetEndTime()
{
	return kolmagorovsModel->GetEndTime();
}

void TransitionsMatrix::SetTime(const double& beginTime, const double& endTime)
{
	kolmagorovsModel->SetTime(beginTime, endTime);
}

void TransitionsMatrix::SetStepCount(const int& count)
{
	kolmagorovsModel->SetStepCount(count);
}

void TransitionsMatrix::SetBeginTime(const double& beginTime)
{
	kolmagorovsModel->SetBeginTime(beginTime);
}

void TransitionsMatrix::SetEndTime(const double& endTime)
{
	kolmagorovsModel->SetEndTime(endTime);
}

void TransitionsMatrix::KolmagorovsModel::ChangeString(std::string str)
{

	std::string new_str;

	for (int i(0); i < str.size(); i++) {

		if (str[i] == 'a') {

			new_str.push_back('(');

			new_str += std::to_string(1);

			new_str.push_back(')');

		}

		if (str[i] >= '0' && str[i] <= '9') {

			new_str.push_back('(');

			while ((str[i] >= '0' && str[i] <= '9' || str[i] == '.') && i < str.size()) {

				new_str.push_back(str[i]);

				i++;

			}

			new_str.push_back(')');

		}

		if (str[i] == 'x') {

			new_str += "(";

			new_str += "(";

			new_str.push_back('x');

			new_str += ")";

			if (0 >= 0)
				new_str.push_back('+');
			else
				new_str.push_back('-');

			new_str += "(";

			new_str += std::to_string(0);

			new_str += ")";

			new_str += ")/(";

			new_str += std::to_string(1);

			new_str += ")";


			continue;

		}

		if (str[i] == '+' || str[i] == '-') {

			if (i == 0 || str[i - 1] != ')') {
				new_str = "(" + new_str + ")";
			}

			new_str.push_back(str[i]);

			if (i == str.size() - 1 || str[i + 1] != '(') {
				new_str.push_back('(');
				str.push_back(')');
			}

			continue;

		}

		if (str[i] == '^') {

			if (i == 0 || str[i - 1] != ')') {
				new_str = "(" + new_str + ")";
			}

			new_str.push_back(str[i]);

			if (i == str.size() - 1 || str[i + 1] != '(') {
				new_str.push_back('(');
				str.push_back(')');
			}

			continue;

		}

		if (str[i] == ' ') {
			continue;
		}

		new_str.push_back(str[i]);

	}

	new_str = "(" + new_str + ")*(" + std::to_string(1) + ")";

	new_str = "(" + new_str + ")";

	if (0 >= 0)
		new_str.push_back('+');

	new_str += "(" + std::to_string(0) + ")";

	changedString = new_str;

}

double TransitionsMatrix::KolmagorovsModel::function(const double& x, int& c)
{
	double res = 0;

	bool dot = false;

	while (c < changedString.size()) {

		if (changedString[c] >= '0' && changedString[c] <= '9') {
			if (dot) {
				res += double(changedString[c] - '0') / 10.;
			}
			else {
				res *= 10.;
				res += changedString[c] - '0';
			}

		}
		else
		if (changedString[c] == ',' || changedString[c] == '.') {
			dot = true;
		}
		else
		if (changedString[c] == '*') {
			c++;
			res *= function(x, c);
			continue;
		}
				else
					if (changedString[c] == '/') {
						c++;
						res /= number_error = function(x, c);
						continue;
					}
					else
						if (changedString[c] == '+') {
							c++;
							res += function(x, c);
							continue;
						}
						else
							if (changedString[c] == '-') {
								c++;
								res -= function(x, c);
								continue;
							}
							else
								if (changedString[c] == '^') {
									c++;
									res = pow(res, function(x, c));
									continue;
								}
								else
									if (changedString[c] == 'x') {
										res = x;
									}
									else
										if (changedString[c] == '(') {

											c++;
											res = function(x, c);

										}
										else
											if (changedString[c] == ')') {

												return res;

											}
											else
												if (!_strnicmp(&changedString[c], "sin(", 4)) {

													c += 4;

													res = sin(function(x, c));

												}
												else
													if (!_strnicmp(&changedString[c], "cos(", 4)) {

														c += 4;

														res = cos(function(x, c));

													}

		c++;

	}

	return res;
}

void TransitionsMatrix::KolmagorovsModel::CalculateMatrixCopy()
{

	intensitiesMatrixCopy = new double* [transitionsMatrix->size];

	for (int i(0); i < transitionsMatrix->size; i++) {

		intensitiesMatrixCopy[i] = new double[transitionsMatrix->size];

		for (int j(0); j < transitionsMatrix->size; j++) {

			if (isGlobalStationary) {
				intensitiesMatrixCopy[i][j] = transitionsMatrix->intensitiesMatrix[i][j];
			}
			else {

				ChangeString(transitionsMatrix->functionsMatrix[i][j]);

				{

					int c = 0;

					double time = 0;

					intensitiesMatrixCopy[i][j] = function(time, c);

				}
			}
		}

	}

	double dr = 0.;

	for (int i(0); i < transitionsMatrix->size; i++) {

		dr = 0.;

		for (int j(0); j < transitionsMatrix->size; j++) {

			dr += intensitiesMatrixCopy[i][j];

		}
		if (dr > 0) {
			for (int j(0); j < transitionsMatrix->size; j++) {

				intensitiesMatrixCopy[i][j] /= dr;

			}
		}
	}

}

TransitionsMatrix::KolmagorovsModel::KolmagorovsModel(TransitionsMatrix* parent) {

	beginTime = 0;
	endTime = 10;

	stepCount = 20;

	CalculateDeltaTime();

	solveBeginPosition = 0;

	this->transitionsMatrix = parent;

}

TransitionsMatrix::KolmagorovsModel::KolmagorovsModel()
{
	beginTime = 0;
	endTime = 10;

	stepCount = 20;

	CalculateDeltaTime();

	solveBeginPosition = 0;

}

void TransitionsMatrix::KolmagorovsModel::Solve(std::vector<double> beginProbabilities)
{
	if(!results.empty())
		results.clear();

	currentTime = beginTime;

	results.push_back(std::vector<double>(transitionsMatrix->size));

	for (int i(0); i < results[0].size(); i++) {
		results[0][i] = 0;
	}

	double r = 0;

	for (int i(0); i < results[0].size(); i++) {
		results[0][i] = beginProbabilities[i];
		r += results[0][i];
	}

	if (r <= 0) {
		for (int i(0); i < results[0].size(); i++) {
			results[0][i] = 0;
		}
		results[0][0] = 1;
	}
	else if (r != 0) {
		for (int i(0); i < results[0].size(); i++) {
			results[0][i] /= r;
		}
	}

	CalculateMatrixCopy();

	for (int i(0); i < stepCount; i++) {
		
		if (!isGlobalStationary) {
			CalculateMatrixCopy();
		}

		NextStep();

	}



	for (int i(0); i < transitionsMatrix->size; i++) {

		delete [] intensitiesMatrixCopy[i];


	}

	delete [] intensitiesMatrixCopy;

}

void TransitionsMatrix::KolmagorovsModel::NextStep()
{

	currentTime += deltaTime;

	int size = transitionsMatrix->size;

	std::vector <double> deltaResult(size);

	int resultLength = results.size() - 1;

	for (int i(0); i < size; i++) {

		deltaResult[i] = 0;

		for (int j(0); j < size; j++) {

			deltaResult[i] += intensitiesMatrixCopy[j][i] * results[resultLength][j];
			deltaResult[i] -= intensitiesMatrixCopy[i][j] * results[resultLength][i];

		}

		deltaResult[i] *= deltaTime;
	}

	this->results.push_back(std::vector<double>(size));

	resultLength++;

	for (int i(0); i < size; i++) {

		results[resultLength][i] = results[resultLength - 1][i] + deltaResult[i];

	}

}

void TransitionsMatrix::KolmagorovsModel::SetBeginTime(const double& beginTime)
{
	this->beginTime = beginTime;

	FinalizationTime();
}

void TransitionsMatrix::KolmagorovsModel::SetEndTime(const double& endTime)
{
	this->endTime = endTime;

	FinalizationTime();
}

void TransitionsMatrix::KolmagorovsModel::SetTime(const double& beginTime, const double& endTime)
{

	this->beginTime = beginTime;
	this->endTime = endTime;

	FinalizationTime();

}

void TransitionsMatrix::KolmagorovsModel::SetStepCount(const int& stepCount)
{
	if (stepCount > 0)
		this->stepCount = stepCount;
	else
		this->stepCount = 2;

	CalculateDeltaTime();
}

void TransitionsMatrix::KolmagorovsModel::FinalizationTime()
{
	if (beginTime <= 0 && endTime <= 0) {
		this->beginTime = this->endTime = 0;
	}
	else
	if (beginTime <= 0 && endTime >= 0) {
		this->beginTime = 0;
		this->endTime = endTime;
	}
	else
	if (beginTime >= 0 && endTime <= 0) {
		this->beginTime = this->endTime = 0;
	}
	else
	if (beginTime >= endTime) {
		std::swap(beginTime, endTime);
	}

	CalculateDeltaTime();
}

void TransitionsMatrix::KolmagorovsModel::CalculateDeltaTime()
{

	deltaTime = (endTime - beginTime) / double(stepCount);

}

double TransitionsMatrix::KolmagorovsModel::GetDeltaTime()
{
	return deltaTime;
}

double TransitionsMatrix::KolmagorovsModel::GetBeginTime()
{
	return this->beginTime;
}

double TransitionsMatrix::KolmagorovsModel::GetEndTime()
{
	return this->endTime;
}

std::vector<std::vector<double>> TransitionsMatrix::KolmagorovsModel::GetResults()
{
	return results;
}
