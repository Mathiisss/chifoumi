#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QPixmap"
#include "chifoumi.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QTimer  *timer;
    Chifoumi monJeu;
    QPixmap *pierre;
    QPixmap *feuille;
    QPixmap *ciseau;
    int seconde;
    bool enPause = false;
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
public:
    bool arretPointGagnant(int);
    void finDePartie();
    char defGagnant(int,int);



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
