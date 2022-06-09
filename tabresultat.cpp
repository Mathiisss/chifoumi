#include "tabresultat.h"
#include "ui_tabresultat.h"
#include "database.h"
#include <QSqlTableModel>
#include <QSqlQuery>

tabResultat::tabResultat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tabResultat)
{
    ui->setupUi(this);
}

tabResultat::~tabResultat()
{
    delete ui;
}

void tabResultat::remplirTable()
{
    bd = new database;
    bd->openDataBase();
    QSqlQueryModel *model= new QSqlQueryModel;

    model->setQuery("SELECT * FROM StockPartie");
    ui->TableResul->setModel(model);
}

