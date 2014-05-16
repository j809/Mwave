/********************************************************************************
** Form generated from reading UI file 'terminal.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TERMINAL_H
#define UI_TERMINAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_terminal
{
public:
    QWidget *terminalback;
    QTextBrowser *terminaltext;
    QWidget *weathericon;
    QPushButton *mutebutton;

    void setupUi(QWidget *terminal)
    {
        if (terminal->objectName().isEmpty())
            terminal->setObjectName(QStringLiteral("terminal"));
        terminal->resize(600, 375);
        terminal->setMouseTracking(true);
        terminal->setAutoFillBackground(false);
        terminalback = new QWidget(terminal);
        terminalback->setObjectName(QStringLiteral("terminalback"));
        terminalback->setGeometry(QRect(0, 0, 600, 375));
        terminalback->setMouseTracking(true);
        terminalback->setStyleSheet(QLatin1String("#terminalback\n"
"{\n"
"	border-image : url(:/basic/images/my_frame.png);\n"
"}"));
        terminaltext = new QTextBrowser(terminalback);
        terminaltext->setObjectName(QStringLiteral("terminaltext"));
        terminaltext->setGeometry(QRect(40, 40, 519, 289));
        QFont font;
        font.setFamily(QStringLiteral("Segoe UI"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        terminaltext->setFont(font);
        terminaltext->setMouseTracking(true);
        terminaltext->setStyleSheet(QLatin1String("#terminaltext\n"
"{\n"
"	border : none;\n"
"	background-color : rgba(255, 255, 255, 0);\n"
"   color : rgb(255, 255, 255);\n"
"}\n"
"QScrollBar:vertical\n"
"{\n"
"	background:rgba(0,0,0,0);\n"
"	width:10px;\n"
"}\n"
"QScrollBar::handle:vertical\n"
"{\n"
"	border:none;\n"
"	background-color:rgba(0,0,0,0);\n"
"}\n"
"QScrollBar::handle:vertical:hover\n"
"{\n"
"	border:1px solid black;\n"
"	border-radius:5px;\n"
"	background-color:rgba(0,0,0,120);\n"
"}\n"
"QScrollBar::handle:vertical:pressed\n"
"{\n"
"	border:1px solid black;\n"
"	border-radius:5px;\n"
"	background-color:rgba(0,0,0,120);\n"
"}\n"
"QScrollBar::add-line:vertical\n"
"{\n"
"	border:none;\n"
"	background:rgba(0,0,0,0);\n"
"}\n"
"QScrollBar::sub-line:vertical\n"
"{\n"
"	border:none;\n"
"	background:rgba(0,0,0,0);\n"
"}\n"
"QScrollBar::handle:horizontal\n"
"{\n"
"	border:none;\n"
"	background-color:rgba(0,0,0,0);\n"
"}\n"
"QScrollBar::handle:horizontal:hover\n"
"{\n"
"	border:1px solid black;\n"
"	border-radius:5px;\n"
"	background-color:rgba(0,0,0,120)"
                        ";\n"
"}\n"
"QScrollBar::handle:horizontal:pressed\n"
"{\n"
"	border:1px solid black;\n"
"	border-radius:5px;\n"
"	background-color:rgba(0,0,0,120);\n"
"}\n"
"QScrollBar::add-line:horizontal\n"
"{\n"
"	border:none;\n"
"	background:rgba(0,0,0,0);\n"
"}\n"
"QScrollBar::sub-line:horizontal\n"
"{\n"
"	border:none;\n"
"	background:rgba(0,0,0,0);\n"
"}"));
        weathericon = new QWidget(terminalback);
        weathericon->setObjectName(QStringLiteral("weathericon"));
        weathericon->setGeometry(QRect(260, 210, 96, 96));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu"));
        weathericon->setFont(font1);
        mutebutton = new QPushButton(terminalback);
        mutebutton->setObjectName(QStringLiteral("mutebutton"));
        mutebutton->setGeometry(QRect(572, 347, 10, 10));
        mutebutton->setStyleSheet(QLatin1String("#mutebutton\n"
"{\n"
"	border:none;\n"
"}\n"
"#mutebutton:hover\n"
"{\n"
"	border-image: url(:/basic/images/unmuted_pressed.png);\n"
"}"));

        retranslateUi(terminal);

        QMetaObject::connectSlotsByName(terminal);
    } // setupUi

    void retranslateUi(QWidget *terminal)
    {
        terminal->setWindowTitle(QApplication::translate("terminal", "Mwave Terminal", 0));
#ifndef QT_NO_TOOLTIP
        mutebutton->setToolTip(QApplication::translate("terminal", "Click to Mute", 0));
#endif // QT_NO_TOOLTIP
        mutebutton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class terminal: public Ui_terminal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TERMINAL_H
