#pragma once

#pragma region std_headers
#include <vector>
#pragma endregion std_headers


#pragma region qt_headers
#include <QObject>
#include <QPointer>
#pragma endregion qt_headers

#pragma region cef_headers
#include <include/cef_base.h>
#include <include/cef_browser.h>
#include <include/cef_scheme.h>
#pragma endregion cef_headers

#include "../CCefWindow.h"

namespace QCefViewDefaultSchemeHandler
{
	static char* scheme_name = QCEF_SCHEMA;

	bool RegisterSchemeHandlerFactory();

	bool RegisterScheme(CefRefPtr<CefSchemeRegistrar> registrar);

	class SchemeHandler
		: public CefResourceHandler
	{
	public:
		SchemeHandler(CCefWindow* pQCefWin);

		virtual bool ProcessRequest(CefRefPtr<CefRequest> request, 
			CefRefPtr<CefCallback> callback);

		virtual void GetResponseHeaders(CefRefPtr<CefResponse> response, 
			int64& response_length, 
			CefString& redirectUrl);

		virtual bool ReadResponse(void* data_out, 
			int bytes_to_read, 
			int& bytes_read, 
			CefRefPtr<CefCallback> callback);

		virtual bool CanGetCookie(const CefCookie& cookie);

		virtual bool CanSetCookie(const CefCookie& cookie);

		virtual void Cancel();

	private:
		QPointer<CCefWindow> pQCefWindow_;
		std::string data_;
		std::string mime_type_;
		int offset_;

	private:
		IMPLEMENT_REFCOUNTING(SchemeHandler);
	};

	class SchemeHandlerFactory 
		: public CefSchemeHandlerFactory {

	  // Return a new scheme handler instance to handle the request.
		 virtual CefRefPtr<CefResourceHandler> Create(
			 CefRefPtr<CefBrowser> browser,
			 CefRefPtr<CefFrame> frame,
			 const CefString& scheme_name,
			 CefRefPtr<CefRequest> request);

	private:
		IMPLEMENT_REFCOUNTING(SchemeHandlerFactory);
	};
}
