/********************************************************************************
** Form generated from reading UI file 'qcefviewtest.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCEFVIEWTEST_H
#define UI_QCEFVIEWTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QCefViewTestClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QCefViewTestClass)
    {
        if (QCefViewTestClass->objectName().isEmpty())
            QCefViewTestClass->setObjectName(QStringLiteral("QCefViewTestClass"));
        QCefViewTestClass->resize(600, 400);
        menuBar = new QMenuBar(QCefViewTestClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        QCefViewTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QCefViewTestClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QCefViewTestClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QCefViewTestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QCefViewTestClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QCefViewTestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QCefViewTestClass->setStatusBar(statusBar);

        retranslateUi(QCefViewTestClass);

        QMetaObject::connectSlotsByName(QCefViewTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *QCefViewTestClass)
    {
        QCefViewTestClass->setWindowTitle(QApplication::translate("QCefViewTestClass", "QCefViewTest", 0));
    } // retranslateUi

};

namespace Ui {
    class QCefViewTestClass: public Ui_QCefViewTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCEFVIEWTEST_H
