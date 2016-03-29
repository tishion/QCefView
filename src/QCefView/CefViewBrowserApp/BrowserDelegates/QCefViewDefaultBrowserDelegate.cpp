#include "stdafx.h"

#include "QCefViewDefaultBrowserDelegate.h"

namespace QCefViewDefaultBrowserDelegate
{
	void CreateBrowserDelegate(QCefViewBrowserApp::BrowserDelegateSet& delegates)
	{
		delegates.insert(new BrowserDelegate());
	}

	BrowserDelegate::BrowserDelegate()
	{

	}

	void BrowserDelegate::OnContextInitialized(CefRefPtr<QCefViewBrowserApp> app)
	{

	}

	void BrowserDelegate::OnBeforeChildProcessLaunch(CefRefPtr<QCefViewBrowserApp> app, 
		CefRefPtr<CefCommandLine> command_line)
	{

	}

	void BrowserDelegate::OnRenderProcessThreadCreated(CefRefPtr<QCefViewBrowserApp> app, 
		CefRefPtr<CefListValue> extra_info)
	{

	}

}
