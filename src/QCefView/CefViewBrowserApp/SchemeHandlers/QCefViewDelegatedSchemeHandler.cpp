#pragma region std_headers
#include <algorithm>
#include <string>
#pragma endregion std_headers

#pragma region cef_headers
#include <include/cef_browser.h>
#include <include/cef_callback.h>
#include <include/cef_frame.h>
#include <include/cef_resource_handler.h>
#include <include/cef_response.h>
#include <include/cef_request.h>
#include <include/cef_scheme.h>
#include <include/wrapper/cef_helpers.h>
#pragma endregion cef_headers

#pragma region qt_headers
#include <QString>
#pragma endregion qt_headers

#include "QCefViewDelegatedSchemeHandler.h"

namespace QCefViewDelegatedSchemeHandler {
//////////////////////////////////////////////////////////////////////////
// handler
SchemeHandler::SchemeHandler(QCefSchemeHandler* handler)
  : handler_(handler)
{}

bool
SchemeHandler::Open(CefRefPtr<CefRequest> request, bool& handle_request, CefRefPtr<CefCallback> callback)
{
  CEF_REQUIRE_IO_THREAD();

  handle_request = true;

  if (!handler_)
    return false;

  auto urlStr = QString::fromStdString(request->GetURL().ToString());

  bool result = handler_->Open(urlStr);

  return result;
}

void
SchemeHandler::GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl)
{
  CEF_REQUIRE_IO_THREAD();

  if (!handler_) {
    response_length = 0;
    response->SetStatus(500);
    return;
  }

  int statusCode;
  int contentSize;
  QString mimeType;
  handler_->GetResponseHeaders(statusCode, contentSize, mimeType);
  response_length = contentSize;
  response->SetStatus(statusCode);
  response->SetMimeType(mimeType.toStdString());
}

bool
SchemeHandler::Skip(int64 bytes_to_skip, int64& bytes_skipped, CefRefPtr<CefResourceSkipCallback> callback)
{
  bytes_skipped = -2;
  if (!handler_) {
    return false;
  } 

  const bool result = handler_->Skip(bytes_to_skip);
  if (result) {
    bytes_skipped = bytes_to_skip;
  }

  return result;
}

bool
SchemeHandler::Read(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefResourceReadCallback> callback)
{
  bytes_read = -1;
  if (!handler_) {
    return false;
  }

  QByteArray data = handler_->Read(bytes_to_read);
  bytes_read = data.length();
  if (bytes_read) {
    memcpy_s(data_out, bytes_to_read, data.constData(), bytes_read);
  }

  return bytes_read > 0;
}

void
SchemeHandler::Cancel()
{
  if (handler_) {
    handler_->Close();
  }
}

//////////////////////////////////////////////////////////////////////////
// handler factory
//

SchemeHandlerFactory::SchemeHandlerFactory(QCefSchemeHandler::SchemeHandlerCreator delegatedHandlerCreator)
  : delegatedHandlerCreator_(delegatedHandlerCreator)
{}

CefRefPtr<CefResourceHandler>
SchemeHandlerFactory::Create(CefRefPtr<CefBrowser> browser,
                             CefRefPtr<CefFrame> frame,
                             const CefString& scheme_name,
                             CefRefPtr<CefRequest> request)
{
  QCefSchemeHandler* handler = delegatedHandlerCreator_();

  if (handler)
    return new SchemeHandler(handler);
  else
    return nullptr;
}

//////////////////////////////////////////////////////////////////////////
bool
RegisterScheme(CefRawPtr<CefSchemeRegistrar> registrar, const CefString& scheme_name)
{
  return registrar->AddCustomScheme(scheme_name, 0);
}

bool
RegisterSchemeHandlerFactory(const CefString& scheme_name, QCefSchemeHandler::SchemeHandlerCreator delegatedHandlerCreator)
{
  return CefRegisterSchemeHandlerFactory(scheme_name, "", new SchemeHandlerFactory(delegatedHandlerCreator));
}
}
