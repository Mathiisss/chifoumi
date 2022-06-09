#ifndef CHIFOUMIDIALOG_H
#define CHIFOUMIDIALOG_H

#include <QDialog>

namespace Ui {
class ChifoumiDialog;
}

class ChifoumiDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChifoumiDialog(QWidget *parent = nullptr);
    ~ChifoumiDialog();
    int getTemps() const;
    int getPoints() const;
    QString getNom() const;
public slots:
    void Valider();

private:
    Ui::ChifoumiDialog *ui;
    int pointsChiffre;
    int tempsChiffre;
    QString nom;
};

#endif // CHIFOUMIDIALOG_H
