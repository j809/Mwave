/********************************************************************************
** Form generated from reading UI file 'dashboard.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBOARD_H
#define UI_DASHBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dashboard
{
public:
    QWidget *centralWidget;
    QLineEdit *inputarea;
    QPushButton *voicebutton;
    QWidget *dashboard;
    QPushButton *closebutton;
    QLabel *bulbglow;

    void setupUi(QMainWindow *Dashboard)
    {
        if (Dashboard->objectName().isEmpty())
            Dashboard->setObjectName(QStringLiteral("Dashboard"));
        Dashboard->resize(460, 103);
        Dashboard->setMouseTracking(true);
        Dashboard->setFocusPolicy(Qt::StrongFocus);
        Dashboard->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(Dashboard);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        inputarea = new QLineEdit(centralWidget);
        inputarea->setObjectName(QStringLiteral("inputarea"));
        inputarea->setGeometry(QRect(40, 43, 380, 25));
        QFont font;
        font.setPointSize(11);
        font.setKerning(true);
        font.setStyleStrategy(QFont::PreferAntialias);
        inputarea->setFont(font);
        inputarea->setStyleSheet(QLatin1String("#inputarea\n"
"{\n"
"	border-image: url(:/basic/images/textbox.png);\n"
"}"));
        inputarea->setAlignment(Qt::AlignCenter);
        voicebutton = new QPushButton(centralWidget);
        voicebutton->setObjectName(QStringLiteral("voicebutton"));
        voicebutton->setGeometry(QRect(392, 41, 30, 30));
        voicebutton->setFocusPolicy(Qt::NoFocus);
        voicebutton->setStyleSheet(QLatin1String("QPushButton#voicebutton\n"
"{\n"
"	border-image : url(:/basic/images/voicebuttonnormal.png);\n"
"}\n"
"QPushButton#voicebutton:hover\n"
"{\n"
"	border-image : url(:/basic/images/voicebuttonhover.png);\n"
"}\n"
"QPushButton#voicebutton:pressed\n"
"{\n"
"	border-image : 	url(:/basic/images/voicebuttonpressed.png);\n"
"}"));
        dashboard = new QWidget(centralWidget);
        dashboard->setObjectName(QStringLiteral("dashboard"));
        dashboard->setGeometry(QRect(0, 9, 460, 95));
        dashboard->setStyleSheet(QLatin1String("#dashboard\n"
"{\n"
"	background-repeat : none;\n"
"	background-image : url(:/basic/images/dash.png);\n"
"}"));
        closebutton = new QPushButton(dashboard);
        closebutton->setObjectName(QStringLiteral("closebutton"));
        closebutton->setGeometry(QRect(440, 0, 19, 19));
        closebutton->setFocusPolicy(Qt::NoFocus);
        closebutton->setStyleSheet(QLatin1String("QPushButton#closebutton\n"
"{\n"
"	border : none;\n"
"}\n"
"QPushButton#closebutton:hover\n"
"{\n"
"	border-image : url(:/basic/images/closebuttonhover.png);\n"
"}\n"
"QPushButton#closebutton:pressed\n"
"{\n"
"	border-image : url(:/basic/images/closebuttonpressed.png);\n"
"}"));
        bulbglow = new QLabel(centralWidget);
        bulbglow->setObjectName(QStringLiteral("bulbglow"));
        bulbglow->setGeometry(QRect(220, 0, 40, 40));
        bulbglow->setStyleSheet(QLatin1String("#bulbglow\n"
"{\n"
"	border-image : url(:/basic/images/bulb_off.png);\n"
"}"));
        Dashboard->setCentralWidget(centralWidget);
        dashboard->raise();
        inputarea->raise();
        voicebutton->raise();
        bulbglow->raise();

        retranslateUi(Dashboard);

        QMetaObject::connectSlotsByName(Dashboard);
    } // setupUi

    void retranslateUi(QMainWindow *Dashboard)
    {
        Dashboard->setWindowTitle(QApplication::translate("Dashboard", "Mwave", 0));
#ifndef QT_NO_TOOLTIP
        voicebutton->setToolTip(QApplication::translate("Dashboard", "Give voice commands", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        voicebutton->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        voicebutton->setText(QString());
#ifndef QT_NO_WHATSTHIS
        dashboard->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        closebutton->setToolTip(QApplication::translate("Dashboard", "Exit (Alt+F4)", 0));
#endif // QT_NO_TOOLTIP
        closebutton->setText(QString());
        bulbglow->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dashboard: public Ui_Dashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARD_H
