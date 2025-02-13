#pragma once

#include <qdialog.h>
#include <qmainwindow.h>

#include "ui_SizeChangeForm.h"

class ChangeSizeDilog :
    public QDialog
{
public:
    ChangeSizeDilog(QMainWindow* parent, int N);
    ~ChangeSizeDilog();

private:

    Ui::SizeChangeForm ui;

private slots:

    void onOK();

    void onCancel();

};

