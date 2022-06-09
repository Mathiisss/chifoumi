#include "chifoumidialog.h"
#include "ui_chifoumidialog.h"
#include <QMessageBox>

ChifoumiDialog::ChifoumiDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChifoumiDialog)
{
    ui->setupUi(this);
    connect(ui->BoutonValider,SIGNAL(accepted()),this,SLOT(Valider()));
}

ChifoumiDialog::~ChifoumiDialog()
{
    delete ui;
}

void ChifoumiDialog::Valider()
{
    nom = ui->nomResul->text();
    if(nom=="")// cas où le joueur n'a pas mit de nom
    {
        nom="Vous";
    }
    QString temps = ui->tempsResul->text();
    QString points = ui->pointsResul->text();
    bool ok;
    if (points=="")// cas où le joueur n'a pas mit de points
    {
        pointsChiffre=5;
    }
    else
    {
        pointsChiffre= points.toInt(&ok,10);
    }
    if (temps=="")// cas où le joueur n'a pas mit de temps
    {
        tempsChiffre=30;
    }
    else
    {
        tempsChiffre = temps.toInt(&ok,10);
    }
    this->close();

}
int ChifoumiDialog::getPoints() const
{
    return pointsChiffre;
}
int ChifoumiDialog::getTemps() const
{
    if (tempsChiffre==0)
    {
        return 30;
    }
    return tempsChiffre;
}
QString ChifoumiDialog::getNom() const
{
    if(nom=="")
    {
        return "Vous";
    }
    else
    {
        return nom;
    }
}
