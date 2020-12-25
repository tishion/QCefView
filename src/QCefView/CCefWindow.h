#pragma once

#pragma region qt_headers
#include <QWindow>
#include <QPointer>
#include <QVariant>
#include <QHash>
#include <QMutex>
#include <QRegion>
#pragma endregion qt_headers

#pragma region cef_headers
#include <include/cef_app.h>
#pragma endregion cef_headers

#include "Include/QCefQuery.h"

/// <summary>
///
/// </summary>
class CCefWindow : public QWindow
{
  Q_OBJECT

  /// <summary>
  ///
  /// </summary>
  static QHash<CefWindowHandle, CCefWindow*> instanceMap_;

  /// <summary>
  ///
  /// </summary>
  static QMutex instanceMtx_;
  ;

public:
  /// <summary>
  ///
  /// </summary>
  static CCefWindow* lookupInstance(CefWindowHandle wnd);

public:
  /// <summary>
  ///
  /// </summary>
  /// <param name="parent"></param>
  explicit CCefWindow(QWindow* parent = 0);

  /// <summary>
  ///
  /// </summary>
  ~CCefWindow();

  /// <summary>
  ///
  /// </summary>
  /// <param name="wnd"></param>
  void setCefBrowserWindow(CefWindowHandle wnd);

signals:
  /// <summary>
  ///
  /// </summary>
  /// <param name="isLoading"></param>
  /// <param name="canGoBack"></param>
  /// <param name="canGoForward"></param>
  void loadingStateChanged(bool isLoading, bool canGoBack, bool canGoForward);

  /// <summary>
  ///
  /// </summary>
  void loadStart();

  /// <summary>
  ///
  /// </summary>
  /// <param name="httpStatusCode"></param>
  void loadEnd(int httpStatusCode);

  /// <summary>
  ///
  /// </summary>
  /// <param name="errorCode"></param>
  /// <param name="errorMsg"></param>
  /// <param name="failedUrl"></param>
  void loadError(int errorCode, const QString& errorMsg, const QString& failedUrl, bool& handled);

  /// <summary>
  ///
  /// </summary>
  /// <param name="regions"></param>
  void draggableRegionChanged(const QRegion& region);

  /// <summary>
  ///
  /// </summary>
  /// <param name="next"></param>
  void takeFocus(bool next);

  /// <summary>
  ///
  /// </summary>
  /// <param name="url"></param>
  void processUrlRequest(const QString& url);

  /// <summary>
  ///
  /// </summary>
  /// <param name="query"></param>
  void processQueryRequest(const QCefQuery& query);

  /// <summary>
  ///
  /// </summary>
  /// <param name="browserId"></param>
  /// <param name="frameId"></param>
  /// <param name="method"></param>
  /// <param name="arguments"></param>
  void invokeMethodNotify(int browserId, int frameId, const QString method, const QVariantList arguments);

public:
  /// <summary>
  ///
  /// </summary>
  void syncCefBrowserWindow();

  /// <summary>
  ///
  /// </summary>
  /// <param name="e"></param>
  virtual void exposeEvent(QExposeEvent* e);

  /// <summary>
  ///
  /// </summary>
  /// <param name="e"></param>
  virtual void resizeEvent(QResizeEvent* e);

private:
  /// <summary>
  ///
  /// </summary>
  CefWindowHandle hwndCefBrowser_;
};
