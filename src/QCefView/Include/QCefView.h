#ifndef QCEFVIEW_H
#define QCEFVIEW_H
#pragma once

#pragma region std_headers
#include <memory>
#pragma endregion std_headers

#pragma region qt_headers
#include <QtCore/qglobal.h>
#include <QSemaphore>
#include <QWidget>
#include <QVariantList>
#pragma endregion qt_headers

#include "QCefQuery.h"
#include "QCefEvent.h"
#include "QCefSchemeHandler.h"

#ifdef QCEFVIEW_LIB
#define QCEFVIEW_EXPORT Q_DECL_EXPORT
#else
#define QCEFVIEW_EXPORT Q_DECL_IMPORT
#if _WIN32
#pragma comment(lib, "QCefView.lib")
#endif
#endif

/** Outline of QCefView:
 **
 **		+--------------------------------------------------------------+
 **		| QCefView(QWidget)                                            |
 **		|                                                              |
 **		|    +----------------------------------------------------+    |
 **		|    | WindowWrapper(QWidget)                             |    |
 **		|    |                                                    |    |
 **		|    |    +-------------------------------------------+   |    |
 **		|    |    | CefWindow(QWindow)                        |   |    |
 **		|    |    |                                           |   |    |
 **		|    |    |                                           |   |    |
 **		|    |    |                                           |   |    |
 **		|    |    +-------------------------------------------+   |    |
 **		|    |                                                    |    |
 **		|    +----------------------------------------------------+    |
 **		|                                                              |
 **		+--------------------------------------------------------------+
 **
 **	Remarks:
 **		The WindowWrapper and CefWindow are transparent to upper layer user.
 **
 **/

class CefContextMenuHandler;
class CefDialogHandler;
class CefDisplayHandler;
class CefDownloadHandler;
class CefJSDialogHandler;
class CefKeyboardHandler;

/// <summary>
///
/// </summary>
class QCEFVIEW_EXPORT QCefView : public QWidget
{
  /// <summary>
  ///
  /// </summary>
  Q_OBJECT
  friend class CCefWindow;

public:
  /// <summary>
  ///
  /// </summary>
  QCefView(const QString url, QWidget* parent = 0);

  /// <summary>
  ///
  /// </summary>
  QCefView(QWidget* parent = 0);

  /// <summary>
  ///
  /// </summary>
  ~QCefView();

  /// <summary>
  ///
  /// </summary>
  /// <param name="path"></param>
  /// <param name="url"></param>
  static void addLocalFolderResource(const QString& path, const QString& url, int priority = 0);

  /// <summary>
  ///
  /// </summary>
  /// <param name="path"></param>
  /// <param name="url"></param>
  /// <param name="password"></param>
  static void addArchiveResource(const QString& path, const QString& url, const QString& password = "");

  /// <summary>
  ///
  /// </summary>
  /// <param name="name"></param>
  /// <param name="value"></param>
  /// <param name="domain"></param>
  /// <param name="url"></param>
  void addCookie(const QString& name, const QString& value, const QString& domain, const QString& url);

  /// <summary>
  ///
  /// </summary>
  /// <returns></returns>
  WId getCefWinId();

  /// <summary>
  /// Navigates to the content.
  /// </summary>
  /// <param name="content"></param>
  void navigateToString(const QString& content);

  /// <summary>
  ///
  /// </summary>
  /// <param name="url"></param>
  void navigateToUrl(const QString& url);

  /// <summary>
  ///
  /// </summary>
  qreal getZoomLevel();

  /// <summary>
  ///
  /// </summary>
  /// <param name="zoomLevel"></param>
  void setZoomLevel(qreal zoomLevel);

  /// <summary>
  ///
  /// </summary>
  /// <param name="scriptSource"></param>
  void runJavaScript(const QString& scriptSource);

  /// <summary>
  ///
  /// </summary>
  void registerSchemeHandler(const QString& scheme, QCefSchemeHandler::SchemeHandlerCreator handlerCreator);

  /// <summary>
  ///
  /// </summary>
  int findText(const QString& text, bool forward = true, bool matchCase = false, int previousId = 0);

  /// <summary>
  ///
  /// </summary>
  /// <returns></returns>
  bool browserCanGoBack();

  /// <summary>
  ///
  /// </summary>
  /// <returns></returns>
  bool browserCanGoForward();

  /// <summary>
  ///
  /// </summary>
  void browserGoBack();

  /// <summary>
  ///
  /// </summary>
  void browserGoForward();

  /// <summary>
  ///
  /// </summary>
  /// <returns></returns>
  bool browserIsLoading();

  /// <summary>
  ///
  /// </summary>
  void browserReload();

  /// <summary>
  ///
  /// </summary>
  void browserStopLoad();

  /// <summary>
  ///
  /// </summary>
  /// <param name="name"></param>
  /// <param name="event"></param>
  /// <param name="frameId"></param>
  /// <returns></returns>
  bool triggerEvent(const QCefEvent& event);

  /// <summary>
  ///
  /// </summary>
  /// <param name="name"></param>
  /// <param name="event"></param>
  /// <param name="frameId"></param>
  /// <returns></returns>
  bool triggerEvent(const QCefEvent& event, int frameId);

  /// <summary>
  ///
  /// </summary>
  /// <param name="name"></param>
  /// <param name="event"></param>
  /// <returns></returns>
  bool broadcastEvent(const QCefEvent& event);

  /// <summary>
  ///
  /// </summary>
  /// <param name="query"></param>
  /// <returns></returns>
  bool responseQCefQuery(const QCefQuery& query);

  /// <summary>
  ///
  /// </summary>
  /// <param name="handler"></param>
  void setContextMenuHandler(CefContextMenuHandler* handler);

  /// <summary>
  ///
  /// </summary>
  /// <param name="handler"></param>
  void setDialogHandler(CefDialogHandler* handler);

  /// <summary>
  ///
  /// </summary>
  /// <param name="handler"></param>
  void setDisplayHandler(CefDisplayHandler* handler);

  /// <summary>
  ///
  /// </summary>
  /// <param name="handler"></param>
  void setDownloadHandler(CefDownloadHandler* handler);

  /// <summary>
  ///
  /// </summary>
  /// <param name="handler"></param>
  void setJSDialogHandler(CefJSDialogHandler* handler);

  /// <summary>
  ///
  /// </summary>
  /// <param name="handler"></param>
  void setKeyboardHandler(CefKeyboardHandler* handler);

  /// <summary>
  ///
  /// </summary>
  /// <param name="isLoading"></param>
  /// <param name="canGoBack"></param>
  /// <param name="canGoForward"></param>
  virtual void onLoadingStateChanged(bool isLoading, bool canGoBack, bool canGoForward);

  /// <summary>
  ///
  /// </summary>
  virtual void onLoadStart();

  /// <summary>
  ///
  /// </summary>
  /// <param name="httpStatusCode"></param>
  virtual void onLoadEnd(int httpStatusCode);

  /// <summary>
  ///
  /// </summary>
  /// <param name="errorCode"></param>
  /// <param name="errorMsg"></param>
  /// <param name="failedUrl"></param>
  /// <param name="handled"></param>
  virtual void onLoadError(int errorCode, const QString& errorMsg, const QString& failedUrl, bool& handled);

  /// <summary>
  ///
  /// </summary>
  /// <param name="region"></param>
  virtual void onDraggableRegionChanged(const QRegion& region);

  /// <summary>
  ///
  /// </summary>
  virtual void onAddressChange(int browserId, int frameId, const QString& url);

  /// <summary>
  ///
  /// </summary>
  virtual void onTitleChange(int browserId, const QString& title);

  /// <summary>
  ///
  /// </summary>
  /// <param name="message"></param>
  /// <param name="level"></param>
  virtual void onConsoleMessage(const QString& message, int level, const QString& source, int line);

  /// <summary>
  ///
  /// </summary>
  /// <param name="next"></param>
  virtual void onTakeFocus(bool next);

  /// <summary>
  ///
  /// </summary>
  virtual void onFindResult(int browserId, int identifier, int count, const QRect& selectionRect, int activeMatchOrdinal, bool finalUpdate);

  /// <summary>
  ///
  /// </summary>
  /// <param name="url"></param>
  virtual void onQCefUrlRequest(const QString& url);

  /// <summary>
  ///
  /// </summary>
  /// <param name="query"></param>
  virtual void onQCefQueryRequest(const QCefQuery& query);

  /// <summary>
  ///
  /// </summary>
  /// <param name="browserId"></param>
  /// <param name="frameId"></param>
  /// <param name="method"></param>
  /// <param name="arguments"></param>
  virtual void onInvokeMethodNotify(int browserId, int frameId, const QString& method, const QVariantList& arguments);

  /// <summary>
  ///
  /// </summary>
  virtual bool isInitialized(int timeout = 50);

protected:
  /// <summary>
  ///
  /// </summary>
  /// <param name="event"></param>
  virtual void changeEvent(QEvent* event) override;

  /// <summary>
  ///
  /// </summary>
  /// <param name="watched"></param>
  /// <param name="event"></param>
  /// <returns></returns>
  virtual bool eventFilter(QObject* watched, QEvent* event) override;

  /// <summary>
  ///
  /// </summary>
  /// <param name="httpStatusCode"></param>
  virtual void onLoadEndInternal(int httpStatusCode);

private:
  bool waitForInit(int timeOut = 50);

  /// <summary>
  ///
  /// </summary>
  class Implementation;
  std::unique_ptr<Implementation> pImpl_;
  QSemaphore* initSemaphore_;
};

#endif // QCEFVIEW_H
