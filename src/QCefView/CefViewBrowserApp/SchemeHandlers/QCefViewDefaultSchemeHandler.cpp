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

#include "QCefViewDefaultSchemeHandler.h"

namespace QCefViewDefaultSchemeHandler {
//////////////////////////////////////////////////////////////////////////
// handler
SchemeHandler::SchemeHandler(QCefViewDelegate* pDelegate)
  : pQCefViewDelegate_(pDelegate)
  , offset_(0)
{}

bool
SchemeHandler::Open(CefRefPtr<CefRequest> request, bool& handle_request, CefRefPtr<CefCallback> callback)
{
  handle_request = false;
  if (pQCefViewDelegate_) {
    CefString cefStrUrl = request->GetURL();
    pQCefViewDelegate_->onQCefUrlRequest(cefStrUrl);
  }

  // no matter whether we have found the handler or not,
  // we don't response this request.
  return false;
}

bool
SchemeHandler::ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefCallback> callback)
{
  if (pQCefViewDelegate_) {
    CefString cefStrUrl = request->GetURL();
    pQCefViewDelegate_->onQCefUrlRequest(cefStrUrl);
  }

  return false;
}

void
SchemeHandler::GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl)
{
  CEF_REQUIRE_IO_THREAD();
  // DCHECK(!data_.empty());
  // response->SetMimeType(mime_type_);
  // response->SetStatus(200);
  //// Set the resulting response length
  // response_length = data_.length();
}

bool
SchemeHandler::Skip(int64 bytes_to_skip, int64& bytes_skipped, CefRefPtr<CefResourceSkipCallback> callback)
{
  bytes_skipped = -2;
  return false;
}

bool
SchemeHandler::Read(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefResourceReadCallback> callback)
{
  bytes_read = 0;
  if (offset_ < data_.length()) {
    // Copy the next block of data into the buffer.
    int transfer_size = min(bytes_to_read, static_cast<int>(data_.length() - offset_));
    memcpy(data_out, data_.c_str() + offset_, transfer_size);
    offset_ += transfer_size;
    bytes_read = transfer_size;
  }

  return bytes_read > 0;
}

bool
SchemeHandler::ReadResponse(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefCallback> callback)
{
  bytes_read = -2;
  return false;
}

void
SchemeHandler::Cancel()
{}

std::map<int, QCefViewDelegate*> SchemeHandlerFactory::mapBrowser2Delegate_;

std::mutex SchemeHandlerFactory::mtxMap_;

void
SchemeHandlerFactory::recordBrowserAndDelegate(CefRefPtr<CefBrowser> browser, QCefViewDelegate* pDelegate)
{
  if (!browser)
    return;

  std::lock_guard<std::mutex> lock(mtxMap_);
  mapBrowser2Delegate_[browser->GetIdentifier()] = pDelegate;
}

void
SchemeHandlerFactory::removeBrowserAndDelegate(CefRefPtr<CefBrowser> browser)
{
  std::lock_guard<std::mutex> lock(mtxMap_);
  if (mapBrowser2Delegate_.count(browser->GetIdentifier()))
    mapBrowser2Delegate_.erase(browser->GetIdentifier());
}

//////////////////////////////////////////////////////////////////////////
// handler factory
//

CefRefPtr<CefResourceHandler>
SchemeHandlerFactory::Create(CefRefPtr<CefBrowser> browser,
                             CefRefPtr<CefFrame> frame,
                             const CefString& scheme_name,
                             CefRefPtr<CefRequest> request)
{
  QCefViewDelegate* pDelegate = nullptr;

  {
    std::lock_guard<std::mutex> lock(mtxMap_);
    if (mapBrowser2Delegate_.count(browser->GetIdentifier()))
      pDelegate = mapBrowser2Delegate_[browser->GetIdentifier()];
  }

  if (pDelegate)
    return new SchemeHandler(pDelegate);
  else
    return nullptr;
}

//////////////////////////////////////////////////////////////////////////
bool
RegisterScheme(CefRawPtr<CefSchemeRegistrar> registrar)
{
  return registrar->AddCustomScheme(scheme_name, 0);
}

bool
RegisterSchemeHandlerFactory()
{
  return CefRegisterSchemeHandlerFactory(scheme_name, "", new SchemeHandlerFactory());
}
}
