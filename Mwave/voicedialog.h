#ifndef VOICEDIALOG_H
#define VOICEDIALOG_H

/////////////Included Files//////////////
#include <QDialog>
#include "workerthread.h"

namespace Ui {
class voiceDialog;
}

class voiceDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit voiceDialog(QWidget *parent = 0);
    workerThread voicethread;
    ~voiceDialog();

private slots:
    void on_recbutton_clicked();

private:
    Ui::voiceDialog *ui;
    bool recbuttonclicked;
};

#endif // VOICEDIALOG_H
