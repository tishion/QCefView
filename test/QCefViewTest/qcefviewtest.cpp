#include "qcefviewtest.h"

#include <windows.h>

#include "Include/QCefSetting.h"
#include "customschemehandler.h"

#include <QDir>
#include <QCoreApplication>
#include <QHBoxLayout>

QCefViewTest::QCefViewTest(QWidget* parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);
  QHBoxLayout* layout = new QHBoxLayout();
  layout->setContentsMargins(2, 2, 2, 2);
  layout->setSpacing(3);

  connect(ui.btn_changeColor, SIGNAL(clicked()), this, SLOT(onBtnChangeColorClicked()));
  layout->addWidget(ui.nativeContainer);

  QCefSetting::addCustomScheme("myscheme");

  QDir dir = QCoreApplication::applicationDirPath();
  QString uri = QDir::toNativeSeparators(dir.filePath("QCefViewTestPage.html"));
  cefview = new CustomCefView(uri, this);
  // cefview = new CustomCefView("http://www.google.com/", this);
  ui.cefContainer->layout()->addWidget(cefview);
  layout->addWidget(ui.cefContainer);

  centralWidget()->setLayout(layout);
}

QCefViewTest::~QCefViewTest() {}

void
QCefViewTest::onBtnChangeColorClicked()
{
  cefview->changeColor();
}
