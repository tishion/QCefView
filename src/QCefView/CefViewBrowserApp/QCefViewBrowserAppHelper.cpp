#include "stdafx.h"

#pragma region std_headers
#include <string>
#pragma endregion std_headers

#pragma region cef_headers
#include <include/cef_browser.h>
#include <include/cef_command_line.h>
#pragma endregion cef_headers

#include "QCefViewBrowserApp.h"
#include "BrowserDelegates/QCefViewDefaultBrowserDelegate.h"
#include "SchemeHandlers/QCefViewDefaultSchemeHandler.h"


void QCefViewBrowserApp::CreateBrowserDelegates(BrowserDelegateSet& delegates)
{
	QCefViewDefaultBrowserDelegate::CreateBrowserDelegate(delegates);
	// add more browser delegates here

}

void QCefViewBrowserApp::RegisterCustomSchemesHandlerFactories()
{
	QCefViewDefaultSchemeHandler::RegisterSchemeHandlerFactory();
}

void QCefViewBrowserApp::RegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar)
{
	QCefViewDefaultSchemeHandler::RegisterScheme(registrar);
}
