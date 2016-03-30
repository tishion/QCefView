#pragma once

#pragma region cef_headers
#include <include/cef_v8.h>
#pragma endregion cef_headers

#pragma region project_headers
#include "QCefClientV8Handler.h"
#pragma endregion project_headers

class QCefClientObjectManager
	: CefBase
{
public:
	QCefClientObjectManager();
	~QCefClientObjectManager();

	virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefV8Context> context);

	virtual void OnContextReleased(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefV8Context> context);

	virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
		CefProcessId source_process,
		CefRefPtr<CefProcessMessage> message);

protected:
	void InitializeQCefClientObject(CefRefPtr<CefV8Value> obj,
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame);

	void TriggerEventMessage(CefRefPtr<CefBrowser> browser,
		const CefString& name,
		const CefV8ValueList& arguments);

private:
	IMPLEMENT_REFCOUNTING(QCefClientObjectManager);
};

