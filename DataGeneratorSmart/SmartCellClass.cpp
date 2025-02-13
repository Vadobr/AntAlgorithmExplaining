#include "SmartCellClass.h"

void SmartCell::NextSelectionState()
{

    int intSelectionState = int(this->selectionState);

    if (intSelectionState < 2) {
        intSelectionState++;
    }

    SetSelectionState(SelectionState(intSelectionState));

}

void SmartCell::SetStyleByState()
{

    CorrectText();

    if (this->selectionState == SelectionState::disabled) {


        this->setDisabled(true);
        this->setStyleSheet("background-color: white; border: 0px solid gray;");
        this->setReadOnly(true);
        this->clear();

    }
    else if (this->selectionState == SelectionState::unselected) {
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

void SmartCell::SetSelectionState(const SelectionState& newSelectionState)
{
    this->selectionState = newSelectionState;

    SetStyleByState();
}

SmartCell::SmartCell(QWidget* window) : QTextEdit(window)
{

    selectionState = unselected;

    this->SetStyleByState();

    this->setMinimumSize(QSize(30, 30));
    this->setMaximumSize(QSize(30, 30));

    QFont font;
    font.setFamily("Consolas");
    font.setPointSize(10);

    this->setFont(font);

    this->setAlignment(Qt::AlignCenter);

}

void SmartCell::keyPressEvent(QKeyEvent* event)
{
    
    if (
        event->key() == Qt::Key_Alt ||
        event->key() == Qt::Key_Control ||
        event->key() == Qt::Key_Shift ||
        event->key() == Qt::Key_CapsLock ||
        event->key() == Qt::Key_Tab
        ) {

        return;

    }

    if (ToLimitInput(event)) {
    
        if( !((event->key() == Qt::Key_Comma || event->key() == Qt::Key_Period) && this->selectionState == SelectionState::preselected))
        {
            return;
        }    

    }

    if (this->selectionState == SelectionState::preselected) {

        if (
            event->key() != Qt::Key_Left &&
            event->key() != Qt::Key_Right &&
            event->key() != Qt::Key_Up &&
            event->key() != Qt::Key_Down 
            
        ) {
            if (
                event->key() != Qt::Key_Return &&
                event->key() != Qt::Key_Enter) {

                this->setText("");
            }

            SetSelectionState(SelectionState::selected);

            if (
                event->key() == Qt::Key_Return ||
                event->key() == Qt::Key_Enter) {

                return;
            }

        }
        else {

            
        
        }

    }
    else if(this->selectionState == SelectionState::selected){
        if (
            event->key() == Qt::Key_Return ||
            event->key() == Qt::Key_Enter)
        {
            SetSelectionState(SelectionState::preselected);

            return;
        }
    }

    QTextEdit::keyPressEvent(event);
    
}

void SmartCell::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {

        NextSelectionState();

        SetStyleByState();

    }
    else {

        QTextEdit::mousePressEvent(event); // Виклик базового обробника подій

    }
}

void SmartCell::mouseDoubleClickEvent(QMouseEvent* event)
{
    SetSelectionState(SelectionState::selected);

}

bool SmartCell::ToLimitInput(QKeyEvent* event)
{
    /*

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

    */

    return false;
}

void SmartCell::focusOutEvent(QFocusEvent* event)
{

    SetSelectionState(SelectionState::unselected);

    QTextEdit::focusOutEvent(event); // Виклик базового обробника подій для забезпечення правильної роботи
}

void SmartCell::CorrectText()
{

    /*

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

    if(newText.size() > 0 && newText[newText.size() - 1] == ',') {
        newText.push_back('0');
    }

    if (newText.size() > 0 && newText[0] == ',') {
        newText.push_front('0');
    }

    this->setText(newText);

    */
}

QString SmartCell::GetText()
{
    return this->toPlainText();
}
