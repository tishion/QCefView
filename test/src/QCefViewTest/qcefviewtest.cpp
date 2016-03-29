#include "qcefviewtest.h"

#include <QDir>

#include <include/QCefView.h>
#include <include/QCefSetting.h>
#include <include/QCefQuery.h>

QCefViewTest::QCefViewTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QCefView* cefview = new QCefView("http://www.qt.io/", this);
	setCentralWidget(cefview);
}

QCefViewTest::~QCefViewTest()
{

}
