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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QCefViewTestClass
{
public:
    QWidget *centralWidget;
    QWidget *nativeContainer;
    QVBoxLayout *verticalLayout_nativeContainer;
    QLabel *label;
    QPushButton *btn_changeColor;
    QSpacerItem *verticalSpacer;
    QWidget *cefContainer;
    QVBoxLayout *verticalLayout_cefContainer;

    void setupUi(QMainWindow *QCefViewTestClass)
    {
        if (QCefViewTestClass->objectName().isEmpty())
            QCefViewTestClass->setObjectName(QStringLiteral("QCefViewTestClass"));
        QCefViewTestClass->resize(600, 400);
        centralWidget = new QWidget(QCefViewTestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QLatin1String("#centralWidget {\n"
"background-color: rgb(0, 85, 0);\n"
"}"));
        nativeContainer = new QWidget(centralWidget);
        nativeContainer->setObjectName(QStringLiteral("nativeContainer"));
        nativeContainer->setGeometry(QRect(20, 19, 120, 361));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(nativeContainer->sizePolicy().hasHeightForWidth());
        nativeContainer->setSizePolicy(sizePolicy);
        nativeContainer->setMinimumSize(QSize(120, 0));
        nativeContainer->setMaximumSize(QSize(120, 16777215));
        nativeContainer->setStyleSheet(QLatin1String("#nativeContainer {\n"
"	background-color: rgb(170, 255, 255);\n"
"}"));
        verticalLayout_nativeContainer = new QVBoxLayout(nativeContainer);
        verticalLayout_nativeContainer->setSpacing(6);
        verticalLayout_nativeContainer->setContentsMargins(11, 11, 11, 11);
        verticalLayout_nativeContainer->setObjectName(QStringLiteral("verticalLayout_nativeContainer"));
        verticalLayout_nativeContainer->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(nativeContainer);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QLatin1String("#label{\n"
"	font: 12pt \"MS Shell Dlg 2\";\n"
"}"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_nativeContainer->addWidget(label);

        btn_changeColor = new QPushButton(nativeContainer);
        btn_changeColor->setObjectName(QStringLiteral("btn_changeColor"));

        verticalLayout_nativeContainer->addWidget(btn_changeColor);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_nativeContainer->addItem(verticalSpacer);

        cefContainer = new QWidget(centralWidget);
        cefContainer->setObjectName(QStringLiteral("cefContainer"));
        cefContainer->setGeometry(QRect(230, 20, 331, 351));
        cefContainer->setStyleSheet(QLatin1String("#cefContainer {\n"
"background-color: rgb(85, 170, 255);\n"
"}"));
        verticalLayout_cefContainer = new QVBoxLayout(cefContainer);
        verticalLayout_cefContainer->setSpacing(0);
        verticalLayout_cefContainer->setContentsMargins(11, 11, 11, 11);
        verticalLayout_cefContainer->setObjectName(QStringLiteral("verticalLayout_cefContainer"));
        verticalLayout_cefContainer->setContentsMargins(0, 0, 0, 0);
        QCefViewTestClass->setCentralWidget(centralWidget);

        retranslateUi(QCefViewTestClass);

        QMetaObject::connectSlotsByName(QCefViewTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *QCefViewTestClass)
    {
        QCefViewTestClass->setWindowTitle(QApplication::translate("QCefViewTestClass", "QCefViewTest", 0));
        label->setText(QApplication::translate("QCefViewTestClass", "Native Area", 0));
        btn_changeColor->setText(QApplication::translate("QCefViewTestClass", "ChangeColor", 0));
    } // retranslateUi

};

namespace Ui {
    class QCefViewTestClass: public Ui_QCefViewTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCEFVIEWTEST_H
