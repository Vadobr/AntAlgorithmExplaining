#include "AdvancedSmartMatrix.h"

int AdvancedSmartMatrix::GetSize()
{
    return size;
}

AdvancedSmartMatrix::AdvancedSmartMatrix()
{

    isPermanently = true;

    size = 0;

    capacity = 0;

    leftSideCellArray.clear();

    topSideCellArray.clear();

    selectedWidgetRow = 1;

    selectedWidgetColumn = 1;


}

void AdvancedSmartMatrix::SetPermanently()
{

    movement.DisableDiagonal();

    isPermanently = true;

    for (int i(0); i < capacity; i++) {

        if (isPermanently)
        {

            gridCellArray[i][i]->SetSelectionState(SmartCell::SelectionState::disabled);

            gridCellArray[i][i]->setEnabled(false);

        }
        else
        {

            gridCellArray[i][i]->SetSelectionState(SmartCell::SelectionState::unselected);

            gridCellArray[i][i]->setEnabled(true);

        }

    }

}

void AdvancedSmartMatrix::SetUnpermanently()
{

    movement.EnableDiagonal();

    isPermanently = false;

    for (int i(0); i < capacity; i++) {

        if (isPermanently)
        {

            gridCellArray[i][i]->SetSelectionState(SmartCell::SelectionState::disabled);

            gridCellArray[i][i]->setEnabled(false);

        }
        else
        {

            gridCellArray[i][i]->SetSelectionState(SmartCell::SelectionState::unselected);

            gridCellArray[i][i]->setEnabled(true);

        }

    }

}

void AdvancedSmartMatrix::Resize(const int& N)
{


    movement.Resize(N);

    if (N > capacity) {

        gridCellArray.resize(N);

        for (int i(0); i < N; i++) {

            gridCellArray[i].resize(N);

        }

    }

    for (int i(0); i < capacity; i++) {

        this->ShowLeftSideWidget(i);
        this->ShowTopSideWidget(i);

        for (int j(0); j < capacity; j++) {

            this->ShowCentralWidget(i, j);

        }
    }

    for (int i(capacity); i < N; i++) {

        {
            AdvancedSideCell* leftCell = new AdvancedSideCell(i + 1, 0, &movement);
            AdvancedSideCell* topCell = new AdvancedSideCell(0, i + 1, &movement);

            leftCell->linckCells(topCell);

            this->SetLeftSideWidget(leftCell, i);
            this->SetTopSideWidget(topCell, i);

            leftCell->setText(QString("S") + QString(std::to_string(i + 1).c_str()));
            topCell->setText(QString("S") + QString(std::to_string(i + 1).c_str()));

            leftSideCellArray.push_back(leftCell);
            topSideCellArray.push_back(topCell);

            connect(leftCell, &QTextEdit::textChanged, this, &AdvancedSmartMatrix::ChangesMade);
            connect(topCell, &QTextEdit::textChanged, this, &AdvancedSmartMatrix::ChangesMade);

        }


    }

    for (int i(0); i < capacity; i++) {
        for (int j(capacity); j < N; j++) {

            AdvancedCentralCell* centralCell = nullptr;


            centralCell = new AdvancedCentralCell(i + 1, j + 1, &movement);

            centralCell->SetLinckedCells(leftSideCellArray[i], topSideCellArray[j]);

            this->SetCentralWidget(centralCell, i, j);

            leftSideCellArray[i]->AddCentrallLinckedCell(centralCell);
            topSideCellArray[j]->AddCentrallLinckedCell(centralCell);

            gridCellArray[i][j] = centralCell;

            connect(centralCell, &QTextEdit::textChanged, this, &AdvancedSmartMatrix::ChangesMade);

            centralCell = new AdvancedCentralCell(j + 1, i + 1, &movement);

            centralCell->SetLinckedCells(leftSideCellArray[j], topSideCellArray[i]);

            this->SetCentralWidget(centralCell, j, i);

            leftSideCellArray[j]->AddCentrallLinckedCell(centralCell);
            topSideCellArray[i]->AddCentrallLinckedCell(centralCell);

            gridCellArray[j][i] = centralCell;

            connect(centralCell, &QTextEdit::textChanged, this, &AdvancedSmartMatrix::ChangesMade);

            connect(centralCell, &AdvancedCentralCell::Focused, this, &AdvancedSmartMatrix::Focused1);

        }
    }

    for (int i(capacity); i < N; i++) {
        for (int j(capacity); j < N; j++) {

            AdvancedCentralCell* centralCell = nullptr;

            centralCell = new AdvancedCentralCell(i + 1, j + 1, &movement);

            centralCell->SetLinckedCells(leftSideCellArray[i], topSideCellArray[j]);

            this->SetCentralWidget(centralCell, i, j);

            leftSideCellArray[i]->AddCentrallLinckedCell(centralCell);
            topSideCellArray[j]->AddCentrallLinckedCell(centralCell);

            gridCellArray[i][j] = centralCell;

            connect(centralCell, &QTextEdit::textChanged, this, &AdvancedSmartMatrix::ChangesMade);

            connect(centralCell, &AdvancedCentralCell::Focused, this, &AdvancedSmartMatrix::Focused1);

        }
    }



    for (int i(N); i < capacity; i++) {

        this->HideLeftSideWidget(i);
        this->HideTopSideWidget(i);

    }
    for (int i(0); i < capacity; i++) {
        for (int j(N); j < capacity; j++) {

            this->HideCentralWidget(i, j);
            this->HideCentralWidget(j, i);

        }
    }

    size = N;

    if (size > capacity)
        capacity = size;



    for (int i(0); i < N; i++) {

        if (isPermanently)
        {

            gridCellArray[i][i]->SetSelectionState(SmartCell::SelectionState::disabled);

            gridCellArray[i][i]->setEnabled(false);

        }
        else
        {

            gridCellArray[i][i]->SetSelectionState(SmartCell::SelectionState::unselected);

            gridCellArray[i][i]->setEnabled(true);

        }

    }
}

bool AdvancedSmartMatrix::IsSomethingChanged()
{

    for (int i(0); i < size; i++) {

        if (leftSideCellArray[i]->IsChanged())
            return true;

        if (topSideCellArray[i]->IsChanged())
            return true;

        for (int j(0); j < size; j++) {

            if (gridCellArray[i][j]->IsChanged())
                return true;

        }

    }

    return false;
}

bool AdvancedSmartMatrix::IsElementChanged(const int& row, const int& column)
{

    if (row == 0 && column == 0)
        return false;
    if (column == 0)
        return leftSideCellArray[row - 1]->IsChanged();
    if (row == 0)
        return topSideCellArray[column - 1]->IsChanged();

    return gridCellArray[row - 1][column - 1]->IsChanged();

}

void AdvancedSmartMatrix::ApplyElementChanges(const int& row, const int& column)
{

    if (row == 0 && column == 0)
        return;

    if (column == 0)
        leftSideCellArray[row - 1]->AcceptChanges();
    else if (row == 0)
        topSideCellArray[column - 1]->AcceptChanges();
    else
        gridCellArray[row - 1][column - 1]->AcceptChanges();

}

ProbabilityBar* AdvancedSmartMatrix::GetProbablilityBar()
{
    return nullptr;
}

void AdvancedSmartMatrix::ClearGrid()
{

    for (int i(0); i < gridCellArray.size(); i++) {

        for (int j(0); j < gridCellArray.size(); j++) {

            gridCellArray[i][j]->setText("");

        }

    }

}

void AdvancedSmartMatrix::Focused1()
{

    emit Focused2();

}



void AdvancedSmartMatrix::ChangesMade() {

    emit Amend();

    

}

