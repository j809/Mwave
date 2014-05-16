#ifndef QUITDIALOG_H
#define QUITDIALOG_H

/////////////Included Files//////////////
#include <QDialog>

namespace Ui {
class quitDialog;
}

class quitDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit quitDialog(QWidget *parent = 0);
    ~quitDialog();
    
private slots:
    void on_yesnobuttons_accepted();
    void on_yesnobuttons_rejected();

private:
    Ui::quitDialog *ui;
};

#endif // QUITDIALOG_H
