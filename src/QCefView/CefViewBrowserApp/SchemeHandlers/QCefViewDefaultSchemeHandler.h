#pragma once

#pragma region stl_headers
#include <vector>
#pragma endregion stl_headers

#pragma region cef_headers
#include <include/cef_base.h>
#pragma endregion cef_headers

class CefBrowser;
class CefSchemeRegistrar;

namespace QCefViewDefaultSchemeHandler
{
	static char* scheme_name = QCEF_SCHEMA;

	bool RegisterSchemeHandlerFactory();

	bool RegisterScheme(CefRefPtr<CefSchemeRegistrar> registrar);

	class SchemeHandler
		: public CefResourceHandler
	{
	public:
		SchemeHandler(HWND h = 0);

		virtual bool ProcessRequest(CefRefPtr<CefRequest> request, 
			CefRefPtr<CefCallback> callback);

		virtual void GetResponseHeaders(CefRefPtr<CefResponse> response, 
			int64& response_length, 
			CefString& redirectUrl);

		virtual bool ReadResponse(void* data_out, 
			int bytes_to_read, 
			int& bytes_read, 
			CefRefPtr<CefCallback> callback);

		virtual void Cancel();
				
	private:
		HWND hWnd_;
		std::string data_;
		std::string mime_type_;
		int offset_;

	private:
		IMPLEMENT_REFCOUNTING(SchemeHandler);
	};

	class SchemeHandlerFactory 
		: public CefSchemeHandlerFactory {
	 public:
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
