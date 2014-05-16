#include "voicedialog.h"
#include "ui_voicedialog.h"
#include <QMovie>
#include "dashboard.h"

extern QString choice;
QMovie *mov;
QAction *escActionvoice;

voiceDialog::voiceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::voiceDialog)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);

    /////////////////Gesture Voice Cancel PgDown Shortcut/////////////////////
    escActionvoice = new QAction(this);
    escActionvoice->setShortcut(Qt::Key_Escape);
    addAction(escActionvoice);

    mov = new QMovie(":/basic/images/spinner.gif");
    mov->setScaledSize(QSize(72,72));
    ui->loader->setMovie(mov);
    recbuttonclicked=false;

    connect(&voicethread,SIGNAL(finished()),this,SLOT(close()));
    connect(ui->recbutton,SIGNAL(clicked()),this,SLOT(close()));
    connect(escActionvoice,SIGNAL(triggered()),this,SLOT(on_recbutton_clicked()));

    voicethread.start();
    mov->start();
    ui->loader->show();
    ui->recstatus->setText("Speak now...");
    ui->recbutton->setToolTip("Stop recording");
}

voiceDialog::~voiceDialog()
{
    system("pkill -9 Mwave_gspeech");
    voicethread.terminate();
    qDebug()<<"Voicethread destroyed";
    delete ui;
}

void voiceDialog::on_recbutton_clicked()
{
    system("pkill -9 Mwave_gspeech");
    voicethread.terminate();
    qDebug()<<"Voicethread terminated!";
    this->close();
    this->deleteLater();
}
