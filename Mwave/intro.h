#ifndef INTRO_H
#define INTRO_H

/////////////Included Files//////////////
#include <QDialog>

namespace Ui {
class Intro;
}

class Intro : public QDialog
{
    Q_OBJECT
    
public:
    explicit Intro(QWidget *parent = 0);
    ~Intro();
    
private:
    Ui::Intro *ui;
};

#endif // INTRO_H
