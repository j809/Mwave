#include "voicewindow.h"
#include "ui_voicewindow.h"

voiceWindow::voiceWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::voiceWindow)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);
}

voiceWindow::~voiceWindow()
{
    delete ui;
}

void voiceWindow::closeEvent(QCloseEvent *event)
{
    //event->ignore();
}
