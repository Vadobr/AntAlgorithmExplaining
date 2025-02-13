#pragma once

#include <qdialog.h>
#include <qmainwindow.h>
#include "ui_RandomSettings.h"

class RandomSettingsDialoh :
    public QDialog
{
public:

    RandomSettingsDialoh(QMainWindow* parent, double* randMin, double* randMax, double* dRandMin, double* dRandMax);
    ~RandomSettingsDialoh();

private:

    Ui::Form ui;

    double* randMin;
    double* randMax;
    double* dRandMin;
    double* dRandMax;

};

