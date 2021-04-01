#ifndef QCEFSCHEMEHANDLER_H
#define QCEFSCHEMEHANDLER_H
#pragma once

#pragma region qt_headers
#include <QtCore/qglobal.h>
#include <QBuffer>
#pragma endregion qt_headers

#ifdef QCEFVIEW_LIB
#define QCEFVIEW_EXPORT Q_DECL_EXPORT
#else
#define QCEFVIEW_EXPORT Q_DECL_IMPORT
#if _WIN32
#pragma comment(lib, "QCefView.lib")
#endif
#endif

/// <summary>
///
/// </summary>
class QCEFVIEW_EXPORT QCefSchemeHandler
{
public:
  typedef QCefSchemeHandler* (*SchemeHandlerCreator)();

  /// <summary>
  ///
  /// </summary>
  QCefSchemeHandler();

  /// <summary>
  ///
  /// </summary>
  ~QCefSchemeHandler();

  virtual bool Open(const QString& url) = 0;

  virtual void GetResponseHeaders(int& statusCode, int& contentSize, QString& mimeType) = 0;

  virtual bool Skip(const int bytesToSkip);

  virtual QByteArray Read(const int bytesToRead) = 0;

  virtual void Close();

private:

};

#endif // QCEFSCHEMEHANDLER_H
