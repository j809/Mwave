#include "setreminder.h"
#include "ui_setreminder.h"
#include <QTime>
#include <QDebug>
extern QString remind_title;
extern QTime set_time;

SetReminder::SetReminder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetReminder)
{
    ui->setupUi(this);   
}

SetReminder::~SetReminder()
{
    delete ui;
}

void SetReminder::on_buttonBox_accepted()
{
    remind_title=ui->title->text();
    set_time.setHMS(ui->hours->value(),ui->minutes->value(),0);
    qDebug()<<set_time;
    qDebug()<<remind_title;
    emit accepted();
    this->close();
    this->deleteLater();
}

void SetReminder::on_buttonBox_rejected()
{
    this->close();
    this->deleteLater();
}
