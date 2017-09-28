#include "menue.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    menue w;
    w.show();

    return a.exec();
}
