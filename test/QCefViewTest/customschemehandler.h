#ifndef CUSTOMSCHEMEHANDLER_H
#define CUSTOMSCHEMEHANDLER_H

#include <include/QCefSchemeHandler.h>

class CustomSchemeHandler : public QCefSchemeHandler
{
public:
  static QCefSchemeHandler* Creator();

  CustomSchemeHandler(const QString& data);

  virtual bool Open(const QString& url) override;

  virtual void GetResponseHeaders(int& statusCode, int& contentSize, QString& mimeType) override;

  virtual QByteArray Read(const int bytesToRead) override;

private:
  QByteArray data_;
  bool done_;
};

#endif // CUSTOMSCHEMEHANDLER_H
