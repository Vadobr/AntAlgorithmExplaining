#pragma once
#include "AdvancedCell.h"

class AdvancedCell;

class GridMovement {

private:

	int size;

	const int capacity = 100;

	AdvancedCell*** grid;

	int currentRow;
	int currentColumn;

	bool isDiagonalAvailable;

public:

	GridMovement();

public:

	void SetElement(AdvancedCell* element, const int& i, const int& j);

	void Resize(const int& newSize);

	void SetCurrentPositionF(const int& i, const int& j);

	void Fee();

	void DisableDiagonal();

	void EnableDiagonal();

public:

	void MoveUp();

	void MoveDown();

	void MoveLeft();

	void MoveRight();

};