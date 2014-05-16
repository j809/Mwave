#include "intro.h"
#include "ui_intro.h"

Intro::Intro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Intro)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);
}

Intro::~Intro()
{
    delete ui;
}
