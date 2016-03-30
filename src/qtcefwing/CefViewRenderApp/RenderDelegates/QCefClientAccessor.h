#pragma once

#pragma region cef_headers
#include <include/cef_v8.h>
#pragma endregion cef_headers

class QCefClientAccessor
	: public CefV8Accessor
{
protected:
	virtual bool Get(const CefString& name,
		const CefRefPtr<CefV8Value> object,
		CefRefPtr<CefV8Value>& retval,
		CefString& exception);

	virtual bool Set(const CefString& name,
		const CefRefPtr<CefV8Value> object,
		const CefRefPtr<CefV8Value> value,
		CefString& exception);

private:
	IMPLEMENT_REFCOUNTING(QCefClientAccessor);
};

