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

        setMdpFromBd();
        if(mdpBd==getMdp())
        {
            return true;

        }
        if (mdpBd!=getMdp())
        {
            wine.show();
            wine.exec();

        }
    }
    else
    {
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
            mdpBd=requete.value(0).toString();
        }
    }


}
void loginDialog::enregistrerDialog(QString nomJoueur,int scoreJoueur,int scoreMachine, int dureePartie)
{

    QSqlQuery larequete;
    larequete.prepare("INSERT INTO StockPartie(NomJoueur,ScoreJoueur,ScoreMachine,TempsPartie) VALUES (:nomJ, :scoreJ, :scoreM, :Temps)");
    larequete.bindValue(":nomJ", nomJoueur);
    larequete.bindValue(":scoreJ", scoreJoueur);
    larequete.bindValue(":scoreM", scoreMachine);
    larequete.bindValue(":Temps", dureePartie);
    larequete.exec();
}
