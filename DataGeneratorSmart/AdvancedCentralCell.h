#pragma once
#include "AdvancedCell.h"
#include "qevent.h"
#include <string>

#include <qobject.h>


class AdvancedCentralCell : public AdvancedCell
{
Q_OBJECT

public:

	AdvancedCentralCell(const int& positionOnGridRow, const int& positionOnGridColumn, GridMovement* movement);

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

public:

	QString GetText();

signals:

	void Focused();

private slots:

	void SendFocused();

public slots:

	void NewTextFromNowhere(QString newText);

};