#include "BeginProbabilityBar.h"

ProbabilityBar::ProbabilityBar(const int &N)
{

	this->Resize(N);

}

void ProbabilityBar::Resize(const int &N)
{

	while (cells.size() < N) {

		cells.push_back(new AdvancedProbabilityCell(cells.size()));

		this->addWidget(cells[cells.size() - 1]);

	}

	for (int i(0); i < N; i++) {

		cells[i]->show();

	}

	for (int i(N); i < cells.size(); i++) {

		cells[i]->hide();

	}
}

std::vector<double> ProbabilityBar::GetVector(int N)
{
	std::vector<double> res;

	res.resize(N);

	for (int i(0); i < N; i++) {

		std::string str;

		str = cells[i]->toPlainText().toStdString();

		std::replace(str.begin(), str.end(), ',', '.');

		res[i] = std::atof(str.c_str());

	}

	return res;
}
