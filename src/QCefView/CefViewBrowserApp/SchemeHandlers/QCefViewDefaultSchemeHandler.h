#pragma once

#pragma region std_headers
#include <vector>
#include <map>
#include <mutex>
#pragma endregion std_headers

#pragma region cef_headers
#include <include/cef_base.h>
#include <include/cef_browser.h>
#include <include/cef_scheme.h>
#pragma endregion cef_headers

#include <QCefProtocol.h>

#include "../QCefViewDelegate.h"

namespace QCefViewDefaultSchemeHandler {
static char* scheme_name = QCEF_SCHEMA;

bool
RegisterSchemeHandlerFactory();

bool
RegisterScheme(CefRawPtr<CefSchemeRegistrar> registrar);

class SchemeHandler : public CefResourceHandler
{
public:
  SchemeHandler(QCefViewDelegate* pDelegate);

  virtual bool Open(CefRefPtr<CefRequest> request, bool& handle_request, CefRefPtr<CefCallback> callback) override;

  virtual bool ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefCallback> callback) override;

  virtual void GetResponseHeaders(CefRefPtr<CefResponse> response,
                                  int64& response_length,
                                  CefString& redirectUrl) override;

  virtual bool Skip(int64 bytes_to_skip, int64& bytes_skipped, CefRefPtr<CefResourceSkipCallback> callback) override;

  virtual bool Read(void* data_out,
                    int bytes_to_read,
                    int& bytes_read,
                    CefRefPtr<CefResourceReadCallback> callback) override;
  virtual bool ReadResponse(void* data_out,
                            int bytes_to_read,
                            int& bytes_read,
                            CefRefPtr<CefCallback> callback) override;

  virtual void Cancel() override;

private:
  QCefViewDelegate* pQCefViewDelegate_;
  std::string data_;
  std::string mime_type_;
  int offset_;

private:
  IMPLEMENT_REFCOUNTING(SchemeHandler);
};

class SchemeHandlerFactory : public CefSchemeHandlerFactory
{

public:
  /// <summary>
  ///
  /// </summary>
  /// <param name="browser"></param>
  /// <param name="pDelegate"></param>
  static void recordBrowserAndDelegate(CefRefPtr<CefBrowser> browser, QCefViewDelegate* pDelegate);

  /// <summary>
  ///
  /// </summary>
  /// <param name="browser"></param>
  static void removeBrowserAndDelegate(CefRefPtr<CefBrowser> browser);

  // Return a new scheme handler instance to handle the request.
  virtual CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser,
                                               CefRefPtr<CefFrame> frame,
                                               const CefString& scheme_name,
                                               CefRefPtr<CefRequest> request);

private:
  static std::map<int, QCefViewDelegate*> mapBrowser2Delegate_;
  static std::mutex mtxMap_;

private:
  IMPLEMENT_REFCOUNTING(SchemeHandlerFactory);
};
}
