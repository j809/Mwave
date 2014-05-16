#include "workerthread.h"
#include <QDebug>
#include "dashboard.h"
#include "stdio.h"
#include <QAction>
#include <QApplication>

extern QString choice;
extern QString city_name;
extern QString saythis;
extern QString mode;
extern QString voiceoutput;
extern QString newsportion;
extern QString newscode;
extern bool appfocused;
extern bool enterneeded;
char tempbufpre;
char tempbuf;

workerThread::workerThread()
{
}

workerThread::~workerThread()
{
}

void workerThread::run()
{
    qDebug() << "Worker thread started.";
    if(mode=="voice")
    {
        system("python ../Mwave/Mwave_gspeech.py build > voice_data.txt");
        FILE *f;
        f=fopen("voice_data.txt","r");
        char buf[100];
        memset(buf,0,99);
        fread(buf,sizeof(char),99,f);
        voiceoutput=buf;
        voiceoutput.remove("REC: ");
        voiceoutput.remove('\n');
        qDebug() << "Voice: " << voiceoutput;
        fclose(f);
        mode="none";
    }
    else if(mode=="speech")
    {
        qDebug()<<"speaking";
        saythis.prepend("espeak -p 50 -s 170 -g 2ms \"");
        saythis.append("\"");
        system(saythis.toStdString().c_str());
        mode="none";
        saythis.clear();
    }
    else if(mode == "weather")
    {
        char buf[200];
        char *cname=(char*)calloc(100,sizeof(char));
        QByteArray ba = city_name.toLocal8Bit();
        cname=ba.data();
        sprintf(buf,"python ../Mwave/Mwave_weather.py %s build > weather_data.txt",cname);
        system(buf);
    }
    else if(mode == "news")
    {
        newscode.prepend("python ../Mwave/Mwave_newsreader.py ");
        newscode.append(" build > news_data.txt");
        system(newscode.toStdString().c_str());
        mode="none";
    }
    else if(mode == "define")
    {
        choice.remove("define ");
        choice.remove("define");
        choice.prepend("python ../Mwave/Mwave_dict_reader.py ");
        choice.append(" build > dict_data.txt");
        char *def=(char*)calloc(100,sizeof(char));
        QByteArray ba = choice.toLocal8Bit();
        def=ba.data();
        qDebug()<<def;
        system(def);
        choice = "define ";
        mode="none";
     }
    else if(mode == "cricket")
    {
        char buf[200];
        if(choice == "cricket")
            system("python ../Mwave/Mwave_cricscorereader.py build > cricket_score_data.txt");
        else
        {
            choice.remove("cricket ");
            memset(buf,0,199);
            sprintf(buf,"python ../Mwave/Mwave_cricscorereader.py %s build > cricket_score_data.txt",choice.toStdString().c_str());
            system(buf);
            mode="none";
        }
    }
    /*else if(mode == "server")
    {
        system("./Mwave_pythonserver");
    }*/
    else if(mode == "fopen")
    {
        system("sudo python ../Mwave/Mwave_portreader.py build");
    }
    else if(mode == "fread")
    {
        char buf[200];
        tempbuf=tempbufpre='N';
        while(1)
        {
            FILE *f_read;
            f_read=fopen("demo.txt","r");
            if(f_read)
            {
                fread(buf,sizeof(char),199,f_read);
                fclose(f_read);
                tempbuf=buf[0];
                if(tempbuf!=tempbufpre)
                {
                    qDebug()<<tempbufpre;
                    qDebug()<<tempbuf;
                    if(tempbufpre=='N'&&tempbuf=='R')
                    {
                        if(appfocused)
                        {
                            qDebug() << "Enter";
                            system("xte \'key Return\'");
                        }
                        else
                        {
                            system("xte \'key Right\'");
                            qDebug() << "Right";
                        }
                    }
                    else if(tempbufpre=='N'&&tempbuf=='L')
                    {
                        system("xte \'key Left\'");
                        qDebug() << "Left";
                    }
                    else if(tempbufpre=='N'&&tempbuf=='F')
                    {
                        if(appfocused && (!choice.contains("news") && !choice.startsWith("define") && choice!="help" && choice!="license" && choice!="volume" && choice!="brightness" && choice!="fan speed"))
                        {
                            system("xte \'key Page_Up\'");
                            qDebug()<<"Page UP";
                        }
                        else
                        {
                            system("xte \'key Up\'");
                            qDebug() << "Up";
                        }
                    }
                    else if(tempbufpre=='N'&&tempbuf=='B')
                    {
                        if(appfocused && (!choice.contains("news") && !choice.startsWith("define") && choice!="help" && choice!="license" && choice!="volume" && choice!="brightness" && choice!="fan speed"))
                        {
                            system("xte \'key Escape\'");
                            qDebug()<<"Esc";
                        }
                        else
                        {
                            system("xte \'key Down\'");
                            qDebug() << "Down";
                        }
                    }
                }
                tempbufpre=tempbuf;
            }
        }
    }
    qDebug() << "Worker thread terminated.";
    this->quit();
}
