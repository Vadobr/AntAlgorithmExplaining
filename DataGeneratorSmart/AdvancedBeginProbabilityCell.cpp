#include "AdvancedBeginProbabilityCell.h"

AdvancedProbabilityCell::AdvancedProbabilityCell(const int& positionOnGridColumn) :
    AdvancedCell(-1, positionOnGridColumn, movement)
{
}

bool AdvancedProbabilityCell::ToLimitInput(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Backspace ||
        event->key() == Qt::Key_Delete ||
        event->key() == Qt::Key_Left ||
        event->key() == Qt::Key_Right ||
        event->key() == Qt::Key_Home ||
        event->key() == Qt::Key_End ||
        event->key() == Qt::Key_Return ||
        event->key() == Qt::Key_Enter)
    {
        return false;
    }

    QRegularExpression regex("^[0-9]*([.,][0-9]*)?$");

    QString text = this->toPlainText();

    text.insert(this->textCursor().position(), event->text());

    if (regex.match(text).hasMatch())
    {
        return false;
    }

    return true;

}

void AdvancedProbabilityCell::CorrectText()
{
    QString oldText = this->toPlainText();

    QString newText;

    for (int i(0); i < oldText.size(); i++) {
        if (oldText[i] == '.')
            newText.push_back(',');
        else if (oldText[i] == '\n')
            ;
        else
            newText.push_back(oldText[i]);
    }

    if (newText.size() > 0 && newText[newText.size() - 1] == ',') {
        newText.push_back('0');
    }

    if (newText.size() > 0 && newText[0] == ',') {
        newText.push_front('0');
    }

    this->setText(newText);
}

void AdvancedProbabilityCell::SetLinckedCells(SmartCell* leftHeader, SmartCell* topHeader)
{
    this->leftHeader = leftHeader;

    this->topHeader = topHeader;

}

void AdvancedProbabilityCell::focusInEvent(QFocusEvent* event)
{

    AdvancedCell::focusInEvent(event);

    if (this->positionOnGridRow < 0)
        return;

    leftHeader->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #ffef5c, stop:1 #00000000);");

    topHeader->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ffef5c, stop:1 #00000000);");

}

void AdvancedProbabilityCell::focusOutEvent(QFocusEvent* event)
{

    AdvancedCell::focusOutEvent(event);

    if (this->positionOnGridRow < 0)
        return;

    leftHeader->SetStyleByState();

    topHeader->SetStyleByState();

}


