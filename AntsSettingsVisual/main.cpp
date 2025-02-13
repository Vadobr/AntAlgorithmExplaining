#include "AntsSettingsVisual.h"
#include <QtWidgets/QApplication>
#include "AlgorythmsEntry.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AntsSettingsVisual w;
    w.show();
    return a.exec();
}
