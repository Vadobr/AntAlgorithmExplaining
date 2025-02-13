#include "AdvancedSideCellClass.h"

AdvancedSideCell::AdvancedSideCell(const int& positionOnGridRow, const int& positionOnGridColumn, GridMovement* movement) :
    AdvancedCell(positionOnGridRow, positionOnGridColumn, movement)
{

	connect(this, &AdvancedSideCell::textChanged, this, &AdvancedSideCell::onTextChanged);

}

void AdvancedSideCell::onTextChanged()
{
	if(this->hasFocus())
		linckedCell->setText(this->toPlainText());

}

void AdvancedSideCell::linckCells(AdvancedSideCell* cell)
{
	this->linckedCell = cell;

	cell->linckedCell = this;
}

void AdvancedSideCell::SetStyleByState()
{

    CorrectText();

    if (this->selectionState == SelectionState::unselected) {

        this->setStyleSheet("border: 1px solid gray; border-radius: 0px; background-color: white;");
        this->setReadOnly(true);
        auto font = this->font();
        font.setBold(false);
        this->setFont(font);
    }
    else if (this->selectionState == SelectionState::preselected) {

        this->setStyleSheet("border: 0px solid white; border-radius: 2px; background-color: #ffef5c;");
        this->setReadOnly(true);
        auto font = this->font();
        font.setBold(true);
        this->setFont(font);
    }
    else if (this->selectionState == SelectionState::selected) {

        this->setStyleSheet("border: 2px solid #e8c00c; border-radius: 10px; background-color: white;");
        this->setReadOnly(false);
        auto font = this->font();
        font.setBold(true);
        this->setFont(font);
        this->moveCursor(QTextCursor::End);
    }
}

bool AdvancedSideCell::ToLimitInput(QKeyEvent* event)
{

    return false;
}

void AdvancedSideCell::RefreshSize()
{

    AdvancedCell::RefreshSize();

}

void AdvancedSideCell::CorrectText()
{

}

void AdvancedSideCell::AddCentrallLinckedCell(SmartCell* linckedCell)
{

    this->centralCellsArray.push_back(linckedCell);

}

void AdvancedSideCell::focusInEvent(QFocusEvent* event)
{

    AdvancedCell::focusInEvent(event);

    linckedCell->setStyleSheet("background-color: #ffcc8a");

    for (auto cell : centralCellsArray) {

        cell->setStyleSheet("background-color: #fff6a8");

    }


}

void AdvancedSideCell::focusOutEvent(QFocusEvent* event)
{

    AdvancedCell::focusOutEvent(event);

    linckedCell->SetStyleByState();

    for (auto cell : centralCellsArray) {

        cell->SetStyleByState();

    }

}
