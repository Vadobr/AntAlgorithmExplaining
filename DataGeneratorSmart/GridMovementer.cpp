#include "GridMovementer.h"

GridMovement::GridMovement()
{

	isDiagonalAvailable = false;

	grid = new AdvancedCell ** [capacity];

	for (int i(0); i < capacity; i++) {

		grid[i] = new AdvancedCell * [capacity];

		for (int j(0); j < capacity; j++) {

			grid[i][j] = nullptr;

		}

	}

	size = 0;

	currentColumn = 0;

	currentRow = 0;

}

void GridMovement::SetElement(AdvancedCell* element, const int& i, const int& j)
{
	if (i < 0)
		return;

	grid[i][j] = element;
}

void GridMovement::Resize(const int& newSize)
{
	if (newSize <= capacity)
		size = newSize;
	else
		size = capacity;
}

void GridMovement::SetCurrentPositionF(const int& i, const int& j)
{
	if (i < 0)
		return;

	currentColumn = j;
	currentRow = i;
}

void GridMovement::Fee()
{
	
}

void GridMovement::DisableDiagonal()
{

	isDiagonalAvailable = false;

}

void GridMovement::EnableDiagonal()
{

	isDiagonalAvailable = true;

}

void GridMovement::MoveUp()
{
	
	if (currentRow - 1 == currentColumn) {
		
		if (currentColumn == 0) {
			return;
		}

		grid[currentRow][currentColumn]->clearFocus();

		if(isDiagonalAvailable)
		{
			currentRow -= 1;
		}
		else
		{ 
			currentRow -= 2;
		}
		

		grid[currentRow][currentColumn]->setFocus();

		grid[currentRow][currentColumn]->SetSelectionState(SmartCell::preselected);

		return;
	}

	if (currentRow > 0 && !(currentColumn == 0 && currentRow == 1)) {

		grid[currentRow][currentColumn]->clearFocus();

		currentRow--;

		grid[currentRow][currentColumn]->setFocus();
		
		grid[currentRow][currentColumn]->SetSelectionState(SmartCell::preselected);

	}
}

void GridMovement::MoveDown()
{

	if (currentRow + 1 == currentColumn) {

		if (currentColumn == size) {
			if (!isDiagonalAvailable)
				return;
		}

		grid[currentRow][currentColumn]->clearFocus();

		if (isDiagonalAvailable)
		{
			currentRow += 1;
		}
		else
		{
			currentRow += 2;
		}

		grid[currentRow][currentColumn]->setFocus();

		grid[currentRow][currentColumn]->SetSelectionState(SmartCell::preselected);

		return;
	}

	if (currentRow < size) {

		grid[currentRow][currentColumn]->clearFocus();

		currentRow++;

		grid[currentRow][currentColumn]->setFocus();

		grid[currentRow][currentColumn]->SetSelectionState(SmartCell::preselected);

	}

}

void GridMovement::MoveLeft()
{

	if (currentColumn - 1 == currentRow) {

		if (currentRow == 0)
			return;

		grid[currentRow][currentColumn]->clearFocus();


		if (isDiagonalAvailable)
		{
			currentColumn -= 1;
		}
		else
		{
			currentColumn -= 2;
		}

		grid[currentRow][currentColumn]->setFocus();

		grid[currentRow][currentColumn]->SetSelectionState(SmartCell::preselected);

		return;

	}

	if (currentColumn > 0 && !( currentColumn == 1 && currentRow == 0 )) {

		grid[currentRow][currentColumn]->clearFocus();

		currentColumn--;

		grid[currentRow][currentColumn]->setFocus();

		grid[currentRow][currentColumn]->SetSelectionState(SmartCell::preselected);

	}

}

void GridMovement::MoveRight()
{

	if (currentColumn + 1 == currentRow) {

		if (currentRow == size) {
			if(!isDiagonalAvailable)
				return;
		}

		grid[currentRow][currentColumn]->clearFocus();

		if (isDiagonalAvailable)
		{
			currentColumn += 1;
		}
		else
		{
			currentColumn += 2;
		}

		grid[currentRow][currentColumn]->setFocus();

		grid[currentRow][currentColumn]->SetSelectionState(SmartCell::preselected);

		return;

	}

	if (currentColumn < size) {

		grid[currentRow][currentColumn]->clearFocus();

		currentColumn++;

		grid[currentRow][currentColumn]->setFocus();

		grid[currentRow][currentColumn]->SetSelectionState(SmartCell::preselected);

	}

}
