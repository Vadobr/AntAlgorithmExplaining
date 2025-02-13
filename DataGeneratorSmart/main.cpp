#include "DataGeneratorSmart.h"
#include <QtWidgets/QApplication>

bool isGlobalStationary = true;
int rowPos = 0;
int colPos = 0;

AdvancedCentralCell* focusedCell = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataGeneratorSmart w;
    w.show();
    return a.exec();
}
