#include <windows.h>
#include <QMessageBox>
#include <QColor>
#include <QRandomGenerator>

#include "customschemehandler.h"

QCefSchemeHandler* CustomSchemeHandler::Creator()
{
  return new CustomSchemeHandler("TESTDATA");
}

CustomSchemeHandler::CustomSchemeHandler(const QString& data)
  : data_(data.toUtf8()), done_(false)
{
}

bool
CustomSchemeHandler::Open(const QString& url)
{
  return true;
}

void
CustomSchemeHandler::GetResponseHeaders(int& statusCode, int& contentSize, QString& mimeType)
{
  statusCode = 200;
  contentSize = data_.size();
  mimeType = "text/plain";
}

QByteArray
CustomSchemeHandler::Read(const int bytesToRead)
{
  if (done_) {
    return QByteArray();
  }

  done_ = true;
  return data_;
}
