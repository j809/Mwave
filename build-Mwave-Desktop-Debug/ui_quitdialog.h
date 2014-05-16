/********************************************************************************
** Form generated from reading UI file 'quitdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUITDIALOG_H
#define UI_QUITDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_quitDialog
{
public:
    QDialogButtonBox *yesnobuttons;
    QLabel *warning;

    void setupUi(QDialog *quitDialog)
    {
        if (quitDialog->objectName().isEmpty())
            quitDialog->setObjectName(QStringLiteral("quitDialog"));
        quitDialog->resize(203, 88);
        yesnobuttons = new QDialogButtonBox(quitDialog);
        yesnobuttons->setObjectName(QStringLiteral("yesnobuttons"));
        yesnobuttons->setGeometry(QRect(12, 48, 176, 27));
        QFont font;
        font.setPointSize(11);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        yesnobuttons->setFont(font);
        yesnobuttons->setStandardButtons(QDialogButtonBox::No|QDialogButtonBox::Yes);
        yesnobuttons->setCenterButtons(false);
        warning = new QLabel(quitDialog);
        warning->setObjectName(QStringLiteral("warning"));
        warning->setGeometry(QRect(24, 12, 151, 31));
        QFont font1;
        font1.setPointSize(11);
        warning->setFont(font1);
        warning->setAlignment(Qt::AlignCenter);

        retranslateUi(quitDialog);

        QMetaObject::connectSlotsByName(quitDialog);
    } // setupUi

    void retranslateUi(QDialog *quitDialog)
    {
        quitDialog->setWindowTitle(QApplication::translate("quitDialog", "Quit", 0));
        warning->setText(QApplication::translate("quitDialog", "Are you sure to quit?", 0));
    } // retranslateUi

};

namespace Ui {
    class quitDialog: public Ui_quitDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUITDIALOG_H
