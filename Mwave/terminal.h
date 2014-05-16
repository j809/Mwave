#ifndef TERMINAL_H
#define TERMINAL_H

/////////////Included Files//////////////
#include <QWidget>
#include <QMouseEvent>
#include <QTimer>

namespace Ui {
class terminal;
}

class terminal : public QWidget
{
    Q_OBJECT
    
public:
    explicit terminal(QWidget *parent = 0);
    ~terminal();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent* event);
    void setterminaltext(QString);
    void appendterminaltext(QString);
    void show_weathericon(int);
    void hide_weathericon();

public slots:
    void on_mutebutton_clicked();
    void scrollup();
    void scrolldown();

private:
    Ui::terminal *ui;
    QPoint mLastMousePosition;
    bool mMoving;
};

#endif // TERMINAL_H
