#include "logindialog.h"
#include "ui_logindialog.h"
#include "chifoumivue.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>


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
    if(bd->openDataBase()==true)//verification que la base est accessible
    {

        setMdpFromBd();
        if(mdpBd==getMdp())
        {
            // identifiant et mdp: correct
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
        QMessageBox *finPartieMachine;
        finPartieMachine = new QMessageBox;
        finPartieMachine->setWindowTitle("Base de donnée");
        finPartieMachine->setInformativeText("La base de donnée est actuellement innacessible.\n"
                                             "Le jeu est désormais en mode hors ligne");
        finPartieMachine->exec();
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
        requete.prepare("SELECT mdp FROM connexion WHERE login LIKE ?");//recuperation du mdp en fonction du login
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
    larequete.bindValue(":nomJ", nomJoueur);//recuperation du nom dans la bd
    larequete.bindValue(":scoreJ", scoreJoueur);//recuperation du score joueur dans la bd
    larequete.bindValue(":scoreM", scoreMachine);//recuperation du score machine dans la bd
    larequete.bindValue(":Temps", dureePartie);//recuperation du temps dans la bd
    larequete.exec();
}
