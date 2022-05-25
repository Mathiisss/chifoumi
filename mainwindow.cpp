#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->boutonNouvellePartie,SIGNAL(clicked()),this,SLOT(Partie()));
    connect(ui->boutonPierre,SIGNAL(clicked()),this,SLOT(jouerLeCailloux()));
    connect(ui->boutonFeuille,SIGNAL(clicked()),this,SLOT(jouerLaFeuille()));
    connect(ui->boutonCiseau,SIGNAL(clicked()),this,SLOT(jouerLeCiseau()));

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
        texteLabel=ui->scoreJoueur->text();
        score=texteLabel.toInt();
        score++;
        texteLabel.setNum(score);
        ui->scoreJoueur->setText(texteLabel);
        ui->scoreJoueur->setFont(QFont("arial",18,100,false));
        ui->scoreJoueur->setAlignment(Qt::AlignCenter);

    }
    else if (monJeu.determinerGagnant()=='M')
    {
        texteLabel=ui->scoreMachine->text();
        score=texteLabel.toInt();
        score++;
        texteLabel.setNum(score);
        ui->scoreMachine->setText(texteLabel);
        ui->scoreMachine->setFont(QFont("arial",18,100,false));
        ui->scoreMachine->setAlignment(Qt::AlignCenter);
    }
    else
    {

    }
}