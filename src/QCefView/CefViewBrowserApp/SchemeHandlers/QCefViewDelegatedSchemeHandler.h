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
#include "../../Include/QCefSchemeHandler.h"

namespace QCefViewDelegatedSchemeHandler {

bool
RegisterSchemeHandlerFactory(const CefString& scheme_name, QCefSchemeHandler::SchemeHandlerCreator delegatedHandlerCreator);

bool
RegisterScheme(CefRawPtr<CefSchemeRegistrar> registrar, const CefString& scheme_name);

class SchemeHandler : public CefResourceHandler
{
public:
  SchemeHandler(QCefSchemeHandler* handler);

  virtual bool Open(CefRefPtr<CefRequest> request, bool& handle_request, CefRefPtr<CefCallback> callback) override;

  virtual void GetResponseHeaders(CefRefPtr<CefResponse> response,
                                  int64& response_length,
                                  CefString& redirectUrl) override;

  virtual bool Skip(int64 bytes_to_skip, int64& bytes_skipped, CefRefPtr<CefResourceSkipCallback> callback) override;

  virtual bool Read(void* data_out,
                    int bytes_to_read,
                    int& bytes_read,
                    CefRefPtr<CefResourceReadCallback> callback) override;

  virtual void Cancel() override;

private:
  QCefSchemeHandler* handler_;

private:
  IMPLEMENT_REFCOUNTING(SchemeHandler);
};

class SchemeHandlerFactory : public CefSchemeHandlerFactory
{

public:
  SchemeHandlerFactory(QCefSchemeHandler::SchemeHandlerCreator delegatedHandlerCreator);

  // Return a new scheme handler instance to handle the request.
  virtual CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser,
                                               CefRefPtr<CefFrame> frame,
                                               const CefString& scheme_name,
                                               CefRefPtr<CefRequest> request);

private:
  QCefSchemeHandler::SchemeHandlerCreator delegatedHandlerCreator_;

private:
  IMPLEMENT_REFCOUNTING(SchemeHandlerFactory);
};
}
