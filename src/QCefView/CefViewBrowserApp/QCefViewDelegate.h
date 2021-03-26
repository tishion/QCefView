#ifndef QCEFVIEWDELEGATE_H_
#define QCEFVIEWDELEGATE_H_
#pragma once

#pragma region cef_headers
#include <include/cef_client.h>
#pragma endregion cef_headers

class QCefViewDelegate
{
public:
  virtual ~QCefViewDelegate(){};

  virtual void setCefBrowserWindow(CefWindowHandle hwnd) = 0;

  virtual void onLoadingStateChanged(bool isLoading, bool canGoBack, bool canGoForward) = 0;

  virtual void onLoadStart() = 0;

  virtual void onLoadEnd(int httpStatusCode) = 0;

  virtual void onLoadError(int errorCode, const CefString& errorMsg, const CefString& failedUrl, bool& handled) = 0;

  virtual void onDraggableRegionChanged(const std::vector<CefDraggableRegion> regions) = 0;

  virtual void onAddressChange(int browserId, int frameId, const CefString& url) = 0;

  virtual void onTitleChange(int browserId, const CefString& title) = 0;

  virtual void onConsoleMessage(const CefString& message, int level, const CefString& source, int line) = 0;

  virtual void onTakeFocus(bool next) = 0;

  virtual void onQCefUrlRequest(const CefString& url) = 0;

  virtual void onQCefQueryRequest(const CefString& request, int64 query_id) = 0;

  virtual void onInvokeMethodNotify(int browserId, const CefRefPtr<CefListValue>& arguments) = 0;
};

#endif
