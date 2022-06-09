#include "chifoumivue.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    chifoumiVue w;
    w.show();
    return a.exec();
}
