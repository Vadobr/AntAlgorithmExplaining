#pragma once

#include "SmartMatrixWidgetClass.h"

#include "GridMovementer.h"
#include "AdvancedCentralCell.h"
#include "AdvancedCornerCell.h"
#include "AdvancedSideCellClass.h"
#include "BeginProbabilityBar.h"


class AdvancedSmartMatrix : public SmartMatrix {

Q_OBJECT

public:
	friend class DataGeneratorSmart;
	friend class MatrixViewModel;
	friend class MainWindow;


private:

	bool isPermanently;

	ProbabilityBar* beginProbabilityBar;

	std::vector <AdvancedSideCell*> topSideCellArray;
	std::vector <AdvancedSideCell*> leftSideCellArray;

	std::vector <std::vector<AdvancedCentralCell*>> gridCellArray;

	GridMovement movement;

	int size;

	int capacity;

	int selectedWidgetRow;

	int selectedWidgetColumn;

public:

	int GetSize();

	AdvancedSmartMatrix();

	void SetPermanently();

	void SetUnpermanently();

	void Resize(const int& N);

	bool IsSomethingChanged();

	bool IsElementChanged(const int &row, const int &column);

	void ApplyElementChanges(const int& row, const int& column);

	ProbabilityBar* GetProbablilityBar();

	void ClearGrid();

public slots:

	void ChangesMade();

	void Focused1();

private:

signals:

	void Amend();

	void Focused2();

};