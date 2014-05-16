#ifndef SETREMINDER_H
#define SETREMINDER_H

/////////////Included Files//////////////
#include <QDialog>

namespace Ui {
class SetReminder;
}

class SetReminder : public QDialog
{
    Q_OBJECT
    
public:
    explicit SetReminder(QWidget *parent = 0);
    ~SetReminder();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::SetReminder *ui;
};

#endif // SETREMINDER_H
