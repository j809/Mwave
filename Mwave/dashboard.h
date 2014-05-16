#ifndef DASHBOARD_H
#define DASHBOARD_H

/////////////Included Files//////////////
#include <QMainWindow>
#include <QMouseEvent>
#include "terminal.h"
#include "workerthread.h"
#include "voicedialog.h"

namespace Ui {
class Dashboard;
}

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = 0);
    ~Dashboard();

public slots:
    void on_closebutton_clicked();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *);
    void on_voicebutton_clicked();
    void DeActivate();
    void user_input();
    void ask_for_input();
    void on_select();
    void brightness();
    void inc_bright();
    void dec_bright();
    void volume();
    void inc_volume();
    void dec_volume();
    void weather();
    void handle_city_results();
    void tick();
    void load_bulb_default_image();
    void news();
    void handle_news_results();
    void define();
    void handle_define_results();
    void remove_terminal_from_focus();
    void time_and_date_show(int);
    void startup();
    void welcome();
    void initialising();
    void usernameinput();
    void cricket_score();
    void handle_cricket_score_results();
    void setinputareatext();
    void showmapgeolocation();
    void handle_reminder();
    void handle_reminder_timeout();
    void set_search_engine();
    void fan_speed();
    void inc_fan_speed();
    void dec_fan_speed();

private:
    Ui::Dashboard *ui;
    terminal t;
    voiceDialog *vw;
    QPoint mLastMousePosition;
    bool mMoving;
    bool window_active;
    workerThread loadthread;
    workerThread speechthread;
    workerThread fileread;
    workerThread portrunner;
    workerThread pythonserver;
    bool usernamementioned;
    bool user_welcomed;
    bool useinlinecompletion;
    char *user_name;
    QByteArray ba;
};

#endif // DASHBOARD_H
