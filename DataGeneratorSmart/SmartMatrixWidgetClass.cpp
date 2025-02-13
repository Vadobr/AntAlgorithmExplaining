#include "SmartMatrixWidgetClass.h"

QWidget* CreateBlackWidget()
{

    QWidget* widget = new QWidget;

    widget->setMinimumSize(QSize(30, 30));

    widget->setMaximumSize(QSize(30, 30));

    widget->setStyleSheet("background-color: gray;");

    return widget;
}

SmartMatrix::SmartMatrix()
{

    

    CreateObjects();
    CreateObjectsSets();
    SetObjectsSetsParameters();
    SetObjectsDependencies();
    SetStyles();

    leftHatWidget->setMaximumWidth(80);
    topHatWidget->setMaximumHeight(80);
    cornerWidget->setMaximumSize(80, 80);

    leftScrollArea->setMaximumWidth(80);
    topScrollArea->setMaximumHeight(80);
    cornerFunctionalWidget->setMaximumSize(80, 80);

}

void SmartMatrix::CreateObjects()
{

    mainWidget = new QWidget;
    mainGridLayout = new QGridLayout();

    cornerFunctionalWidget = new QWidget();
    centralScrollArea = new QScrollArea;
    leftScrollArea = new QScrollArea;
    topScrollArea = new QScrollArea;

    cornerFuntionalLayout = new QGridLayout();

    cornerWidget = new QWidget();
    leftHatWidget = new QWidget();
    topHatWidget = new QWidget();
    centralWidget = new QWidget();

    cornerGridLayout = new QGridLayout();
    centralGridLayout = new QGridLayout();
    leftHatVerticalLayout = new QVBoxLayout();
    topHatHorizontalLayout = new QHBoxLayout();

}

void SmartMatrix::CreateObjectsSets()
{

    objectList = {
        this,
        mainWidget,
        mainGridLayout,
        cornerFunctionalWidget,
        centralScrollArea,
        leftScrollArea,
        topScrollArea,
        cornerFuntionalLayout,
        cornerWidget,
        leftHatWidget,
        topHatWidget,
        centralWidget,
        cornerGridLayout,
        centralGridLayout,
        leftHatVerticalLayout,
        topHatHorizontalLayout
    };

    widgetList = {
        this,
        mainWidget,
        cornerFunctionalWidget,
        centralScrollArea,
        leftScrollArea,
        topScrollArea,
        cornerWidget,
        leftHatWidget,
        topHatWidget,
        centralWidget
    };

    layoutList = {
        cornerGridLayout,
        centralGridLayout,
        leftHatVerticalLayout,
        topHatHorizontalLayout,
        cornerFuntionalLayout,
        mainGridLayout
    };

    qurtersWidgetList = {
        cornerWidget,
        leftHatWidget,
        topHatWidget,
        centralWidget,
    };

    scrollAreaList = {
        centralScrollArea,
        leftScrollArea,
        topScrollArea
    };
}

void SmartMatrix::SetObjectsSetsParameters()
{
    for (auto object : objectList) {

        

    }

    for (auto object : layoutList) {

        object->setContentsMargins(QMargins(1, 1, 1, 1));

        object->setSpacing(2);

    }

    for (auto object : widgetList) {

        object->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));

    }
    
    this->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));

    for (auto object : qurtersWidgetList) {

    }

    for (auto object : scrollAreaList) {

        object->setWidgetResizable(true);

        object->setFrameShape(QFrame::NoFrame);

    }
}

void SmartMatrix::SetObjectsDependencies()
{

    this->setLayout(mainGridLayout);

    mainGridLayout->addWidget(cornerFunctionalWidget, 0, 0);
    mainGridLayout->addWidget(centralScrollArea, 1, 1);
    mainGridLayout->addWidget(leftScrollArea, 1, 0);
    mainGridLayout->addWidget(topScrollArea, 0, 1);

    cornerFunctionalWidget->setLayout(cornerFuntionalLayout);

    cornerFuntionalLayout->addWidget(cornerWidget);
    centralScrollArea->setWidget(centralWidget);
    leftScrollArea->setWidget(leftHatWidget);
    topScrollArea->setWidget(topHatWidget);

    cornerFuntionalLayout->addWidget(cornerWidget);

    cornerWidget->setLayout(cornerGridLayout);
    centralWidget->setLayout(centralGridLayout);
    leftHatWidget->setLayout(leftHatVerticalLayout);
    topHatWidget->setLayout(topHatHorizontalLayout);

    leftHatVerticalLayout->setAlignment(Qt::AlignCenter);
    cornerGridLayout->setAlignment(Qt::AlignLeft);

    cornerGridLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    leftHatVerticalLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    topHatHorizontalLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    centralGridLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    cornerFuntionalLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    leftScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    leftScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    topScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    topScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    centralScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    centralScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    connect(
        centralScrollArea->verticalScrollBar(), 
        &QScrollBar::valueChanged, 
        this, 
        [&](int value) {
            leftScrollArea->verticalScrollBar()->setValue(value);
        }
    );

    connect(
        centralScrollArea->horizontalScrollBar(),
        &QScrollBar::valueChanged,
        this,
        [&](int value) {
            topScrollArea->horizontalScrollBar()->setValue(value);
        }
    );

    connect(
        leftScrollArea ->verticalScrollBar(),
        &QScrollBar::valueChanged,
        this,
        [&](int value) {
            centralScrollArea->verticalScrollBar()->setValue(value);
        }
    );

    connect(
        topScrollArea->horizontalScrollBar(),
        &QScrollBar::valueChanged,
        this,
        [&](int value) {
            centralScrollArea->horizontalScrollBar()->setValue(value);
        }
    );

    leftScrollArea->verticalScrollBar()->setVisible(false);
    leftScrollArea->horizontalScrollBar()->setVisible(false);
    topScrollArea->verticalScrollBar()->setVisible(false);
    topScrollArea->horizontalScrollBar()->setVisible(false);

}

void SmartMatrix::FillMatrix(const int& count, QWidget* (*CreateWidgetFunction)(void))
{
    for (int i(0); i < count; i++) {
        for (int j(0); j < count; j++) {
            centralGridLayout->addWidget(CreateWidgetFunction(), i, j);
        }
    }
}

void SmartMatrix::FillSides(const int& count, QWidget* (*CreateWidgetFunction)(void))
{
    FillLeftSide(count, CreateWidgetFunction);
    FillTopSide(count, CreateWidgetFunction);
}

void SmartMatrix::FillLeftSide(const int& count, QWidget* (*CreateWidgetFunction)(void))
{
    for (int i(0); i < count; i++) {
        leftHatVerticalLayout->addWidget(CreateWidgetFunction(), i);
    }
}

void SmartMatrix::FillTopSide(const int& count, QWidget* (*CreateWidgetFunction)(void))
{
    for (int i(0); i < count; i++) {
        topHatHorizontalLayout->addWidget(CreateWidgetFunction(), i);
    }
}

void SmartMatrix::FillCorner(QWidget* (*CreateWidgetFunction)(void))
{
    cornerGridLayout->addWidget(CreateWidgetFunction());
}

void SmartMatrix::SetCentralWidget(QWidget* widget, const int& row, const int& column)
{
    
    centralGridLayout->addWidget(widget, row, column);
}

void SmartMatrix::SetLeftSideWidget(QWidget* widget, const int& row)
{
    leftHatVerticalLayout->insertWidget(row, widget);
}

void SmartMatrix::SetTopSideWidget(QWidget* widget, const int& column)
{
    topHatHorizontalLayout->insertWidget(column, widget);
}

void SmartMatrix::ShowCentralWidget(const int& row, const int& column)
{
    centralGridLayout->itemAtPosition(row, column)->widget()->show();
}

void SmartMatrix::HideCentralWidget(const int& row, const int& column)
{
    centralGridLayout->itemAtPosition(row, column)->widget()->hide();
}

void SmartMatrix::ShowLeftSideWidget(const int& row)
{
    leftHatVerticalLayout->itemAt(row)->widget()->show();
}

void SmartMatrix::HideLeftSideWidget(const int& row)
{
    leftHatVerticalLayout->itemAt(row)->widget()->hide();
}

void SmartMatrix::ShowTopSideWidget(const int& column)
{
    topHatHorizontalLayout->itemAt(column)->widget()->show();
}

void SmartMatrix::HideTopSideWidget(const int& column)
{
    topHatHorizontalLayout->itemAt(column)->widget()->hide();
}

std::string SmartMatrix::GetElementAsTextEditText(const int& row, const int& column)
{
    auto a = dynamic_cast<QTextEdit*>(centralGridLayout->itemAtPosition(row, column)->widget());

    auto b = a->toPlainText();

    return b.toStdString();

}

std::string SmartMatrix::GetLeftHeaderAsTextEditText(const int& row)
{
    auto a = dynamic_cast<QTextEdit*>(leftHatVerticalLayout->itemAt(row)->widget());

    auto b = a->toPlainText();

    return b.toStdString();
}

std::string SmartMatrix::GetTopHeaderAsTextEditText(const int& column)
{
    auto a = dynamic_cast<QTextEdit*>(topHatHorizontalLayout->itemAt(column)->widget());

    auto b = a->toPlainText();

    return b.toStdString();
}

void SmartMatrix::SetStyles()
{

    QString style = R"(

        QScrollBar:vertical{
            
            border-radius: 7px;
            background-color: #726aa877;

            width: 15px;
        }
        
        QScrollBar:horizontal {
            
            border-radius: 7px;
            background-color: #726aa877;

            height: 15px;
        }

        QScrollBar::handle {

            border-radius: 7px;
            background-color: #726aa8;
            
            width: 10px;

        }

        QScrollBar::up-arrow, QScrollBar::down-arrow, QScrollBar::left-arrow, QScrollBar::right-arrow {
            background-color: #00000000;
        }

        QScrollBar::add-page, QScrollBar::sub-page {
            background-color: #00000000;
        }

        QScrollBar::add-line, QScrollBar::sub-line {
            background-color: #00000000;
        }

       )";

    this->setStyleSheet(style);

}

void SmartMatrix::Fill(const int& count, QWidget* (*CreateWidgetFunction)(void))
{
    FillMatrix(count, CreateWidgetFunction);
    FillSides(count, CreateWidgetFunction);
    FillCorner(CreateWidgetFunction);
}

void SmartMatrix::SomeWidgetSelected(){

    QWidget* senderWdiget = qobject_cast<QWidget*>(sender());

}