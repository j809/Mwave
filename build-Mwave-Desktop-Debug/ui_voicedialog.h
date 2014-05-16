/********************************************************************************
** Form generated from reading UI file 'voicedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOICEDIALOG_H
#define UI_VOICEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_voiceDialog
{
public:
    QWidget *voiceback;
    QPushButton *recbutton;
    QLabel *recstatus;
    QLabel *loader;

    void setupUi(QDialog *voiceDialog)
    {
        if (voiceDialog->objectName().isEmpty())
            voiceDialog->setObjectName(QStringLiteral("voiceDialog"));
        voiceDialog->resize(284, 182);
        voiceDialog->setStyleSheet(QStringLiteral(""));
        voiceback = new QWidget(voiceDialog);
        voiceback->setObjectName(QStringLiteral("voiceback"));
        voiceback->setGeometry(QRect(0, 0, 284, 182));
        voiceback->setStyleSheet(QLatin1String("#voiceback\n"
"{\n"
"	background-repeat : none;\n"
"	background-image : url(:/basic/images/voiceback.png);\n"
"}"));
        recbutton = new QPushButton(voiceback);
        recbutton->setObjectName(QStringLiteral("recbutton"));
        recbutton->setGeometry(QRect(124, 90, 48, 48));
        recbutton->setFocusPolicy(Qt::NoFocus);
        recbutton->setStyleSheet(QLatin1String("QPushButton#recbutton\n"
"{\n"
"	border-image : url(:/basic/images/voicerecnormal.png);\n"
"}\n"
"QPushButton#recbutton:hover\n"
"{\n"
"	border-image : url(:/basic/images/voicerechover.png);\n"
"}\n"
"QPushButton#recbutton:pressed\n"
"{\n"
"	border-image : url(:/basic/images/voicerecpressed.png);\n"
"}"));
        recstatus = new QLabel(voiceback);
        recstatus->setObjectName(QStringLiteral("recstatus"));
        recstatus->setGeometry(QRect(75, 40, 141, 21));
        recstatus->setStyleSheet(QLatin1String("#recstatus\n"
"{\n"
"	color : rgb(255, 255, 255);\n"
"}"));
        recstatus->setAlignment(Qt::AlignCenter);
        loader = new QLabel(voiceback);
        loader->setObjectName(QStringLiteral("loader"));
        loader->setGeometry(QRect(112, 79, 70, 70));
        loader->raise();
        recbutton->raise();
        recstatus->raise();

        retranslateUi(voiceDialog);

        QMetaObject::connectSlotsByName(voiceDialog);
    } // setupUi

    void retranslateUi(QDialog *voiceDialog)
    {
        voiceDialog->setWindowTitle(QApplication::translate("voiceDialog", "Voice Recognition", 0));
#ifndef QT_NO_TOOLTIP
        recbutton->setToolTip(QApplication::translate("voiceDialog", "Start recording", 0));
#endif // QT_NO_TOOLTIP
        recbutton->setText(QString());
        recstatus->setText(QApplication::translate("voiceDialog", "Speak Now...", 0));
        loader->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class voiceDialog: public Ui_voiceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOICEDIALOG_H
