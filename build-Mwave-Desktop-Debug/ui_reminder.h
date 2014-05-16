/********************************************************************************
** Form generated from reading UI file 'reminder.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMINDER_H
#define UI_REMINDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Reminder
{
public:
    QLabel *remindertitle;
    QPushButton *okbutton;

    void setupUi(QDialog *Reminder)
    {
        if (Reminder->objectName().isEmpty())
            Reminder->setObjectName(QStringLiteral("Reminder"));
        Reminder->resize(250, 150);
        remindertitle = new QLabel(Reminder);
        remindertitle->setObjectName(QStringLiteral("remindertitle"));
        remindertitle->setGeometry(QRect(0, 30, 250, 51));
        QFont font;
        font.setFamily(QStringLiteral("Segoe UI"));
        font.setPointSize(14);
        remindertitle->setFont(font);
        remindertitle->setAlignment(Qt::AlignCenter);
        okbutton = new QPushButton(Reminder);
        okbutton->setObjectName(QStringLiteral("okbutton"));
        okbutton->setGeometry(QRect(78, 105, 100, 27));

        retranslateUi(Reminder);

        QMetaObject::connectSlotsByName(Reminder);
    } // setupUi

    void retranslateUi(QDialog *Reminder)
    {
        Reminder->setWindowTitle(QApplication::translate("Reminder", "Reminder", 0));
        remindertitle->setText(QString());
        okbutton->setText(QApplication::translate("Reminder", "Ok", 0));
    } // retranslateUi

};

namespace Ui {
    class Reminder: public Ui_Reminder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMINDER_H
