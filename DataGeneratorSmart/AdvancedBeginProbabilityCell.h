#pragma once
#include "AdvancedCell.h"
#include "qevent.h"

class AdvancedProbabilityCell : public AdvancedCell
{
public:

	AdvancedProbabilityCell(const int& positionOnGridColumn);

protected:

	bool ToLimitInput(QKeyEvent* event) override;

	void CorrectText() override;

private:

	SmartCell* leftHeader;

	SmartCell* topHeader;

public:

	void SetLinckedCells(SmartCell* leftHeader, SmartCell* topHeader);

protected:

	void focusInEvent(QFocusEvent* event) override;

	void focusOutEvent(QFocusEvent* event) override;

};