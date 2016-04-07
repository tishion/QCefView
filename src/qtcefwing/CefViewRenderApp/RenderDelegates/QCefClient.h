#pragma once

#pragma region cef_headers
#include <include/cef_v8.h>
#pragma endregion cef_headers

class QCefClient
	: public CefBase
{
	class Accessor
		: public CefV8Accessor
	{
	public:
		virtual bool Get(const CefString& name, 
			const CefRefPtr<CefV8Value> object, 
			CefRefPtr<CefV8Value>& retval, 
			CefString& exception) override;

		virtual bool Set(const CefString& name, 
			const CefRefPtr<CefV8Value> object, 
			const CefRefPtr<CefV8Value> value, 
			CefString& exception) override;

	private:
		IMPLEMENT_REFCOUNTING(Accessor);
	};

	typedef std::map<CefString, CefRefPtr<CefV8Handler>> EventHandlerMap;

	class V8Handler
		: public CefV8Handler
	{
	public:
		V8Handler(CefRefPtr<CefBrowser> browser, 
			CefRefPtr<CefFrame> frame,
			QCefClient::EventHandlerMap& eventHandlerMap);
		virtual bool Execute(const CefString& function, 
			CefRefPtr<CefV8Value> object, 
			const CefV8ValueList& arguments, 
			CefRefPtr<CefV8Value>& retval, 
			CefString& exception) override;

	protected:
		void ExecuteInvokeMethod(const CefString& function, 
			CefRefPtr<CefV8Value> object, 
			const CefV8ValueList& arguments, 
			CefRefPtr<CefV8Value>& retval, 
			CefString& exception);
		void ExecuteRegisterEventHandler(const CefString& function,
			CefRefPtr<CefV8Value> object, 
			const CefV8ValueList& arguments, 
			CefRefPtr<CefV8Value>& retval, 
			CefString& exception);
		void ExecuteUnregisterEventHandler(const CefString& function,
			CefRefPtr<CefV8Value> object,
			const CefV8ValueList& arguments,
			CefRefPtr<CefV8Value>& retval,
			CefString& exception);

	private:
		CefRefPtr<CefBrowser>	browser_;
		CefRefPtr<CefFrame>		frame_;
		QCefClient::EventHandlerMap& eventHandlerMap_;

	private:
		IMPLEMENT_REFCOUNTING(V8Handler);
	};


public:
	QCefClient(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame);

	 CefRefPtr<CefV8Value> GetObject();

	 bool ExecuteEventHandler(CefString eventName);

private:
	CefRefPtr<CefV8Value>	object_;
	CefRefPtr<CefBrowser>	browser_;
	CefRefPtr<CefFrame>		frame_;
	EventHandlerMap			eventHandlerMap_;

private:
	IMPLEMENT_REFCOUNTING(QCefClient);
};
