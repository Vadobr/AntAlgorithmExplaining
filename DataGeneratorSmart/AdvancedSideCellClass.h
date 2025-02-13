#pragma once
#include "AdvancedCell.h"

#include <list>

class AdvancedSideCell : public AdvancedCell
{
public:

	AdvancedSideCell(const int& positionOnGridRow, const int& positionOnGridColumn, GridMovement* movement);

private:

	AdvancedSideCell* linckedCell;

	void onTextChanged();

public:

	void linckCells(AdvancedSideCell* cell);

protected:

	void SetStyleByState() override;

protected:

	bool ToLimitInput(QKeyEvent* event) override;

	void RefreshSize() override;

protected:

	void CorrectText() override;

private:

	std::list <SmartCell*> centralCellsArray;

public:

	void AddCentrallLinckedCell(SmartCell* linckedCell);

protected:

	void focusInEvent(QFocusEvent* event) override;

	void focusOutEvent(QFocusEvent* event) override;


};