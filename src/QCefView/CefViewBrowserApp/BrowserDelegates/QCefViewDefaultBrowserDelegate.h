#pragma once

#pragma region cef_headers
#include <include/wrapper/cef_message_router.h>
#pragma endregion cef_headers

#include "../QCefViewBrowserApp.h"

namespace QCefViewDefaultBrowserDelegate
{
	void CreateBrowserDelegate(QCefViewBrowserApp::BrowserDelegateSet& delegates);

	class BrowserDelegate
		: public QCefViewBrowserApp::BrowserDelegate
	{
	public:
		BrowserDelegate();

		virtual void OnContextInitialized(CefRefPtr<QCefViewBrowserApp> app);

		virtual void OnBeforeChildProcessLaunch(
			CefRefPtr<QCefViewBrowserApp> app,
			CefRefPtr<CefCommandLine> command_line);

		virtual void OnRenderProcessThreadCreated(
			CefRefPtr<QCefViewBrowserApp> app,
			CefRefPtr<CefListValue> extra_info);

	private:
		IMPLEMENT_REFCOUNTING(BrowserDelegate);
	};

}
