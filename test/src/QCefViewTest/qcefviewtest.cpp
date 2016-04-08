#include "qcefviewtest.h"

#include <windows.h>

#include <QDir>
#include <QCoreApplication>
#include <QHBoxLayout>


QCefViewTest::QCefViewTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QHBoxLayout* layout = new QHBoxLayout();
	layout->setContentsMargins(2, 2, 2, 2);
	layout->setSpacing(3);

	connect(ui.btn_changeColor, SIGNAL(clicked()),
		this, SLOT(onBtnChangeColorClicked()));
	layout->addWidget(ui.nativeContainer);

	QDir dir = QCoreApplication::applicationDirPath();
	QString uri = QDir::toNativeSeparators(dir.filePath("web\\QCefViewTestPage.html"));
	cefview = new QCefView(uri, this);
	ui.cefContainer->layout()->addWidget(cefview);
	layout->addWidget(ui.cefContainer);

	centralWidget()->setLayout(layout);
}

QCefViewTest::~QCefViewTest()
{

}

void QCefViewTest::onBtnChangeColorClicked()
{
	::MessageBoxA(NULL, "HEHE", "HAHA", MB_OK);

	QVariantList args;
	args.append(QVariant::fromValue(QString("red")));
	cefview->broadcastEvent("colorChanged", args);
}
