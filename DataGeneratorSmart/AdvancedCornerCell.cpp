#include "AdvancedCornerCell.h"

AdvancedCornerCell::AdvancedCornerCell(GridMovement* movement) : AdvancedCell(0, 0, movement)
{

    this->setStyleSheet("border: 0px; background-color: white;");

    auto font = this->font();
    font.setBold(false);
    this->setFont(font);

	this->setEnabled(false);
	this->setReadOnly(true);

}
