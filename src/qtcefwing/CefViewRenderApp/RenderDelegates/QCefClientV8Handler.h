#pragma once

#pragma region cef_headers
#include <include/cef_v8.h>
#pragma endregion cef_headers

class QCefClientV8Handler
	: public CefV8Handler
{
public:
	QCefClientV8Handler(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame);
protected:
	virtual bool Execute(const CefString& name,
		CefRefPtr<CefV8Value> object,
		const CefV8ValueList& arguments,
		CefRefPtr<CefV8Value>& retval,
		CefString& exception);

private:
	CefRefPtr<CefBrowser>	browser_;
	CefRefPtr<CefFrame>		frame_;

private:
	IMPLEMENT_REFCOUNTING(QCefClientV8Handler);
};

