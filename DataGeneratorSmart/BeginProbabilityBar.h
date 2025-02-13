#pragma once
#include "AdvancedBeginProbabilityCell.h"

#include <qlayout.h>
#include <qlabel.h>

#include <vector>

class ProbabilityBar : public QHBoxLayout {

private:

	std::vector<AdvancedCell*> cells;

public:

	ProbabilityBar(const int &N);

	void Resize(const int &N);

	std::vector<double> GetVector(int N);


};