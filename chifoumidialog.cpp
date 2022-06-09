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
       QString temps = ui->tempsResul->text();
       QString points = ui->pointsResul->text();
       while(temps<0 and points<0)
       {
           QMessageBox *finPartieMachine;
           finPartieMachine = new QMessageBox;
           finPartieMachine->setWindowTitle("Saisi incorrect");
           finPartieMachine->setInformativeText("Le temps et le score doivent être supérieur à 0");
           finPartieMachine->exec();
           ui->tempsResul->text();
           points = ui->pointsResul->text();
       }

       bool ok;
       tempsChiffre = temps.toInt(&ok,10);
       pointsChiffre= points.toInt(&ok,10);
       this->close();

}
int ChifoumiDialog::getPoints() const
{
    return pointsChiffre;
}
int ChifoumiDialog::getTemps() const
{
    return tempsChiffre;
}
QString ChifoumiDialog::getNom() const
{
    return nom;
}
