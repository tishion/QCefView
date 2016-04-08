#ifndef QCEFVIEWTEST_H
#define QCEFVIEWTEST_H

#include <QtWidgets/QMainWindow>
#include "ui_qcefviewtest.h"

#include <include/QCefView.h>
#include <include/QCefSetting.h>
#include <include/QCefQuery.h>

class QCefViewTest : public QMainWindow
{
	Q_OBJECT

public:
	QCefViewTest(QWidget *parent = 0);
	~QCefViewTest();

protected slots:
	void onBtnChangeColorClicked();
private:
	Ui::QCefViewTestClass ui;
	QCefView* cefview;
};

#endif // QCEFVIEWTEST_H
