#ifndef QCEFQUERY_H
#define QCEFQUERY_H
#pragma once

#pragma region std_headers
#include <cstdint>
#pragma endregion std_headers

#pragma region qt_headers
#include <QtCore/qglobal.h>
#include <QString>
#include <QPointer>
#include <QMetaType>
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
class QCEFVIEW_EXPORT QCefQuery
{
public:
  /// <summary>
  ///
  /// </summary>
  QCefQuery();

  /// <summary>
  ///
  /// </summary>
  /// <param name="req"></param>
  /// <param name="query"></param>
  QCefQuery(QString req, int64_t query);

  /// <summary>
  ///
  /// </summary>
  /// <param name="other"></param>
  QCefQuery(const QCefQuery& other);

  /// <summary>
  ///
  /// </summary>
  /// <param name="other"></param>
  /// <returns></returns>
  QCefQuery& operator=(const QCefQuery& other);

  /// <summary>
  ///
  /// </summary>
  ~QCefQuery();

  /// <summary>
  ///
  /// </summary>
  /// <returns></returns>
  const QString reqeust() const;

  /// <summary>
  ///
  /// </summary>
  /// <returns></returns>
  const int64_t id() const;

  /// <summary>
  ///
  /// </summary>
  /// <returns></returns>
  const QString response() const;

  /// <summary>
  ///
  /// </summary>
  /// <returns></returns>
  const bool result() const;

  /// <summary>
  ///
  /// </summary>
  /// <returns></returns>
  const int error() const;

  /// <summary>
  ///
  /// </summary>
  /// <param name="success"></param>
  /// <param name="response"></param>
  /// <param name="error"></param>
  void setResponseResult(bool success, const QString& response, int error = 0) const;

private:
  /// <summary>
  ///
  /// </summary>
  int64_t id_;

  /// <summary>
  ///
  /// </summary>
  QString reqeust_;

  /// <summary>
  ///
  /// </summary>
  mutable QString response_;

  /// <summary>
  ///
  /// </summary>
  mutable bool restult_;

  /// <summary>
  ///
  /// </summary>
  mutable int error_;

  /// <summary>
  ///
  /// </summary>
  static int TYPEID;
};
Q_DECLARE_METATYPE(QCefQuery);
#endif // QCEFQUERY_H
