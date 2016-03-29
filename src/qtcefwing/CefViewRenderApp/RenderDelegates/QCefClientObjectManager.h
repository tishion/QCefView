#pragma once

#pragma region cef_headers
#include <include/cef_v8.h>
#pragma endregion cef_headers

#pragma region project_headers
#include "QCefClientObject.h"
#pragma endregion project_headers

class QCefClientObjectManager
	: CefBase
{
	typedef std::pair<CefRefPtr<CefFrame>, CefRefPtr<QCefClient>> FrameGxxClient;
	typedef std::map<int64, FrameGxxClient> FrameMap;
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

private:
	FrameMap frame_map_;

private:
	IMPLEMENT_REFCOUNTING(QCefClientObjectManager);
};

