#include "qcefviewtest.h"

#include <QDir>
#include <QCoreApplication>

#include <include/QCefView.h>
#include <include/QCefSetting.h>
#include <include/QCefQuery.h>

QCefViewTest::QCefViewTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QDir dir = QCoreApplication::applicationDirPath();
	QString uri = QDir::toNativeSeparators(dir.filePath("QCefViewTestPage.html"));
	//QString uri = "http://www.qt.io";

	QCefView* cefview = new QCefView(uri, this);

	setCentralWidget(cefview);
}

QCefViewTest::~QCefViewTest()
{

}
