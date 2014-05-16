/////////////Included Files/////////////
#include "dashboard.h"
#include "ui_dashboard.h"
#include "quitdialog.h"
#include "voicedialog.h"
#include <QDesktopWidget>
#include "terminal.h"
#include <QtGui>
#include <QCompleter>
#include "reminder.h"
#include "setreminder.h"

//////////////Variables/////////////////
extern QString choice;
extern QString saythis;
extern QString city_name;
extern QString mode;
extern QString voiceoutput;
extern QString newscode;
extern QString remind_title;
extern QTime set_time;
extern bool mute;
extern bool appfocused;
extern bool enterneeded;
QString search_engine;
QStringList newscodes;
QStringList search_engines;
QAction *enterAction;
QAction *incAction;
QAction *decAction;
QAction *escAction;
QAction *pgupAction;
QCompleter *completer;
float bright_i=1;
QTimer bulb_timer;
QTimer remind_timer;
int tickindex=1;
QString define_word;


Dashboard::Dashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);

    //////////////Inital Positon//////////////
    //setGeometry(475,500,460,95);

    QDesktopWidget* desktop = QApplication::desktop();
    QRect desk_rect = desktop->screenGeometry(desktop->screenNumber(QCursor::pos()));
    this->move(desk_rect.center() - this->rect().center());
    this->move(this->x(),this->y()+this->height());

    /////////Enter to display on textbrowser////////
    enterAction = new QAction(this);
    enterAction->setShortcut(Qt::Key_Return);
    connect(enterAction, SIGNAL(triggered()), this, SLOT(on_select()));
    addAction(enterAction);

    /////////////Esc to cancel command///////////////
    escAction = new QAction(this);
    escAction->setShortcut(Qt::Key_Escape);
    connect(escAction, SIGNAL(triggered()), this, SLOT(ask_for_input()));
    addAction(escAction);

    /////////////Increment/Decrement////////////////
    incAction = new QAction(this);
    decAction = new QAction(this);
    incAction->setShortcut(Qt::Key_Up);
    decAction->setShortcut(Qt::Key_Down);
    addAction(incAction);
    addAction(decAction);

    ////////////////Scroll Up/Down//////////////////
    connect(incAction,SIGNAL(triggered()),&t,SLOT(scrollup()));
    connect(decAction,SIGNAL(triggered()),&t,SLOT(scrolldown()));

    /////////////PG_UP[Voice Command////////////////
    pgupAction = new QAction(this);
    pgupAction->setShortcut(Qt::Key_PageUp);
    addAction(pgupAction);

    //////////////////Inital values/////////////////
    mode="keyboard";
    city_name = "none";
    window_active=false;
    mute=false;
    usernamementioned=false;
    useinlinecompletion=true;
    search_engine="google";
    srand(time(NULL));
    city_name=(char*)calloc(50,sizeof(char));

    ///////////////////////Bulb/////////////////////
    connect(&bulb_timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(&loadthread,SIGNAL(finished()),this,SLOT(load_bulb_default_image()));

    ////////////////////Reminder////////////////////
    connect(&remind_timer,SIGNAL(timeout()),this,SLOT(handle_reminder_timeout()));

    //////STEAL FOCUS TO DASHBOARD FROM TERMINAL/////
    connect(qApp,SIGNAL(focusChanged(QWidget*,QWidget*)),this,SLOT(remove_terminal_from_focus()));

    //////////CONNECT PGUP/PGDOWN TO VOICEDIALOG//////
    connect(pgupAction,SIGNAL(triggered()),this,SLOT(on_voicebutton_clicked()));

    /////////////////Auto Completer//////////////////
    QStringList wordList;
    wordList<<"weather"<<"search "<<"activate"<<"deactivate"<<"exit"<<"bye"<<"mute"<<"unmute"<<"brightness"<<"volume"<<"screen off"<<"define "<<"cricket score"<<"time"<<"date"<<"time and date"<<"completion popup"<<"completion inline"<<"yes"<<"no"<<"wakeup"<<"sleep"<<"where am i"<<"set reminder"<<"about"<<"help"<<"license"<<"licence"<<"gesture mode"<<"set search engine"<<"gmail"<<"facebook"<<"yahoo mail"<<"wikipedia"<<"quora"<<"linkedin"<<"youtube"<<"twitter"<<"lights on"<<"lights off"<<"fan on"<<"fan off"<<"fan speed";

    /////////////////News Catagories//////////////////
    newscodes<<"news"<<"headlines"<<"technology news"<<"local news"<<"world news"<<"business news"<<"entertainment news"<<"sports news"<<"science news"<<"health news"<<"stories in spotlight";

    /////////////////Search Engines///////////////////
    search_engines<<"google"<<"yahoo"<<"bing"<<"duckduckgo";

    //////////////////Auto_Completer/////////////////
    QStringList commandlist = wordList+newscodes+search_engines;
    commandlist.sort();
    completer = new QCompleter(commandlist);
    completer->setCompletionMode(QCompleter::InlineCompletion);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->inputarea->setCompleter(completer);

    /////////////Gesturemode File read/////////////////
    mode = "fopen";
    portrunner.start();
    QThread::msleep(50);
    mode = "fread";
    fileread.start();
}

Dashboard::~Dashboard()
{
    if(!mute)
    {
        mode = "speech";
        if(user_welcomed)
            saythis = "Bye"+(QString)user_name;
        else
            saythis = "Goodbye";
        speechthread.start();
    }

    fileread.terminate();
    portrunner.terminate();
    system("sudo killall -9 Mwave_portreader.py");
    delete ui;
}

void Dashboard::user_input()
{
    choice = ui->inputarea->text();
}

void Dashboard::ask_for_input()
{
    //////////////////Defaul Values///////////////////
    appfocused=true;
    t.hide_weathericon();
    city_name="none";
    loadthread.terminate();
    bulb_timer.stop();
    load_bulb_default_image();
    loadthread.disconnect();
    connect(&loadthread,SIGNAL(finished()),this,SLOT(load_bulb_default_image()));
    disconnect(incAction,SIGNAL(triggered()),this,SLOT(inc_volume()));
    disconnect(decAction,SIGNAL(triggered()),this,SLOT(dec_volume()));
    disconnect(incAction,SIGNAL(triggered()),this,SLOT(inc_bright()));
    disconnect(decAction,SIGNAL(triggered()),this,SLOT(dec_bright()));
    disconnect(incAction,SIGNAL(triggered()),this,SLOT(inc_fan_speed()));
    disconnect(decAction,SIGNAL(triggered()),this,SLOT(dec_fan_speed()));
    enterAction->disconnect();
    ui->inputarea->clear();
    mode="none";
    choice="none";

    ////////////////Asking for command////////////////
    QStringList ask;
    ask<<"What can I do for you?"<<"At your command, "+(QString)user_name<<"What to do next?"<<"Waiting for your command, "+(QString)user_name<<"What do you order me?"<<"At your service, "+(QString)user_name<<"Ready for your command, "+(QString)user_name<<"What do you request me?"<<"What is your request?";
    saythis = ask.at(rand()%ask.count());
    t.setterminaltext(saythis);
    if(!mute && usernamementioned)
    {
        mode = "speech";
        speechthread.start();
    }
    connect(enterAction,SIGNAL(triggered()),this,SLOT(on_select()));
}

void Dashboard::on_select()
{
    mode="none";
    choice="none";
    user_input();
    if(choice.toLower() == "exit" || choice == "bye")
    {
        ui->inputarea->clear();
        on_closebutton_clicked();
    }
    else if((choice.toLower() == "mute")&&!mute)
    {
        ui->inputarea->clear();
        t.on_mutebutton_clicked();
        ask_for_input();
    }
    else if((choice.toLower() == "unmute")&&mute)
    {
        ui->inputarea->clear();
        t.on_mutebutton_clicked();
        ask_for_input();
    }
    else if(choice.toLower() == "back")
    {
        ui->inputarea->clear();
        escAction->trigger();
    }
    else if(choice.toLower() == "completion inline")
    {
        ui->inputarea->clear();
        completer->setCompletionMode(QCompleter::InlineCompletion);
        useinlinecompletion=true;
    }
    else if(choice.toLower() == "completion popup")
    {
        ui->inputarea->clear();
        completer->setCompletionMode(QCompleter::PopupCompletion);
        useinlinecompletion=false;
    }

    else if(!window_active)
    {
        if(choice.toLower() == "activate" || choice.toLower() == "wakeup")
        {
            bulb_timer.stop();
            ui->inputarea->clear();

            t.show();
            QPropertyAnimation *animation = new QPropertyAnimation(&t, "pos");
            animation->setDuration(1000);
            animation->setStartValue(QPoint(t.pos().x(),t.pos().y()+650));
            animation->setEndValue(QPoint(383,86));
            animation->setEasingCurve(QEasingCurve::OutElastic);
            animation->start();
            usernamementioned=true;
            window_active=true;
            //qApp->processEvents();
            if(!mute)
            {
                mode = "speech";
                if(!user_welcomed)
                    saythis = "Activated";
                else
                {
                    saythis = "Welcome back";
                }
                speechthread.start();
            }
            ui->inputarea->setFocus();
            connect(animation,SIGNAL(finished()),this,SLOT(startup()));
        }
    }
    else if(window_active)
    {
        if(choice.toLower() == "deactivate" || choice.toLower() == "sleep")
            DeActivate();
        else if(choice.toLower() == "brightness")
        {
            ui->inputarea->clear();
            brightness();
        }
        else if(choice.toLower() == "volume")
        {
            ui->inputarea->clear();
            volume();
        }
        else if(choice.toLower() == "weather")
        {
            ui->inputarea->clear();
            weather();
        }
        else if(choice.toLower() == "screen off")
        {
            ui->inputarea->clear();;
            system("xset dpms force standby");
            ask_for_input();
        }
        else if(choice.toLower().startsWith("search "))
        {
            ui->inputarea->clear();
            choice.remove("search ");
            choice.replace(" ","+");
            if(search_engine=="google")
            {
                QDesktopServices::openUrl(QUrl("http://www.google.co.in/search?as_q="+choice));
            }
            else if(search_engine=="yahoo")
            {
                QDesktopServices::openUrl(QUrl("http://search.yahoo.com/search?p="+choice));
            }
            else if(search_engine=="bing")
            {
                QDesktopServices::openUrl(QUrl("http://www.bing.com/search?q="+choice));
            }
            else if(search_engine=="duckduckgo")
            {
                QDesktopServices::openUrl(QUrl("https://duckduckgo.com/?q="+choice));
            }
            ask_for_input();
        }
        else if(choice.toLower().startsWith("define"))
        {
            ui->inputarea->clear();
            define();
        }
        else if(newscodes.contains(choice,Qt::CaseInsensitive))
        {
            newscode=choice;
            ui->inputarea->clear();
            news();
        }
        else if(choice.toLower() == "time")
        {
            ui->inputarea->clear();
            time_and_date_show(0);
        }
        else if(choice.toLower() == "date")
        {
            ui->inputarea->clear();
            time_and_date_show(1);
        }
        else if(choice.toLower() == "time and date" || choice.toLower() == "date and time")
        {
            ui->inputarea->clear();
            time_and_date_show(2);
        }
        else if(choice.toLower() == "cricket score")
        {
            cricket_score();
        }
        else if(choice.toLower() == "set reminder")
        {
            ui->inputarea->clear();
            SetReminder sr;
            connect(&sr,SIGNAL(accepted()),this,SLOT(handle_reminder()));
            sr.exec();
        }
        else if(choice.toLower() == "help")
        {
            ui->inputarea->clear();
            FILE *f1;
            f1=fopen("../Mwave/Help.txt","r");
            char buf[1500];
            memset(buf,0,1499);
            fread(buf,sizeof(char),1499,f1);
            t.setterminaltext(buf);
            t.appendterminaltext("\nPress Enter/Esc to go back.");
            enterAction->disconnect();
            connect(enterAction,SIGNAL(triggered()),this,SLOT(ask_for_input()));
        }
        else if(choice.toLower() == "license" || choice.toLower() == "licence")
        {
            ui->inputarea->clear();
            FILE *f1;
            f1=fopen("../Mwave/LICENSE.txt","r");
            char buf[1000];
            memset(buf,0,999);
            fread(buf,sizeof(char),999,f1);
            t.setterminaltext(buf);
            t.appendterminaltext("\n\nPress Enter/Esc to go back.");
            enterAction->disconnect();
            connect(enterAction,SIGNAL(triggered()),this,SLOT(ask_for_input()));
        }
        else if(choice.toLower() == "about")
        {
            ui->inputarea->clear();
            t.setterminaltext("M-wave is a fully featured voice and gesture controlled automated assistant. It packs both hardware and software features to complete some of your routine tasks.The creators have tried their best to make the interface as much user friendly as possible. These include:\n- Google search\n- Weather report\n- Remainders\n- Dictionary\n- Daily news headlines\n- Control system volume, brightness, media controls and many more…\n- Home automation: Controlling lights, fans and other devices…\n\nPress Enter/Esc to go back.");
            enterAction->disconnect();
            connect(enterAction,SIGNAL(triggered()),this,SLOT(ask_for_input()));
        }
        else if(choice.toLower() == "set search engine")
        {
            ui->inputarea->clear();
            if(!mute)
            {
                mode="speech";
                saythis="Please select a search engine from this list";
                speechthread.start();
            }
            t.setterminaltext("The default search engine is Google.\n\nYou can select your favourite search engine from this list:\n1. Google\n2. Yahoo!\n3. Bing\n4. DuckDuckGo\n\nPlease select one from the above list.");
            enterAction->disconnect();
            connect(enterAction,SIGNAL(triggered()),this,SLOT(set_search_engine()));
        }
        else if(choice.toLower() == "gesture mode")
        {
            mode="gesture mode";
            ui->inputarea->clear();
            appfocused=false;
            t.setterminaltext("Entered geture mode...\nNow you can use gesture controller to control other programs...\n\nPress Enter/Esc to exit this mode.");
            enterAction->disconnect();
            connect(enterAction,SIGNAL(triggered()),this,SLOT(ask_for_input()));
        }
        else if(choice.toLower() == "facebook")
        {
            ui->inputarea->clear();
            QDesktopServices::openUrl(QUrl("http://www.facebook.com/"));
        }
        else if(choice.toLower() == "gmail")
        {
            ui->inputarea->clear();
            QDesktopServices::openUrl(QUrl("http://www.gmail.com/"));
        }
        else if(choice.toLower() == "yahoo mail")
        {
            ui->inputarea->clear();
            QDesktopServices::openUrl(QUrl("http://mail.yahoo.com/"));
        }
        else if(choice.toLower() == "twitter")
        {
            ui->inputarea->clear();
            QDesktopServices::openUrl(QUrl("http://www.twitter.com/"));
        }
        else if(choice.toLower() == "youtube")
        {
            ui->inputarea->clear();
            QDesktopServices::openUrl(QUrl("http://www.youtube.com/"));
        }
        else if(choice.toLower() == "linkedin")
        {
            ui->inputarea->clear();
            QDesktopServices::openUrl(QUrl("http://www.linkedin.com/"));
        }
        else if(choice.toLower() == "quora")
        {
            ui->inputarea->clear();
            QDesktopServices::openUrl(QUrl("http://www.quora.com/"));
        }
        else if(choice.toLower() == "wikipedia")
        {
            ui->inputarea->clear();
            QDesktopServices::openUrl(QUrl("http://en.wikipedia.com/"));
        }
        else if(choice.toLower() == "where am i")
        {
            ui->inputarea->clear();
            showmapgeolocation();
        }
        else if(choice.toLower() == "lights on")
        {
            ui->inputarea->clear();
            FILE *f1;
            f1=fopen("room_automation.txt","w");
            if(f1)
            {
                fprintf(f1,"a");
                fclose(f1);
            }
        }
        else if(choice.toLower() == "lights off")
        {
            ui->inputarea->clear();
            FILE *f1;
            f1=fopen("room_automation.txt","w");
            if(f1)
            {
                fprintf(f1,"b");
                fclose(f1);
            }
        }
        else if(choice.toLower() == "fan on")
        {
            ui->inputarea->clear();
            FILE *f1;
            f1=fopen("room_automation.txt","w");
            if(f1)
            {
                fprintf(f1,"c");
                fclose(f1);
            }
        }
        else if(choice.toLower() == "fan off")
        {
            ui->inputarea->clear();
            FILE *f1;
            f1=fopen("room_automation.txt","w");
            if(f1)
            {
                fprintf(f1,"d");
                fclose(f1);
            }
        }
        else if(choice.toLower() == "fan speed")
        {
            ui->inputarea->clear();
            fan_speed();
        }
    }
}

void Dashboard::fan_speed()
{
    t.setterminaltext("Use Up & Down Arrow Keys to Increase/Descrease Fan Speed\n\nUse Enter Key to Return");

    disconnect(incAction,SIGNAL(triggered()),this,SLOT(inc_fan_speed()));
    disconnect(decAction,SIGNAL(triggered()),this,SLOT(dec_fan_speed()));

    connect(incAction,SIGNAL(triggered()),this,SLOT(inc_fan_speed()));
    connect(decAction,SIGNAL(triggered()),this,SLOT(dec_fan_speed()));
    connect(enterAction,SIGNAL(triggered()),this,SLOT(ask_for_input()));
}

void Dashboard::inc_fan_speed()
{
    FILE *f1;
    f1=fopen("room_automation.txt","w");
    if(f1)
    {
        fprintf(f1,"e");
        fclose(f1);
    }
    fan_speed();
}

void Dashboard::dec_fan_speed()
{
    FILE *f1;
    f1=fopen("room_automation.txt","w");
    if(f1)
    {
        fprintf(f1,"f");
        fclose(f1);
    }
    fan_speed();
}

void Dashboard::setinputareatext()
{
    ////Writing Voice captured words on inputarea/////
    ui->inputarea->setText(voiceoutput);
    enterAction->trigger();
}

void Dashboard::showmapgeolocation()
{
    /*mode = "server";
    pythonserver.start();
    QThread::sleep(5);
    QDesktopServices::openUrl(QUrl("http://localhost:1234/../map_geo.html"));*/
    QString path = QDir::currentPath();
    //qDebug()<<"file://"+path+"../Mwave/map_geo.html";
    QDesktopServices::openUrl(QUrl("file://"+path+"/../Mwave/map_geo.html"));
}

void Dashboard::handle_reminder()
{
    ui->inputarea->clear();
    if(set_time < QTime::currentTime())
    {
        if(!mute)
        {
            mode="speech";
            saythis="Please provide a valid time";
            speechthread.start();
        }
        t.setterminaltext("Please provide a valid Time.\n\nPress Enter/Esc to go back");
        enterAction->disconnect();
        connect(enterAction,SIGNAL(triggered()),this,SLOT(ask_for_input()));
    }
    else
    {
        remind_timer.start(QTime::currentTime().msecsTo(set_time));
        if(!mute)
        {
            mode="speech";
            saythis="Your reminder is successfully setup";
            speechthread.start();
        }
        t.setterminaltext("Your Reminder has been recorded.\n\nPress Enter/Esc to go back.");
        enterAction->disconnect();
        connect(enterAction,SIGNAL(triggered()),this,SLOT(ask_for_input()));
    }
}

void Dashboard::handle_reminder_timeout()
{
    QProcess *remindsound = new QProcess(this);
    remindsound->start("play ../Mwave/sounds/reminder.ogg");
    remind_timer.stop();
    Reminder r;
    r.exec();
}

void Dashboard::set_search_engine()
{
    user_input();
    search_engine = choice;
    qDebug() << search_engine;
    if(search_engines.contains(search_engine.toLower()))
    {
        if(!mute)
        {
            mode="speech";
            saythis="Your search engine is now set to "+search_engine;
            speechthread.start();
        }
        ui->inputarea->clear();
        t.setterminaltext("Your search engine is now set to "+search_engine+".\n\nPress Enter/Esc to go back...");
        enterAction->disconnect();
        connect(enterAction,SIGNAL(triggered()),this,SLOT(ask_for_input()));
    }
}

void Dashboard::cricket_score()
{
    mode = "cricket";
    user_input();
    ui->inputarea->clear();
    t.setterminaltext("Please wait while data is fetched...");
    bulb_timer.start(200);
    if(choice.startsWith("cricket", Qt::CaseInsensitive))
        choice="cricket";
    else
        choice.prepend("cricket ");
    loadthread.start();
    connect(&loadthread,SIGNAL(finished()),this,SLOT(handle_cricket_score_results()));
}

void Dashboard::handle_cricket_score_results()
{
    disconnect(&loadthread,SIGNAL(finished()),this,SLOT(handle_cricket_score_results()));
    char buf[5000];
    memset(buf,0,4999);
    FILE *f1;
    f1=fopen("cricket_score_data.txt","r");
    int readbyte=fread(buf,sizeof(char),4999,f1);
    if(readbyte)
    {
        bulb_timer.stop();
        t.setterminaltext(buf);
        t.appendterminaltext("\nPress Esc to return...");
        enterAction->disconnect();
        if(!mute)
        {
            mode = "speech";
            if(choice.contains("cricket", Qt::CaseInsensitive))
                saythis = "Please select a match";
            else if(!strcmp(buf,"Error in fetching data!\n"))
                    saythis = "Sorry for inconvenience";
            else
                saythis = "This is the current match status.";
            speechthread.start();
            QThread::msleep(10);
        }
        if(choice.contains("cricket", Qt::CaseInsensitive))
        {
            disconnect(&loadthread,SIGNAL(finished()),this,SLOT(cricket_score()));
            connect(enterAction,SIGNAL(triggered()),this,SLOT(cricket_score()));
        }
        else
        {
            disconnect(&loadthread,SIGNAL(finished()),this,SLOT(cricket_score()));
            connect(enterAction,SIGNAL(triggered()),this,SLOT(ask_for_input()));
            choice.clear();
        }
    }
    else
    {
        if(!mute)
        {
            mode = "speech";
            saythis = "Sorry for inconvenience.";
            speechthread.start();
        }
        bulb_timer.stop();
        t.setterminaltext("Error in fetching data.\nPress Enter/Esc to go back...");
        disconnect(&loadthread,SIGNAL(finished()),this,SLOT(cricket_score()));
        connect(enterAction,SIGNAL(triggered()),this,SLOT(handle_cricket_score_results()));
        choice.clear();
    }
    mode = "none";
}

void Dashboard::startup()
{
    ui->inputarea->clear();
    if(!user_welcomed)
    {
        user_welcomed=true;
        initialising();
    }
    else
    {
        t.setterminaltext("Welcome back!");
        t.appendterminaltext("Press Enter to continue.");
        connect(enterAction,SIGNAL(triggered()),SLOT(ask_for_input()));
    }
}

void Dashboard::initialising()
{
    t.setterminaltext("");
    char str[][50]= {"Initialising M-wave...",
                     "Initialised.",
                     "Loading components...",
                     "Loaded.",
                     "Setting up UI...",
                     "UI ready.",
                     "Welcome to M-wave!"};
    QString displayed[7];
    QString curdisplay="\0";
    int k=0,j;
    for(int i=0;str[i][0]!='\0';++i)
    {
        curdisplay="\0";
        if(i==6 && !mute)
        {
            mode="speech";
            saythis="Welcome to M-wave";
            speechthread.start();
        }
        for(j=0;str[i][j]!='\0';++j)
        {
            curdisplay+=str[i][j];
            displayed[i]=curdisplay;
            if(i==0)
                t.setterminaltext((displayed[0]+char(73))); //(displayed[0]+char(127))
            else
                t.setterminaltext(displayed[0]);
            QThread::msleep(50);
            qApp->processEvents();
            for(k=1;k<=i;++k)
            {
                if(k==i)
                    t.appendterminaltext((displayed[k]+char(73)));
                else
                    t.appendterminaltext(displayed[k]);
                qApp->processEvents();
            }
        }
        if(i!=6)
            QThread::msleep(200*(i&1));
        QThread::sleep(1*(!(i&1)));
    }
    QThread::msleep(1000);
    welcome();
}

void Dashboard::welcome()
{
    t.setterminaltext("");
    QString buf;
    user_name=getenv("LOGNAME");
    if(user_name[0]>=97&&user_name[0]<=122)
        user_name[0]-=32;
    buf="Hello...\nDo you want to be called as ";
    buf.append(user_name);
    saythis=buf;
    buf.append("?(yes/no)");
    t.setterminaltext(buf);
    ui->inputarea->clear();
    if(!mute)
    {
        mode = "speech";
        saythis = "Hello! Do you want to be called as ";
        saythis.append(user_name);
        saythis.append("?");
        speechthread.start();
    }
    enterAction->disconnect();
    connect(enterAction, SIGNAL(triggered()), this, SLOT(usernameinput()));
}

void Dashboard::usernameinput()
{
    user_input();
    ui->inputarea->clear();
    char *ch;
    ch = (char *)calloc(5,sizeof(char));
    ba = choice.toLocal8Bit();
    ch = ba.data();
    if(!strcmp(ch,"no"))
    {
        ui->inputarea->clear();
        if(!mute)
        {
            mode = "speech";
            saythis="Then, what should I call you?";
            speechthread.start();
        }
        t.appendterminaltext("Then, what should I call you? : ");
        usernamementioned=true;
        enterAction->disconnect();
        connect(enterAction, SIGNAL(triggered()), this, SLOT(usernameinput()));
    }
    else if(!strcmp(ch,"yes"))
    {
        QTime  time = QTime ::currentTime();
        if((time.hour()>5)&&(time.hour()<12))
            saythis = "Good Morning... ";
        else if((time.hour()>=12)&&(time.hour()<18))
            saythis = "Good Afternoon... ";
        else if(time.hour()>=18)
            saythis = "Good Evening... ";
        else if(time.hour()<6)
            saythis = "Good Evening... ";
        saythis.append(user_name);
        usernamementioned=true;
        t.setterminaltext(saythis);
        qApp->processEvents();
        if(!mute)
        {
            mode = "speech";
            speechthread.start();
        }
        QThread::sleep(2);
        ask_for_input();
    }
    else if(usernamementioned)
    {
        ba = choice.toLocal8Bit();
        user_name = ba.data();
        if(user_name[0]>=97&&user_name[0]<=122)
            user_name[0]-=32;
        choice[0]=user_name[0];
        QTime  time = QTime ::currentTime();
        if((time.hour()>5)&&(time.hour()<12))
            saythis = "Good Morning... ";
        else if((time.hour()>=12)&&(time.hour()<18))
            saythis = "Good Afternoon... ";
        else if(time.hour()>=18)
            saythis = "Good Evening... ";
        else if(time.hour()<6)
            saythis = "Good Evening... ";
        saythis.append(choice);
        t.setterminaltext(saythis);
        qApp->processEvents();
        if(!mute)
        {
            mode = "speech";
            speechthread.start();
        }
        ui->inputarea->clear();
        QThread::sleep(3);
        ask_for_input();
    }
}

void Dashboard::time_and_date_show(int code)
{
    QTime  time = QTime ::currentTime();
    QString  timeString = time.toString("h : mm AP");
    QDate  date = QDate ::currentDate();
    QString  dateString = date.toString("dddd, d MMMM, yyyy");

    if(code == 0)               //get current time
    {
        t.setterminaltext(("Currently, time is " + timeString+"."));
        saythis="Currently, time is " + timeString;
    }
    else if(code == 1)          //get current date
    {
        t.setterminaltext(("Today is " + dateString+"."));
        saythis = "Today is " + dateString;
    }
    else if(code == 2)          //get current date and time
    {
        t.setterminaltext(("It is " + timeString + " now, and today is " + dateString + "."));
        saythis = "It is " + timeString + " now, and today is " + dateString;
    }
    if(!mute)
    {
        mode="speech";
        speechthread.start();
    }
    t.appendterminaltext("\nPress Enter to continue...");
    connect(enterAction,SIGNAL(triggered()),this,SLOT(ask_for_input()));
}

void Dashboard::weather()
{
    mode="weather";
    user_input();
    city_name=choice;
    ui->inputarea->clear();
    t.setterminaltext("Please wait while weather data is fetched...");
    bulb_timer.start(200);
    mode = "weather";
    loadthread.start();
    connect(&loadthread,SIGNAL(finished()),this,SLOT(handle_city_results()));
}

void Dashboard::handle_city_results()
{
    char buf[100];
    memset(buf, 0, 99);
    FILE *f1;
    f1=fopen("weather_data.txt","r");
    int i,readbytes;
    readbytes=fread(buf,sizeof(char),99,f1);
    for(i=0;buf[i]!='\0';++i);
    char ic_code[3];
    ic_code[0]=buf[i-3];
    ic_code[1]=buf[i-2];
    ic_code[2]='\0';
    buf[i-3]='\0';
    int icon_code = atoi(ic_code);
    if(readbytes)
    {
        if(!mute)
        {
            saythis=buf;
            saythis.replace("*C"," degree celsius");
            mode="speech";
            speechthread.start();
        }
        bulb_timer.stop();
        QString qbuf=buf;
        qbuf.replace("*C","°C");
        t.setterminaltext(qbuf);
        t.show_weathericon(icon_code);
        t.appendterminaltext("\nPress Enter to continue...");
        enterAction->disconnect();
        connect(enterAction,SIGNAL(triggered()),this,SLOT(ask_for_input()));
        disconnect(&loadthread,SIGNAL(finished()),this,SLOT(handle_city_results()));
    }
    else
    {
        if(!mute)
        {
            saythis="Cannot locate, please enter your city";
            mode="speech";
            speechthread.start();
        }
        t.hide_weathericon();
        bulb_timer.stop();
        t.setterminaltext("Cannot locate your location.\nEnter your city name...\nOr Press Esc to cancel...");
        fclose(f1);
        enterAction->disconnect();
        connect(enterAction,SIGNAL(triggered()),this,SLOT(weather()));
    }
    mode = "none";
}

void Dashboard::DeActivate()
{
    QPropertyAnimation *animation = new QPropertyAnimation(&t, "pos");
    animation->setDuration(300);
    animation->setStartValue(t.pos());
    animation->setEndValue(QPoint(t.pos().x(),t.pos().y()+700));
    animation->setEasingCurve(QEasingCurve::OutCurve);
    animation->start();
    connect(animation,SIGNAL(finished()),&t,SLOT(close()));
    usernamementioned=false;
    if(!mute)
    {
        saythis="Entering sleep mode";
        mode = "speech";
        speechthread.start();
    }
    window_active=false;
    ui->inputarea->clear();
    on_select();
}

void Dashboard::volume()
{
    t.setterminaltext("Use Up & Down Arrow Keys to Increase/Descrease Volume\n\nUse Enter Key to Return");

    disconnect(incAction,SIGNAL(triggered()),this,SLOT(inc_volume()));
    disconnect(decAction,SIGNAL(triggered()),this,SLOT(dec_volume()));

    connect(incAction,SIGNAL(triggered()),this,SLOT(inc_volume()));
    connect(decAction,SIGNAL(triggered()),this,SLOT(dec_volume()));
    connect(enterAction,SIGNAL(triggered()),this,SLOT(ask_for_input()));
}

void Dashboard::inc_volume()
{
    char buf[50];
    sprintf(buf,"amixer sset Master 10%%+");
    system(buf);
    ////////////////////////////////AUDIO////////////////////////////////
    volume();
}

void Dashboard::dec_volume()
{
    char buf[50];
    sprintf(buf,"amixer sset Master 10%%-");
    system(buf);
    volume();
}

void Dashboard::brightness()
{
    t.setterminaltext("Use Up & Down Arrow Keys to Increase/Descrease Brightness\n\nUse Enter Key to Return.");

    disconnect(incAction,SIGNAL(triggered()),this,SLOT(inc_bright()));
    disconnect(decAction,SIGNAL(triggered()),this,SLOT(dec_bright()));

    connect(incAction,SIGNAL(triggered()),this,SLOT(inc_bright()));
    connect(decAction,SIGNAL(triggered()),this,SLOT(dec_bright()));
    connect(enterAction,SIGNAL(triggered()),this,SLOT(ask_for_input()));
}

void Dashboard::inc_bright()
{
    char buf[50];
    if(bright_i<1.5)
    {
        bright_i+=0.1;
        sprintf(buf,"xrandr --output LVDS1 --brightness %.1f",bright_i);
        system(buf);
    }
    brightness();
}

void Dashboard::dec_bright()
{
    char buf[50];
    if(bright_i>0.2)
    {
        bright_i-=0.1;
        sprintf(buf,"xrandr --output LVDS1 --brightness %.1f",bright_i);
        system(buf);
    }
    brightness();
}

void Dashboard::on_closebutton_clicked()
{
    if(!mute)
    {
        mode = "speech";
        saythis = "Should I confirn Exit?";
        speechthread.start();
    }
    quitDialog diag;
    diag.exec();
}

void Dashboard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mLastMousePosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
        mMoving = true;
    }
}

void Dashboard::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && mMoving)
    {
        move(event->globalPos() - mLastMousePosition);
        mLastMousePosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void Dashboard::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = false;
    }
}

void Dashboard::closeEvent(QCloseEvent *event)
{
    event->ignore();
    quitDialog diag;
    diag.exec();
}

void Dashboard::on_voicebutton_clicked()
{
    if(this->isActiveWindow())
    {
        mode = "voice";
        vw = new voiceDialog;
        connect(&vw->voicethread,SIGNAL(finished()),this,SLOT(setinputareatext()));
        vw->exec();
    }
}

void Dashboard::tick()
{
    if(tickindex==1)
    {
        ui->bulbglow->setStyleSheet("#bulbglow{	border-image : url(:/basic/images/bulb_on.png);}");
        ++tickindex;
    }
    else if(tickindex==2)
    {
        ui->bulbglow->setStyleSheet("#bulbglow{	border-image : url(:/basic/images/bulb_red.png);}");
        ++tickindex;
    }
    else if(tickindex==3)
    {
        ui->bulbglow->setStyleSheet("#bulbglow{	border-image : url(:/basic/images/bulb_yellow.png);}");
        tickindex=1;
    }
}

void Dashboard::load_bulb_default_image()
{
    ui->bulbglow->setStyleSheet("#bulbglow{	border-image : url(:/basic/images/bulb_off.png);}");
}

void Dashboard::news()
{
    switch(newscodes.indexOf(newscode))
    {
        case 0:
        case 1: newscode.clear();
            break;
        case 2: newscode="tc";
            break;
        case 3: newscode = "n";
            break;
        case 4: newscode = "w";
            break;
        case 5: newscode = "b";
            break;
        case 6: newscode = "e";
            break;
        case 7: newscode = "s";
            break;
        case 8: newscode = "snc";
            break;
        case 9: newscode = "m";
            break;
        case 10: newscode = "ir";
            break;
        default: newscode.clear();
    }
    mode = "news";
    loadthread.start();
    bulb_timer.start(200);
    t.setterminaltext("Please wait while current news headlines are fetched...");
    connect(&loadthread,SIGNAL(finished()),this,SLOT(handle_news_results()));
}

void Dashboard::handle_news_results()
{
    FILE *f;
    f=fopen("news_data.txt","r");
    char buf[1000000];
    memset(buf,0,1000000);
    int readbytes = fread(buf,sizeof(char),999999,f);
    t.hide_weathericon();
    if(readbytes)
    {
        if(!mute)
        {
            saythis="These are the news headlines";
            mode = "speech";
            speechthread.start();
        }
        t.setterminaltext("News HeadLines\n-----------------------\n");
        t.appendterminaltext(buf);
    }
    else
        t.setterminaltext("Error in getting data!");
    t.appendterminaltext("Press Enter/Esc to continue...");
    bulb_timer.stop();
    connect(enterAction,SIGNAL(triggered()),this,SLOT(ask_for_input()));
    disconnect(&loadthread,SIGNAL(finished()),this,SLOT(handle_news_results()));
    mode = "none";
}

void Dashboard::define()
{
    mode = "define";
    choice.remove("define ");
    define_word = choice;
    choice.prepend("define ");
    bulb_timer.start(200);
    loadthread.start();
    t.setterminaltext("Please wait while word definitions are fetched...");
    connect(&loadthread,SIGNAL(finished()),this,SLOT(handle_define_results()));
}

void Dashboard::handle_define_results()
{
    choice = "define ";
    FILE *f;
    f=fopen("dict_data.txt","r");
    char buf[1000000];
    memset(buf,0,1000000);
    int readbytes = fread(buf,sizeof(char),999999,f);
    if(readbytes)
    {  
        if(!mute)
        {
            saythis="Basic definitions of "+define_word+" is ";
            mode = "speech";
            speechthread.start();
        }
        t.setterminaltext("Meaning of "+define_word);
        t.appendterminaltext("----------------------\n");
        t.appendterminaltext(buf);
    }
    else
    {
        if(!mute)
        {
            saythis="Cannot find related definitions";
            mode = "speech";
            speechthread.start();
        }
        t.setterminaltext("Cannot find definition of "+define_word+"...");
    }
    t.appendterminaltext("Press Enter/Esc to continue...");
    bulb_timer.stop();
    disconnect(&loadthread,SIGNAL(finished()),this,SLOT(handle_define_results()));
    mode = "none";
    connect(enterAction,SIGNAL(triggered()),this,SLOT(ask_for_input()));
}

void Dashboard::remove_terminal_from_focus()
{
    if(t.isActiveWindow())
    {
        this->raise();
        this->activateWindow();
        QApplication::setActiveWindow(this);
        ui->inputarea->setFocus();
    }
}
