#ifndef QCEFVIEWBROWSERAPP_H_
#define QCEFVIEWBROWSERAPP_H_
#pragma once

#pragma region std_headers
#include <set>
#pragma endregion std_headers

#pragma region cef_headers
#include <include/cef_app.h>
#pragma endregion cef_headers

class QCefViewBrowserApp
  : public CefApp
  , public CefBrowserProcessHandler
{
public:
  QCefViewBrowserApp(const CefString& name);
  ~QCefViewBrowserApp();

  class BrowserDelegate : public virtual CefBaseRefCounted
  {
  public:
    virtual void OnContextInitialized(CefRefPtr<QCefViewBrowserApp> app) {}

    virtual void OnBeforeChildProcessLaunch(CefRefPtr<QCefViewBrowserApp> app, CefRefPtr<CefCommandLine> command_line)
    {}
  };
  typedef std::set<CefRefPtr<BrowserDelegate>> BrowserDelegateSet;

private:
  // Creates all of the BrowserDelegate objects. Implemented in
  // client_app_delegates.
  static void CreateBrowserDelegates(BrowserDelegateSet& delegates);

  // Rigster custom schemes handler factories
  static void RegisterCustomSchemesHandlerFactories();

  // Registers custom schemes. Implemented in client_app_delegates.
  static void RegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar);

#pragma region CefApp

  //////////////////////////////////////////////////////////////////////////
  // CefApp methods:
  virtual void OnBeforeCommandLineProcessing(const CefString& process_type,
                                             CefRefPtr<CefCommandLine> command_line) override;

  virtual void OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) override;

  virtual CefRefPtr<CefResourceBundleHandler> GetResourceBundleHandler() override;

  virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;

  virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override;

#pragma endregion CefApp

#pragma region CefBrowserProcessHandler

  // CefBrowserProcessHandler methods:
  virtual void OnContextInitialized() override;

  virtual void OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line) override;

  virtual CefRefPtr<CefPrintHandler> GetPrintHandler() override;

  virtual void OnScheduleMessagePumpWork(int64 delay_ms) override;

#pragma endregion CefBrowserProcessHandler

private:
  CefString bridge_object_name_;

  // Set of supported BrowserDelegates. Only used in the browser process.
  BrowserDelegateSet browser_delegates_;

  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(QCefViewBrowserApp);
};

#endif //  QCEFVIEWBROWSERAPP_H_
