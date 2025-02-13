#pragma once

#include <qwidget>
#include <qlayout.h>
#include <qscrollarea.h>
#include <qscrollbar.h>
#include <qtextedit.h>

QWidget* CreateBlackWidget();

class SmartMatrix : public QWidget {

Q_OBJECT

public:

    SmartMatrix();

protected:

    // Objects:

    QWidget* mainWidget;
    QGridLayout* mainGridLayout;

    QWidget* cornerFunctionalWidget;
    QScrollArea* centralScrollArea;
    QScrollArea* leftScrollArea;
    QScrollArea* topScrollArea;

    QGridLayout* cornerFuntionalLayout;

    QWidget* cornerWidget;
    QWidget* leftHatWidget;
    QWidget* topHatWidget;
    QWidget* centralWidget;

    QGridLayout* cornerGridLayout;
    QGridLayout* centralGridLayout;
    QVBoxLayout* leftHatVerticalLayout;
    QHBoxLayout* topHatHorizontalLayout;

    // Object`s sets:

protected:

    std::vector <QObject*> objectList;

    std::vector <QWidget*> widgetList;

    std::vector <QLayout*> layoutList;

    std::vector <QWidget*> qurtersWidgetList;

    std::vector <QScrollArea*> scrollAreaList;

protected:

    virtual void CreateObjects();

    virtual void CreateObjectsSets();

    virtual void SetObjectsDependencies();

    virtual void SetObjectsSetsParameters();

    virtual void SetStyles();

public:

    void Fill(const int& count, QWidget* (*CreateWidgetFunction)(void) = CreateBlackWidget);

    void FillMatrix(const int& count, QWidget* (*CreateWidgetFunction)(void) = CreateBlackWidget);

    void FillSides(const int& count, QWidget* (*CreateWidgetFunction)(void) = CreateBlackWidget);

    void FillLeftSide(const int& count, QWidget* (*CreateWidgetFunction)(void) = CreateBlackWidget);

    void FillTopSide(const int& count, QWidget* (*CreateWidgetFunction)(void) = CreateBlackWidget);

    void FillCorner(QWidget* (*CreateWidgetFunction)(void) = CreateBlackWidget);

    void SetCentralWidget(QWidget* widget, const int& row, const int& column);

    void SetLeftSideWidget(QWidget* widget, const int& row);

    void SetTopSideWidget(QWidget* widget, const int& column);

    void ShowCentralWidget(const int& row, const int& column);

    void HideCentralWidget(const int& row, const int& column);

    void ShowLeftSideWidget(const int& row);

    void HideLeftSideWidget(const int& row);

    void ShowTopSideWidget(const int& column);

    void HideTopSideWidget(const int& column);

public:

    std::string GetElementAsTextEditText(const int& row, const int& column);

    std::string GetLeftHeaderAsTextEditText(const int& row);

    std::string GetTopHeaderAsTextEditText(const int& column);

protected slots:

    void SomeWidgetSelected();

};