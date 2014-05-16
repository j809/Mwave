#ifndef REMINDER_H
#define REMINDER_H

/////////////Included Files//////////////
#include <QDialog>

namespace Ui {
class Reminder;
}

class Reminder : public QDialog
{
    Q_OBJECT
    
public:
    explicit Reminder(QWidget *parent = 0);
    ~Reminder();

private slots:
    void on_okbutton_clicked();

private:
    Ui::Reminder *ui;
};

#endif // REMINDER_H
