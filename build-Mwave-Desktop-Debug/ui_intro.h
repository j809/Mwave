/********************************************************************************
** Form generated from reading UI file 'intro.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTRO_H
#define UI_INTRO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Intro
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *introback;

    void setupUi(QDialog *Intro)
    {
        if (Intro->objectName().isEmpty())
            Intro->setObjectName(QStringLiteral("Intro"));
        Intro->resize(413, 147);
        Intro->setStyleSheet(QStringLiteral(""));
        horizontalLayout = new QHBoxLayout(Intro);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        introback = new QWidget(Intro);
        introback->setObjectName(QStringLiteral("introback"));
        introback->setStyleSheet(QLatin1String("#introback\n"
"{\n"
"	background-color:rgba(0,0,0,80);\n"
"	border-radius:5px;\n"
"	border-image : url(:/basic/images/logo.png);\n"
"}"));

        horizontalLayout->addWidget(introback);


        retranslateUi(Intro);

        QMetaObject::connectSlotsByName(Intro);
    } // setupUi

    void retranslateUi(QDialog *Intro)
    {
        Intro->setWindowTitle(QApplication::translate("Intro", "Intro Screen", 0));
    } // retranslateUi

};

namespace Ui {
    class Intro: public Ui_Intro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTRO_H
