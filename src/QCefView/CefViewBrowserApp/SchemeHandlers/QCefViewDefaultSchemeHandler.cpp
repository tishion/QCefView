#include "stdafx.h"
#pragma region stl_headers
#include <algorithm>
#include <string>
#pragma endregion stl_headers

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

namespace QCefViewDefaultSchemeHandler
{
	//////////////////////////////////////////////////////////////////////////
	// handler
	SchemeHandler::SchemeHandler(CCefWindow* pQCefWin)
		: pQCefWindow_(pQCefWin)
		, offset_(0)
	{
	}

	bool SchemeHandler::ProcessRequest(CefRefPtr<CefRequest> request, 
		CefRefPtr<CefCallback> callback)
	{
		CEF_REQUIRE_IO_THREAD();
		if (pQCefWindow_)
		{
			CefString cefStrUrl = request->GetURL();
			QString url = QString::fromStdString(cefStrUrl.ToString());
			pQCefWindow_->processUrlRequest(url);
		}
		// no matter whether we have found the handler or not, 
		// we don't response this request.
		return false;
	}

	void SchemeHandler::GetResponseHeaders(CefRefPtr<CefResponse> response, 
		int64& response_length, 
		CefString& redirectUrl)
	{
		CEF_REQUIRE_IO_THREAD();
		//DCHECK(!data_.empty());
		//response->SetMimeType(mime_type_);
		//response->SetStatus(200);
		//// Set the resulting response length
		//response_length = data_.length();
	}

	bool SchemeHandler::ReadResponse(void* data_out, 
		int bytes_to_read, 
		int& bytes_read, 
		CefRefPtr<CefCallback> callback)
	{
		CEF_REQUIRE_IO_THREAD();
		bool has_data = false;

		//bytes_read = 0;
		//if (offset_ < data_.length())
		//{
		//	// Copy the next block of data into the buffer.
		//	int transfer_size = min(
		//		bytes_to_read, static_cast<int>(data_.length() - offset_));
		//	memcpy(data_out, data_.c_str() + offset_, transfer_size);
		//	offset_ += transfer_size;
		//	bytes_read = transfer_size;
		//	has_data = true;
		//}

		return has_data;
	}

	bool SchemeHandler::CanGetCookie(const CefCookie& cookie)
	{
		CEF_REQUIRE_IO_THREAD();
		return true;
	}

	bool SchemeHandler::CanSetCookie(const CefCookie& cookie)
	{
		CEF_REQUIRE_IO_THREAD();
		return true;
	}

	void SchemeHandler::Cancel()
	{
		CEF_REQUIRE_IO_THREAD();
	}

	//////////////////////////////////////////////////////////////////////////
	// handler factory
	CefRefPtr<CefResourceHandler> SchemeHandlerFactory::Create(
		CefRefPtr<CefBrowser> browser, 
		CefRefPtr<CefFrame> frame, 
		const CefString& scheme_name, 
		CefRefPtr<CefRequest> request)
	{
		// 
		// TO DO (Get the correct SchemeHandler corresponding to the browser)
		// 

		return new SchemeHandler(nullptr);
	}

	//////////////////////////////////////////////////////////////////////////
	bool RegisterScheme(CefRefPtr<CefSchemeRegistrar> registrar)
	{
		return registrar->AddCustomScheme(scheme_name, false, false, false);
	}

	bool RegisterSchemeHandlerFactory()
	{
		return CefRegisterSchemeHandlerFactory(scheme_name, "", new SchemeHandlerFactory());
	}
}