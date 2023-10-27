/********************************************************************************
** Form generated from reading UI file 'SFTableProject.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SFTABLEPROJECT_H
#define UI_SFTABLEPROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SFTableProjectClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SFTableProjectClass)
    {
        if (SFTableProjectClass->objectName().isEmpty())
            SFTableProjectClass->setObjectName(QString::fromUtf8("SFTableProjectClass"));
        SFTableProjectClass->resize(600, 400);
        menuBar = new QMenuBar(SFTableProjectClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        SFTableProjectClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SFTableProjectClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SFTableProjectClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(SFTableProjectClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        SFTableProjectClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SFTableProjectClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SFTableProjectClass->setStatusBar(statusBar);

        retranslateUi(SFTableProjectClass);

        QMetaObject::connectSlotsByName(SFTableProjectClass);
    } // setupUi

    void retranslateUi(QMainWindow *SFTableProjectClass)
    {
        SFTableProjectClass->setWindowTitle(QApplication::translate("SFTableProjectClass", "SFTableProject", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SFTableProjectClass: public Ui_SFTableProjectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SFTABLEPROJECT_H
