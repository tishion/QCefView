#pragma region std_headers
#include <string>
#pragma endregion std_headers

#pragma region cef_headers
#include <include/cef_browser.h>
#include <include/cef_command_line.h>
#include <include/wrapper/cef_helpers.h>
#pragma endregion cef_headers

#include <QCefProtocol.h>

#include "QCefViewBrowserApp.h"

QCefViewBrowserApp::QCefViewBrowserApp(const CefString& name)
  : bridge_object_name_(name)
{}

QCefViewBrowserApp::~QCefViewBrowserApp() {}

//////////////////////////////////////////////////////////////////////////
void
QCefViewBrowserApp::OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line)
{
  command_line->AppendSwitch("disable-spell-checking");
  command_line->AppendSwitch("disable-extensions");
  command_line->AppendSwitch("disable-web-security");
  command_line->AppendSwitch("disable-pdf-extension");
  command_line->AppendSwitch("enable-direct-write");
  command_line->AppendSwitch("allow-file-access-from-files");
  command_line->AppendSwitch("no-proxy-server");
  command_line->AppendSwitch("in-process-gpu");
  command_line->AppendSwitch("disable-direct-composition");
  command_line->AppendSwitchWithValue("disable-features", "NetworkService");
  command_line->AppendSwitchWithValue("renderer-process-limit", "1");
}

void
QCefViewBrowserApp::OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar)
{
  RegisterCustomSchemes(registrar);
}

CefRefPtr<CefResourceBundleHandler>
QCefViewBrowserApp::GetResourceBundleHandler()
{
  return nullptr;
}

CefRefPtr<CefBrowserProcessHandler>
QCefViewBrowserApp::GetBrowserProcessHandler()
{
  return this;
}

CefRefPtr<CefRenderProcessHandler>
QCefViewBrowserApp::GetRenderProcessHandler()
{
  return nullptr;
}

//////////////////////////////////////////////////////////////////////////
void
QCefViewBrowserApp::OnContextInitialized()
{
  CEF_REQUIRE_UI_THREAD();

  // create all browser delegates
  CreateBrowserDelegates(browser_delegates_);

  // Register cookieable schemes with the global cookie manager.
  CefRefPtr<CefCookieManager> manager = CefCookieManager::GetGlobalManager(nullptr);
  DCHECK(manager.get());
  typedef std::vector<CefString> CookiableSchemeSet;
  CookiableSchemeSet cookieable_schemes_;
  manager->SetSupportedSchemes(cookieable_schemes_, true, nullptr);

  RegisterCustomSchemesHandlerFactories();

  BrowserDelegateSet::iterator it = browser_delegates_.begin();
  for (; it != browser_delegates_.end(); ++it)
    (*it)->OnContextInitialized(this);
}

void
QCefViewBrowserApp::OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line)
{
  if (bridge_object_name_.empty())
    bridge_object_name_ = QCEF_OBJECT_NAME;

  command_line->AppendSwitchWithValue(QCEF_BRIDGE_OBJ_NAME_KEY, bridge_object_name_);
  BrowserDelegateSet::iterator it = browser_delegates_.begin();
  for (; it != browser_delegates_.end(); ++it)
    (*it)->OnBeforeChildProcessLaunch(this, command_line);
}

void
QCefViewBrowserApp::OnRenderProcessThreadCreated(CefRefPtr<CefListValue> extra_info)
{
  CEF_REQUIRE_IO_THREAD();
  BrowserDelegateSet::iterator it = browser_delegates_.begin();
  for (; it != browser_delegates_.end(); ++it)
    (*it)->OnRenderProcessThreadCreated(this, extra_info);
}

CefRefPtr<CefPrintHandler>
QCefViewBrowserApp::GetPrintHandler()
{
  return nullptr;
}

void
QCefViewBrowserApp::OnScheduleMessagePumpWork(int64 delay_ms)
{}
