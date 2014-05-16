#include "quitdialog.h"
#include "ui_quitdialog.h"

extern bool appfocused;

quitDialog::quitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::quitDialog)
{
    ui->setupUi(this);
}

quitDialog::~quitDialog()
{
    delete ui;
}

void quitDialog::on_yesnobuttons_accepted()
{
    qApp->quit();
}

void quitDialog::on_yesnobuttons_rejected()
{
    this->close();
    this->deleteLater();
}
