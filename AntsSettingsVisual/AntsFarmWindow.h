#pragma once
#include "PCHNames.h"

#include "ui_AntsFarm.h"
#include "AlgorythmsEntry.h"

class AntsFarmWindow :
    public QWidget
{

public:

    AntsFarmWindow();

    ~AntsFarmWindow();

private:

    Ui::AntsFarm ui;
    
    QTimer* timer;

protected:

    void paintEvent(QPaintEvent*) override;
    
private:

};

