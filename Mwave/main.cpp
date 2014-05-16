#include "intro.h"
#include "dashboard.h"
#include "terminal.h"
#include <QApplication>
#include <QObject>

QString choice;
QString saythis;
QString city_name = "none";
QString mode = "keyboard";
QString voiceoutput;
QString newscode;
QString remind_title;
QTime set_time;
bool appfocused=true;
bool enterneeded=true;
bool mute;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Intro i;
    Dashboard d;
    i.show();

    QTimer *showintro = new QTimer;
    showintro->start(2500);
    d.connect(showintro,SIGNAL(timeout()),SLOT(show()));
    i.connect(showintro,SIGNAL(timeout()),SLOT(close()));
    showintro->connect(showintro,SIGNAL(timeout()),SLOT(deleteLater()));

    return a.exec();
}
