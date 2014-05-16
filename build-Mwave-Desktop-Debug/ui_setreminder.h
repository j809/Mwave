/********************************************************************************
** Form generated from reading UI file 'setreminder.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETREMINDER_H
#define UI_SETREMINDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetReminder
{
public:
    QLabel *timelabel;
    QDialogButtonBox *buttonBox;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *hours;
    QLabel *hourslabel;
    QSpinBox *minutes;
    QLabel *minuteslabel;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *titlelabel;
    QLineEdit *title;

    void setupUi(QDialog *SetReminder)
    {
        if (SetReminder->objectName().isEmpty())
            SetReminder->setObjectName(QStringLiteral("SetReminder"));
        SetReminder->resize(319, 196);
        timelabel = new QLabel(SetReminder);
        timelabel->setObjectName(QStringLiteral("timelabel"));
        timelabel->setGeometry(QRect(20, 70, 191, 17));
        buttonBox = new QDialogButtonBox(SetReminder);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(80, 150, 176, 27));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        widget = new QWidget(SetReminder);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 100, 239, 29));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        hours = new QSpinBox(widget);
        hours->setObjectName(QStringLiteral("hours"));
        hours->setMaximum(23);

        horizontalLayout_2->addWidget(hours);

        hourslabel = new QLabel(widget);
        hourslabel->setObjectName(QStringLiteral("hourslabel"));

        horizontalLayout_2->addWidget(hourslabel);

        minutes = new QSpinBox(widget);
        minutes->setObjectName(QStringLiteral("minutes"));
        minutes->setMaximum(59);

        horizontalLayout_2->addWidget(minutes);

        minuteslabel = new QLabel(widget);
        minuteslabel->setObjectName(QStringLiteral("minuteslabel"));

        horizontalLayout_2->addWidget(minuteslabel);

        widget1 = new QWidget(SetReminder);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(20, 15, 262, 29));
        horizontalLayout_3 = new QHBoxLayout(widget1);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        titlelabel = new QLabel(widget1);
        titlelabel->setObjectName(QStringLiteral("titlelabel"));

        horizontalLayout_3->addWidget(titlelabel);

        title = new QLineEdit(widget1);
        title->setObjectName(QStringLiteral("title"));

        horizontalLayout_3->addWidget(title);


        retranslateUi(SetReminder);

        QMetaObject::connectSlotsByName(SetReminder);
    } // setupUi

    void retranslateUi(QDialog *SetReminder)
    {
        SetReminder->setWindowTitle(QApplication::translate("SetReminder", "Set Reminder", 0));
        timelabel->setText(QApplication::translate("SetReminder", "Set Time (24-Hour format) :", 0));
        hourslabel->setText(QApplication::translate("SetReminder", "Hours", 0));
        minuteslabel->setText(QApplication::translate("SetReminder", "Minutes", 0));
        titlelabel->setText(QApplication::translate("SetReminder", "Reminder Title :", 0));
    } // retranslateUi

};

namespace Ui {
    class SetReminder: public Ui_SetReminder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETREMINDER_H
