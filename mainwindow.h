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
    Chifoumi monJeu;

    QPixmap *pierre;
    QPixmap *feuille;
    QPixmap *ciseau;
public slots:
    void Partie();
    void jeu();
    void jouerLeCailloux();
    void jouerLaFeuille();
    void jouerLeCiseau();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
