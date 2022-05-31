#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->boutonNouvellePartie,SIGNAL(clicked()),this,SLOT(Partie()));
    connect(ui->boutonPierre,SIGNAL(clicked()),this,SLOT(jouerLeCailloux()));
    connect(ui->boutonFeuille,SIGNAL(clicked()),this,SLOT(jouerLaFeuille()));
    connect(ui->boutonCiseau,SIGNAL(clicked()),this,SLOT(jouerLeCiseau()));
    connect(ui->actionQuitter,SIGNAL(triggered()),this,SLOT(quitter()));
    connect(ui->actionA_propos_de,SIGNAL(triggered()),this,SLOT(aPropos()));

    pierre = new QPixmap(":/chifoumi/images/pierre.gif");
    ciseau = new QPixmap(":/chifoumi/images/ciseau.gif");
    feuille = new QPixmap(":/chifoumi/images/papier.gif");


}

MainWindow::~MainWindow()
{
    delete ui;
}

//SOUS PROGRAMMES

void MainWindow::Partie()
{

    ui->boutonCiseau->setEnabled(true);
    ui->boutonFeuille->setEnabled(true);
    ui->boutonPierre->setEnabled(true);

}

void MainWindow::jouerLeCailloux(){
    monJeu.setCoupJoueur(Chifoumi::pierre);
    ui->coupJoueur->setPixmap(*pierre);
    jeu();

}

void MainWindow::jouerLaFeuille(){
    monJeu.setCoupJoueur(Chifoumi::papier);
    ui->coupJoueur->setPixmap(*feuille);
    jeu();
}

void MainWindow::jouerLeCiseau(){
    monJeu.setCoupJoueur(Chifoumi::ciseau);
    ui->coupJoueur->setPixmap(*ciseau);
    jeu();

}
bool MainWindow::arretPointGagnant(int point)
{
    if(point==5){
        return true;
    }
    else
    {
        return false;
    }
}

void MainWindow::jeu()
{
    QString texteLabel;
    int score;
    monJeu.setCoupMachine(monJeu.genererUnCoup());
    switch (monJeu.getCoupMachine()) {
    case Chifoumi::pierre:
        ui->coupMachine->setPixmap(*pierre);
        break;
    case Chifoumi::papier:
        ui->coupMachine->setPixmap(*feuille);
        break;
    case Chifoumi::ciseau:
        ui->coupMachine->setPixmap(*ciseau);
        break;
    default:
        break;
    }
    if(monJeu.determinerGagnant()=='J')
    {
        monJeu.majScores('J');
        score=monJeu.getScoreJoueur();
        texteLabel.setNum(score);
        ui->scoreJoueur->setText(texteLabel);
        ui->scoreJoueur->setFont(QFont("arial",18,100,false));
        ui->scoreJoueur->setAlignment(Qt::AlignCenter);
        if(arretPointGagnant(monJeu.getScoreJoueur()))
        {
            QMessageBox *finPartieJoueur;
            finPartieJoueur = new QMessageBox;
            finPartieJoueur->setWindowTitle("Fin de Partie");
            finPartieJoueur->setInformativeText("Felicitation vous remportez la partie!!!");
            finPartieJoueur->exec();
            finDePartie();
        }

    }
    else if (monJeu.determinerGagnant()=='M')
    {
        monJeu.majScores('M');
        score=monJeu.getScoreMachine();
        texteLabel.setNum(score);
        ui->scoreMachine->setText(texteLabel);
        ui->scoreMachine->setFont(QFont("arial",18,100,false));
        ui->scoreMachine->setAlignment(Qt::AlignCenter);

        if(arretPointGagnant(monJeu.getScoreMachine()))
        {
            QMessageBox *finPartieMachine;
            finPartieMachine = new QMessageBox;
            finPartieMachine->setWindowTitle("Fin de Partie");
            finPartieMachine->setInformativeText("Dommage la Machine remporte la partie...");
            finPartieMachine->exec();
            finDePartie();
        }

    }
    else
    {

    }
}
void MainWindow::quitter()
{
    this->close();
}
void MainWindow::aPropos()
{
    QMessageBox *box;
    box = new QMessageBox;
    box->setWindowTitle("A propos du Chifoumi");
    box->setInformativeText("CHIFOUMI v3 \n"
                            "Date de création : 18/04/2022\n"
                            "Créateur: G.Arricastres, M.Lague, M.Segot");
    box->exec();



}

void MainWindow::finDePartie()
{
    QString texteLabel;
    ui->boutonCiseau->setEnabled(false);
    ui->boutonFeuille->setEnabled(false);
    ui->boutonPierre->setEnabled(false);
    monJeu.initCoups();
    monJeu.initScores();
    texteLabel.setNum(monJeu.getScoreMachine());
    ui->scoreMachine->setText(texteLabel);
    ui->scoreMachine->setFont(QFont("arial",18,100,false));
    ui->scoreMachine->setAlignment(Qt::AlignCenter);
    ui->scoreJoueur->setText(texteLabel);
    ui->scoreJoueur->setFont(QFont("arial",18,100,false));
    ui->scoreJoueur->setAlignment(Qt::AlignCenter);
}
