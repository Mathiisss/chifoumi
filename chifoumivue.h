#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QPixmap"
#include "chifoumi.h"
#include "chifoumidialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class chifoumiVue : public QMainWindow
{
    Q_OBJECT

public:
    chifoumiVue(QWidget *parent = nullptr);
    ~chifoumiVue();
private:
    QTimer  *timer;
    Chifoumi monJeu;
    QPixmap *pierre;
    QPixmap *feuille;
    QPixmap *ciseau;
    int seconde;
    bool enPause = false;
    int goal;
    ChifoumiDialog chifoumiAff;

public slots:
    void Partie();
    void jeu();
    void jouerLeCailloux();
    void jouerLaFeuille();
    void jouerLeCiseau();
    void quitter();
    void aPropos();
    void time();
    void mettrePause();
    void afficherDialog();
public:
    bool arretPointGagnant(int);
    void finDePartie();
    char defGagnant(int,int);



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
