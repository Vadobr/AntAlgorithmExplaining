#pragma once

#include <QtWidgets/qtextedit.h>
#include <QtWidgets/qmainwindow.h>

#include <qevent.h>
#include <qregularexpression.h>
#include <qlineedit.h>

class SmartCell : public QTextEdit {

Q_OBJECT

public:

	friend class AdvancedSmartMatrix;

	SmartCell(QWidget* window = nullptr);

public:

	enum SelectionState {
		disabled = -1,
		unselected = 0,
		preselected = 1,
		selected = 2
	};

protected:

	SelectionState selectionState;

private:

	void NextSelectionState();

public:

	virtual void SetStyleByState();

public:

	void SetSelectionState(const SelectionState& newSelectionState);

protected:

	virtual void keyPressEvent(QKeyEvent* event) override;

protected:

	virtual void mousePressEvent(QMouseEvent* event) override;

protected:

	virtual void mouseDoubleClickEvent(QMouseEvent* event) override;

private:

	virtual bool ToLimitInput(QKeyEvent* event);

protected:

	virtual void focusOutEvent(QFocusEvent* event) override;

protected:

	virtual void CorrectText();

protected:

	QString GetText();

};