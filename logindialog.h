#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <database.h>

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog();
    QString getLogin();
    QString getMdp();
    void setMdpFromBd();
public slots:
    bool Valider();
    void Fermer();
private:
    Ui::loginDialog *ui;
    QString login;
    QString mdp;
    QString mdpBd;
    bool connexionOk;
    database *bd;
};

#endif // LOGINDIALOG_H
