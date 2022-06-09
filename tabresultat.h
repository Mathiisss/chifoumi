#ifndef TABRESULTAT_H
#define TABRESULTAT_H

#include <QDialog>
#include <database.h>

namespace Ui {
class tabResultat;
}

class tabResultat : public QDialog
{
    Q_OBJECT

public:
    explicit tabResultat(QWidget *parent = nullptr);
    ~tabResultat();
    void remplirTable();

private:
    Ui::tabResultat *ui;
    database *bd;
};

#endif // TABRESULTAT_H
