#include "AdvancedCell.h"

extern bool isGlobalStationary;

int AdvancedCell::cellSize = 35;

int AdvancedCell::sizeAdmission = 15;

std::list <AdvancedCell*> AdvancedCell::allCells;

AdvancedCell::AdvancedCell(const int& positionOnGridRow, const int& positionOnGridColumn, GridMovement* movement)
{

	isC = false;

	this->positionOnGridRow = positionOnGridRow;
	this->positionOnGridColumn = positionOnGridColumn;
	this->movement = movement;

	QTextOption textOption = this->document()->defaultTextOption();
	textOption.setWrapMode(QTextOption::NoWrap);

	textOption.setAlignment(Qt::AlignCenter);

	this->document()->setDefaultTextOption(textOption);

	this->setMinimumHeight(25);
	this->setMaximumHeight(25);

	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	this->horizontalScrollBar()->setVisible(false);
	this->verticalScrollBar()->setVisible(false);

	if (DoChangeAllCellsSize()) {
		ChangeAllCellsSize();
	}

	allCells.push_back(this);

	movement->SetElement(this, positionOnGridRow, positionOnGridColumn);

	this->movement->Fee();

	isChanged = false;

	connect(this, &QTextEdit::textChanged, this, &AdvancedCell::TextChanged);

	QWidget* parentWidget = this->parentWidget();
	if (parentWidget)
	{
		// Встановлюємо фільтр подій для батьківського виджета
		parentWidget->installEventFilter(this);
	}


}

AdvancedCell::~AdvancedCell()
{
	allCells.remove(this);
}

void AdvancedCell::RefreshSize()
{

	//static bool isnFirst = false;

	//if (isnFirst)
	//	return;

	//isnFirst = true;

	int newSize = 45; // cellSize + sizeAdmission;

	//this->setMinimumSize(newSize, newSize);
	//this->setMaximumSize(newSize, newSize);

	this->setMinimumWidth(newSize);
	this->setMaximumWidth(newSize);

}

void AdvancedCell::keyPressEvent(QKeyEvent* event)
{

	if (this->selectionState == SelectionState::preselected) {
		if (event->key() == Qt::Key_Left) {
			movement->MoveLeft();
		}
		if (event->key() == Qt::Key_Right) {
			movement->MoveRight();
		}
		if (event->key() == Qt::Key_Up) {
			movement->MoveUp();
		}
		if (event->key() == Qt::Key_Down) {
			movement->MoveDown();
		}
	}

	//

	if (event->modifiers() == Qt::ControlModifier)
	{
		if (event->key() == Qt::Key_C)
		{
			if(this->selectionState == SelectionState::preselected)
			{
				QClipboard* clipboard = QApplication::clipboard();
				clipboard->setText(toPlainText());
			}

			return;
		}
		else if (event->key() == Qt::Key_V)
		{

			QClipboard* clipboard = QApplication::clipboard();
			QString str = clipboard->text();


			if (this->selectionState == SelectionState::preselected)
			{
				setText(str);

			}
			else if (this->selectionState == SelectionState::selected) {

				str += this->toPlainText();

				setText(str);

			}

			return;
		}
	}

	//

	SmartCell::keyPressEvent(event);

	if (DoChangeAllCellsSize()) {
		ChangeAllCellsSize();
	}

}

void AdvancedCell::focusOutEvent(QFocusEvent* event)
{
	SmartCell::focusOutEvent(event);
}

void AdvancedCell::mousePressEvent(QMouseEvent* event)
{

	if (event->modifiers() & Qt::AltModifier)
	{
		QClipboard* clipboard = QApplication::clipboard();
		clipboard->setText(toPlainText());
	}
	else 
	{

		movement->SetCurrentPositionF(positionOnGridRow, positionOnGridColumn);

	}
	SmartCell::mousePressEvent(event);
}

void AdvancedCell::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->modifiers() & Qt::AltModifier)
	{
		QClipboard* clipboard = QApplication::clipboard();
		QString str = clipboard->text();

		setText(str);
	}
	

	QTextEdit::mouseReleaseEvent(event);

}

void AdvancedCell::mouseDoubleClickEvent(QMouseEvent* event)
{

	SmartCell::mouseDoubleClickEvent(event);
}

void AdvancedCell::focusInEvent(QFocusEvent* event)
{
	
	QWidget::focusInEvent(event);

	if (event->gotFocus())
	{
		QScrollArea* scrollArea = GetParentScrollArea();

		if (scrollArea) {

			scrollArea->ensureWidgetVisible(this, this->width(), this->height());

		}

	}

}

void AdvancedCell::resizeEvent(QResizeEvent* event)
{

	QTextEdit::resizeEvent(event);

	QScrollArea* scrollArea = GetParentScrollArea();

	if (scrollArea) {

		scrollArea->setMinimumWidth(this->width());

	}

}

bool AdvancedCell::DoChangeAllCellsSize()
{
	int textWidth;

	int maxWidth = 30;

	for (auto cell : allCells) {

		QTextDocument* document = cell->document();
		QFontMetrics fontMetrics(document->defaultFont());
		QSize textSize = fontMetrics.size(0, document->toPlainText());

		textWidth = textSize.width();

		if (maxWidth < textWidth) {
			maxWidth = textWidth;
		}
	}

	if (maxWidth > cellSize - sizeAdmission || maxWidth < cellSize + sizeAdmission) {
		cellSize = maxWidth;
		return true;
	}

	return false;
}

void AdvancedCell::ChangeAllCellsSize()
{

	for (auto cell : allCells) {
		cell->RefreshSize();
	}

}

QScrollArea* AdvancedCell::GetParentScrollArea()
{
	if (this->positionOnGridRow < 0)
		return nullptr;

	return qobject_cast<QScrollArea*>(parent()->parent()->parent());;
}

void AdvancedCell::AnnounceChanges()
{

	isChanged = true;

}

void AdvancedCell::AcceptChanges()
{

	isChanged = false;

}

bool AdvancedCell::IsChanged()
{
	return isChanged;
}

QString AdvancedCell::GetText()
{
	return SmartCell::GetText();
}

void AdvancedCell::TextChanged() 
{

	//if (isC && !isGlobalStationary) {
	//	return;
	//}

	AnnounceChanges();

}
