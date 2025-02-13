#pragma once

#include <vector>
#include <string>

class TransitionsMatrix {

private:

	double **probabilitiesMatrix;
	double **intensitiesMatrix;

	bool** probabilitiesMask;
	bool** intensitiesMask;

	std::string** functionsMatrix;

	std::string* verticesName;

	int size;

	int copacity;

	class KolmagorovsModel {

	private:

		int solveBeginPosition;

		TransitionsMatrix* transitionsMatrix;

		double beginTime;
		double endTime;

		int stepCount;

		double deltaTime;

		double** intensitiesMatrixCopy;

	private:

		std::string changedString;

		double currentTime;

		void ChangeString(std::string str);

		double function(const double& x, int& c);

		void CalculateMatrixCopy();

	private:

		std::vector <std::vector<double>> results;

	public:

		KolmagorovsModel(TransitionsMatrix* parent);

	private:

		KolmagorovsModel();

	public:

		void Solve(std::vector<double> beginProbabilities);

	public:

		void NextStep();

	public:

		void SetBeginTime(const double& beginTime);

		void SetEndTime(const double& endTime);

		void SetTime(const double& beginTime, const double& endTime = 0);

		void SetStepCount(const int& stepCount);

	private:

		void FinalizationTime();

	private:

		void CalculateDeltaTime();

	public:

		double GetDeltaTime();

		double GetBeginTime();

		double GetEndTime();

		std::vector <std::vector<double>> GetResults();

	};

	KolmagorovsModel* kolmagorovsModel;


public:

	TransitionsMatrix();

	TransitionsMatrix(const int& N);

	~TransitionsMatrix();

public:

	void Resize(const int& N);

	void SetIntensitiveElement(const double& value, const int& row, const int& column);

	void SetVerticeName(const std::string& value, const int& verticeNumber);

	void SetFunctionOfElement(const std::string& value, const int& row, const int& column);

public:

	std::vector <std::vector<double>> SolveAsKolmagorovsEquation(std::vector<double> beginProbabilities);
	
public:

	int Size();

	double GetDeltaTime();

	std::string GetVerticeName(const int& verticeNumber);

	double GeteIntensitie(const int& i, const int& j);

	std::string GetFunctionOfElement(const int& i, const int& j);

	double GetBeginTime();

	double GetEndTime();

public:

	void SetTime(const double& beginTime, const double& endTime);
	void SetStepCount(const int& count);
	
	void SetBeginTime(const double& beginTime);
	
	void SetEndTime(const double& beginTime);

public:

	friend class KolmagorovsModel;

};