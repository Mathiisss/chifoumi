#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(ui->boutonNouvellePartie,SIGNAL(clicked()),this,SLOT(Partie()));
    connect(ui->boutonPierre,SIGNAL(clicked()),this,SLOT(jouerLeCailloux()));
    connect(ui->boutonFeuille,SIGNAL(clicked()),this,SLOT(jouerLaFeuille()));
    connect(ui->boutonCiseau,SIGNAL(clicked()),this,SLOT(jouerLeCiseau()));
    connect(ui->actionQuitter,SIGNAL(triggered()),this,SLOT(quitter()));
    connect(ui->actionA_propos_de,SIGNAL(triggered()),this,SLOT(aPropos()));
    connect(timer,SIGNAL(timeout()),this,SLOT(time()));
    connect(ui->bouttonPause,SIGNAL(clicked()),this,SLOT(mettrePause()));

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
    ui->scoreJoueur->setText("0");
    ui->scoreJoueur->setFont(QFont("arial",18,100,false));
    ui->scoreJoueur->setAlignment(Qt::AlignCenter);
    ui->scoreMachine->setText("0");
    ui->scoreMachine->setFont(QFont("arial",18,100,false));
    ui->scoreMachine->setAlignment(Qt::AlignCenter);
    ui->boutonCiseau->setEnabled(true);
    ui->boutonFeuille->setEnabled(true);
    ui->boutonPierre->setEnabled(true);
    ui->bouttonPause->setEnabled(true);
    seconde = 30;
    timer->start();
    time();

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
    timer->stop();
    ui->boutonCiseau->setEnabled(false);
    ui->boutonFeuille->setEnabled(false);
    ui->boutonPierre->setEnabled(false);
    ui->boutonNouvellePartie->setEnabled(true);
    ui->bouttonPause->setEnabled(false);
    monJeu.initCoups();
    monJeu.initScores();
    texteLabel.setNum(monJeu.getScoreMachine());
    ui->scoreMachine->setText(texteLabel);
    ui->scoreMachine->setFont(QFont("arial",18,100,false));
    ui->scoreMachine->setAlignment(Qt::AlignCenter);
    ui->scoreJoueur->setText(texteLabel);
    ui->scoreJoueur->setFont(QFont("arial",18,100,false));
    ui->scoreJoueur->setAlignment(Qt::AlignCenter);
    ui->Temps->setText("Partie Terminé");
    ui->Temps->setFont(QFont("arial",8,100,false));
    ui->Temps->setAlignment(Qt::AlignCenter);

}

void MainWindow::time()
{
    QString valTemps;
    if (seconde==0)
    {
        timer->stop();
        QMessageBox *finPartie;
        finPartie = new QMessageBox;
        QString gagnant;
        ui->Temps->setText("");
        ui->Temps->setFont(QFont("arial",8,100,false));
        ui->Temps->setAlignment(Qt::AlignCenter);
        if(defGagnant(monJeu.getScoreJoueur(),monJeu.getScoreMachine())=='J')
        {
            gagnant="Felicitation vous remportez la partie!!! Avec un score de ";
            gagnant.append(QString::number(monJeu.getScoreJoueur()));
            finPartie->setWindowTitle("Fin de Partie");
            finPartie->setInformativeText(gagnant);
            finPartie->exec();
            finDePartie();
        }
        else if(defGagnant(monJeu.getScoreJoueur(),monJeu.getScoreMachine())=='M')
        {
            gagnant="Dommage la Machine remporte la partie... La machine a un score de ";
            gagnant.append(QString::number(monJeu.getScoreMachine()));
            finPartie->setWindowTitle("Fin de Partie");
            finPartie->setInformativeText(gagnant);
            finPartie->exec();
            finDePartie();
        }
        else if(defGagnant(monJeu.getScoreJoueur(),monJeu.getScoreMachine())=='E')
        {
            gagnant="Vous avez fait une égalité contre la machine. Avec un score de ";
            gagnant.append(QString::number(monJeu.getScoreJoueur()));
            finPartie->setWindowTitle("Fin de Partie");
            finPartie->setInformativeText(gagnant);
            finPartie->exec();
            finDePartie();
        }
        finDePartie();

    }
    else
    {
        seconde--;
        valTemps ="Temps restant: ";
        valTemps.append(QString::number(seconde));
        ui->Temps->setText(valTemps);
        ui->Temps->setFont(QFont("arial",8,100,false));
        ui->Temps->setAlignment(Qt::AlignCenter);
    }

}

char MainWindow::defGagnant(int scoreJoueur,int scoreMachine)
{
    if(scoreJoueur>scoreMachine)
    {
        return 'J';
    }
    else if (scoreJoueur<scoreMachine)
    {
        return 'M';
    }
    else
    {
        return 'E';
    }
}

void MainWindow::mettrePause()
{

    if (enPause==true)
    {
        ui->boutonCiseau->setEnabled(true);
        ui->boutonFeuille->setEnabled(true);
        ui->boutonPierre->setEnabled(true);
        ui->boutonNouvellePartie->setEnabled(true);
        ui->bouttonPause->setText("Pause");
        enPause=false;
        timer->start();
    }
    else
    {
        timer->stop();
        ui->boutonCiseau->setEnabled(false);
        ui->boutonFeuille->setEnabled(false);
        ui->boutonPierre->setEnabled(false);
        ui->boutonNouvellePartie->setEnabled(false);
        ui->bouttonPause->setText("Reprise Jeu");
        enPause=true;
    }
}



