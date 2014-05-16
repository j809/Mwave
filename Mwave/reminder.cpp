#include "reminder.h"
#include "ui_reminder.h"

extern QString remind_title;
extern QTime set_time;

Reminder::Reminder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reminder)
{
    this->setModal(true);
    ui->setupUi(this);
    ui->remindertitle->setText(remind_title);
}

Reminder::~Reminder()
{
    delete ui;
}

void Reminder::on_okbutton_clicked()
{
    this->close();
    this->deleteLater();
}
