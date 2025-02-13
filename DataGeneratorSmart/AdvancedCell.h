#pragma once
#include <qscrollbar.h>
#include <qscrollarea.h>
#include <qlayout.h>
#include <qclipboard.h>
#include <qapplication.h>
#include <qobject.h>

#include "SmartCellClass.h"

#include <list>

#include "GridMovementer.h"

class GridMovement;

class AdvancedCell : public SmartCell {

Q_OBJECT

public:

	friend class AdvancedSmartMatrix;

	AdvancedCell(const int& positionOnGridRow,	const int& positionOnGridColumn, GridMovement* movement);

	~AdvancedCell();

protected:

	bool isC;

	int positionOnGridRow;
	int positionOnGridColumn;

	GridMovement *movement;

protected:

	static int cellSize;

private:

	static int sizeAdmission;

	static std::list <AdvancedCell*> allCells;

protected:

	virtual void RefreshSize();

protected:

	void keyPressEvent(QKeyEvent* event) override;

	virtual void mousePressEvent(QMouseEvent* event) override;

	void mouseReleaseEvent(QMouseEvent* event) override;

	virtual void mouseDoubleClickEvent(QMouseEvent* event) override;

	virtual void focusInEvent(QFocusEvent* event) override;

	virtual void focusOutEvent(QFocusEvent* event) override;

	virtual void resizeEvent(QResizeEvent* event) override;

private:

	bool DoChangeAllCellsSize();

	void ChangeAllCellsSize();

private slots:

	void TextChanged();

public:

	friend class GridMovement;

protected:

	QScrollArea* GetParentScrollArea();

private:

	bool isChanged;

public:

	void AnnounceChanges();

	void AcceptChanges();

	bool IsChanged();

public:

	QString GetText();

};