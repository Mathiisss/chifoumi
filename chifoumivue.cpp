#include "chifoumivue.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <chifoumidialog.h>



chifoumiVue::chifoumiVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    goal=5;
    timer = new QTimer(this);
    timer->setInterval(1000);
    seconde = 30;
    connect(ui->boutonNouvellePartie,SIGNAL(clicked()),this,SLOT(Partie()));
    connect(ui->boutonPierre,SIGNAL(clicked()),this,SLOT(jouerLeCailloux()));
    connect(ui->boutonFeuille,SIGNAL(clicked()),this,SLOT(jouerLaFeuille()));
    connect(ui->boutonCiseau,SIGNAL(clicked()),this,SLOT(jouerLeCiseau()));
    connect(ui->actionQuitter,SIGNAL(triggered()),this,SLOT(quitter()));
    connect(ui->actionA_propos_de,SIGNAL(triggered()),this,SLOT(aPropos()));
    connect(timer,SIGNAL(timeout()),this,SLOT(time()));
    connect(ui->bouttonPause,SIGNAL(clicked()),this,SLOT(mettrePause()));
    connect(ui->actionParametres,SIGNAL(triggered()),this,SLOT(afficherDialog()));

    pierre = new QPixmap(":/chifoumi/images/pierre.gif");
    ciseau = new QPixmap(":/chifoumi/images/ciseau.gif");
    feuille = new QPixmap(":/chifoumi/images/papier.gif");


}

chifoumiVue::~chifoumiVue()
{
    delete ui;
}

//SOUS PROGRAMMES

void chifoumiVue::Partie()
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
    ui->actionParametres->setEnabled(false);
    timer->start();
    time();

}

void chifoumiVue::jouerLeCailloux(){
    monJeu.setCoupJoueur(Chifoumi::pierre);
    ui->coupJoueur->setPixmap(*pierre);
    jeu();

}

void chifoumiVue::jouerLaFeuille(){
    monJeu.setCoupJoueur(Chifoumi::papier);
    ui->coupJoueur->setPixmap(*feuille);
    jeu();
}

void chifoumiVue::jouerLeCiseau(){
    monJeu.setCoupJoueur(Chifoumi::ciseau);
    ui->coupJoueur->setPixmap(*ciseau);
    jeu();

}
bool chifoumiVue::arretPointGagnant(int point)
{
    if(point==goal){
        return true;
    }
    else
    {
        return false;
    }
}



void chifoumiVue::jeu()
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
            timer->stop();
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
            timer->stop();
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
void chifoumiVue::quitter()
{
    this->close();
}
void chifoumiVue::aPropos()
{
    QMessageBox *box;
    box = new QMessageBox;
    box->setWindowTitle("A propos du Chifoumi");
    box->setInformativeText("CHIFOUMI v3 \n"
                            "Date de création : 18/04/2022\n"
                            "Créateur: G.Arricastres, M.Lague, M.Segot");
    box->exec();



}

void chifoumiVue::finDePartie()
{
    QString texteLabel;
    loginBd.enregistrerDialog(chifoumiAff.getNom(),monJeu.getScoreJoueur(),monJeu.getScoreMachine(),(chifoumiAff.getTemps()-seconde));
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
    seconde=30;
    goal = 5;
    ui->labelGoal->setNum(goal);
    ui->labelGoal->setFont(QFont("Times",12,40,false));
    ui->labelGoal->setAlignment(Qt::AlignCenter);
    ui->labelGoal->setStyleSheet("color: #606060;");
    ui->actionParametres->setEnabled(true);

}

void chifoumiVue::time()
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

char chifoumiVue::defGagnant(int scoreJoueur,int scoreMachine)
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

void chifoumiVue::mettrePause()
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

void chifoumiVue::afficherDialog()
{

    chifoumiAff.show();
    chifoumiAff.exec();

    if(chifoumiAff.getNom()!="")
    {
        ui->Vous->setText(chifoumiAff.getNom());
        ui->Vous->setFont(QFont("arial",18,100,false));
        ui->Vous->setAlignment(Qt::AlignCenter);
    }
    if(chifoumiAff.getTemps()!=0)
    {
        seconde = chifoumiAff.getTemps();
    }
    if(chifoumiAff.getPoints()!=0)
    {
        goal = chifoumiAff.getPoints();
        ui->labelGoal->setNum(goal);
        ui->labelGoal->setFont(QFont("Times",12,40,false));
        ui->labelGoal->setAlignment(Qt::AlignCenter);
        ui->labelGoal->setStyleSheet("color: #606060;");
    }
}



