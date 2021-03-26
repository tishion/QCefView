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

#include <QCefProtocol.h>
#include "CefViewBrowserApp/QCefViewDelegate.h"

#include "Include/QCefQuery.h"
#include "Include/QCefView.h"

/// <summary>
///
/// </summary>
class CCefWindow
  : public QWindow
  , public QCefViewDelegate
{
  Q_OBJECT

public:
  /// <summary>
  ///
  /// </summary>

public:
  /// <summary>
  ///
  /// </summary>
  /// <param name="parent"></param>
  explicit CCefWindow(QCefView* view = 0);

  /// <summary>
  ///
  /// </summary>
  ~CCefWindow();

  virtual void setCefBrowserWindow(CefWindowHandle hwnd) override;

  virtual void onLoadingStateChanged(bool isLoading, bool canGoBack, bool canGoForward) override;

  virtual void onLoadStart() override;

  virtual void onLoadEnd(int httpStatusCode) override;

  virtual void onLoadError(int errorCode,
                           const CefString& errorMsg,
                           const CefString& failedUrl,
                           bool& handled) override;

  virtual void onDraggableRegionChanged(const std::vector<CefDraggableRegion> regions) override;

  virtual void onAddressChange(int browserId, int frameId, const CefString& url) override;

  virtual void onTakeFocus(bool next) override;

  virtual void onQCefUrlRequest(const CefString& url) override;

  virtual void onQCefQueryRequest(const CefString& request, int64 query_id) override;

  virtual void onInvokeMethodNotify(int browserId, const CefRefPtr<CefListValue>& arguments) override;

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
  QCefView* view_;

  /// <summary>
  ///
  /// </summary>
  CefWindowHandle hwndCefBrowser_;
};
