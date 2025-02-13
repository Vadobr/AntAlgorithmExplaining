#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DataGeneratorSmart.h"

#include "AdvancedSmartMatrix.h"
#include "TransitionsMatrix.h"
#include "RandomSettingsDialoh.h"
#include <qtimer.h>
#include <Windows.h>
#include "ChangeSizeDilog.h"
#include <random>
#include "FileThatInsteadAPI.h"
#include <qfile.h>

class DataGeneratorSmart : public QMainWindow
{
    Q_OBJECT

public:
    DataGeneratorSmart(QWidget *parent = nullptr);
    ~DataGeneratorSmart();

private:
    Ui::DataGeneratorSmartClass ui;

private:
    AdvancedSmartMatrix* matrix;
    TransitionsMatrix model;

    void Resize(int N);

private:

    double randomMin;
    double randomMax;
    double dRandomMin;
    double dRandomMax;

private slots:

    void AllTo0();

    void AllTo1();

    void AllRandom();

    void AddRandom();

    void onRandomSettings();

private slots:

    void ViewToModel();

    void Plus1();

    void Plus10();

    void Minus1();

    void Minus10();

    void onCustomResize();

private slots:

    void onTimeout();

public:

    

};
