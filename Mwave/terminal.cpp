#include "terminal.h"
#include "ui_terminal.h"
#include "dashboard.h"
#include <QDesktopWidget>
#include <QTextCursor>
#include <QScrollBar>

extern bool mute;

terminal::terminal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::terminal)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);

    //////////////Inital Positon///////////////
    //setGeometry(457,170,500,350);

    QDesktopWidget* desktop = QApplication::desktop();
    QRect desk_rect = desktop->screenGeometry(desktop->screenNumber(QCursor::pos()));
    this->move(desk_rect.center() - this->rect().center());
    this->move(this->x(),this->y()-110);
    ui->weathericon->hide();
}

terminal::~terminal()
{
    delete ui;
}

void terminal::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mLastMousePosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
        mMoving = true;
    }
}

void terminal::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && mMoving)
    {
        move(event->globalPos() - mLastMousePosition);
        mLastMousePosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void terminal::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = false;
    }
}

void terminal::setterminaltext(QString setthis)
{
    ui->terminaltext->setText(setthis);
    QScrollBar *vScrollBar = ui->terminaltext->verticalScrollBar();
    vScrollBar->triggerAction(QScrollBar::SliderToMinimum);
}

void terminal::appendterminaltext(QString appendthis)
{
    ui->terminaltext->append(appendthis);
    QScrollBar *vScrollBar = ui->terminaltext->verticalScrollBar();
    vScrollBar->triggerAction(QScrollBar::SliderToMinimum);
}

void terminal::show_weathericon(int icon_code)
{
    ui->weathericon->show();
    char buf[100];
    sprintf(buf,"#weathericon{border-image: url(:/weather/weathericons/%d.png);}",icon_code);
    ui->weathericon->setStyleSheet(buf);
}

void terminal::hide_weathericon()
{
    ui->weathericon->hide();
}

void terminal::on_mutebutton_clicked()
{
    if(!mute)
    {
        qDebug()<<"muted";
        mute=true;
        ui->mutebutton->setStyleSheet("#mutebutton{border-image: url(:/basic/images/muted_normal.png)}#mutebutton:hover{border-image: url(:/basic/images/muted_pressed.png);}");
    }
    else
    {
        mute=false;
        ui->mutebutton->setStyleSheet("#mutebutton{border:none}#mutebutton:hover{border-image: url(:/basic/images/unmuted_pressed.png);}");
    }
}

void terminal::scrollup()
{
    QScrollBar *vScrollBar = ui->terminaltext->verticalScrollBar();
    vScrollBar->triggerAction(QScrollBar::SliderSingleStepSub);
}

void terminal::scrolldown()
{
    QScrollBar *vScrollBar = ui->terminaltext->verticalScrollBar();
    vScrollBar->triggerAction(QScrollBar::SliderSingleStepAdd);
}
