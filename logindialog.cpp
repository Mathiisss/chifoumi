#include "logindialog.h"
#include "ui_logindialog.h"
#include "chifoumivue.h"
#include <QSqlQuery>
#include <QDebug>


loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    connect(ui->bOk,SIGNAL(accepted()),this,SLOT(Valider()));

}

loginDialog::~loginDialog()
{
    delete ui;
}

bool loginDialog::Valider()
{
    bd = new database;
    loginDialog wine;
    if(bd->openDataBase()==true)
    {
        qDebug()<<"bite";

        setMdpFromBd();
        if(mdpBd==getMdp())
        {
            qDebug()<<"bien prepare";
            return true;

        }
        if (mdpBd!=getMdp())
        {
            qDebug()<<"bonjour";
            wine.show();
            wine.exec();

        }
    }
    else
    {
        qDebug()<<"ERREUR DE CONNEXION";
        return false;
    }
    bd->closeDataBase();
    return false;
}
void loginDialog::Fermer()
{

}
QString loginDialog::getLogin()
{
    return ui->loginEdit->text();
}
QString loginDialog::getMdp()
{
    return ui->mdpEdit->text();
}

void loginDialog::setMdpFromBd()
{
    QSqlQuery requete;
    if (getLogin()=="")
    {
        mdpBd="gdf";
    }
    else
    {
        requete.prepare("SELECT mdp FROM connexion WHERE login LIKE ?");
        requete.addBindValue(getLogin());
        requete.exec();
        while (requete.next())
        {
            qDebug()<<"feur";
            mdpBd=requete.value(0).toString();
            qDebug()<<mdpBd;
        }
    }


}
