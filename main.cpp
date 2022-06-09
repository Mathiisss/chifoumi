#include "chifoumivue.h"
#include "logindialog.h"
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    bool ok=false;
    QApplication a(argc, argv);
    loginDialog win;
    chifoumiVue w;
    while (ok==false){
        if(win.Valider()==false)
        {
            ok=true;
            w.setWindowTitle("Chifoumi");
            w.show();
        }
    }
    return a.exec();
}
