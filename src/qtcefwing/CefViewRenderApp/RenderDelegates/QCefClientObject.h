#pragma once

#pragma region stl_headers
#include <unordered_map>
#pragma endregion stl_headers

#pragma region cef_headers
#include <include/cef_v8.h>
#pragma endregion cef_headers

class QCefClient
	: public CefV8Handler
	, public CefV8Accessor
{
public:
	QCefClient(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame);

	CefRefPtr<CefV8Value> self();

	void attatchToObject(CefRefPtr<CefV8Value> obj);

	void TriggerEvent(CefRefPtr<CefV8Context> context, const CefString& name, const CefV8ValueList& args);

protected:
	virtual bool Execute(const CefString& name,
		CefRefPtr<CefV8Value> object,
		const CefV8ValueList& arguments,
		CefRefPtr<CefV8Value>& retval,
		CefString& exception);

	virtual bool Get(const CefString& name,
		const CefRefPtr<CefV8Value> object,
		CefRefPtr<CefV8Value>& retval,
		CefString& exception);

	virtual bool Set(const CefString& name,
		const CefRefPtr<CefV8Value> object,
		const CefRefPtr<CefV8Value> value,
		CefString& exception);

	operator CefRefPtr<CefV8Value>();

protected:
	// self
	CefRefPtr<CefV8Value> self_;

	// properties
	static CefString versionInt_;
	static CefString versionStr_;

	// events
	std::unordered_map<std::string, CefRefPtr<CefV8Value>> eventMap_;

private:
	CefRefPtr<CefBrowser> browser_;
	CefRefPtr<CefFrame> frame_;

private:
	IMPLEMENT_REFCOUNTING(QCefClient);
};

