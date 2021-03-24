#pragma region std_headers
#include <string>
#pragma endregion std_headers

#pragma region cef_headers
#include <include/wrapper/cef_helpers.h>
#include <include/cef_browser.h>
#include <include/cef_command_line.h>
#pragma endregion cef_headers

#pragma region project_headers
#include "QCefViewRenderApp.h"
#include "RenderDelegates/QCefViewDefaultRenderDelegate.h"
#pragma endregion project_headers

QCefViewRenderApp::QCefViewRenderApp(const CefString& name)
  : bridge_object_name_(name)
{
  CreateRenderDelegates(render_delegates_, bridge_object_name_);
}

QCefViewRenderApp::~QCefViewRenderApp() {}

void
QCefViewRenderApp::CreateRenderDelegates(RenderDelegateSet& delegates, const CefString& name)
{
  QCefViewDefaultRenderDelegate::CreateRenderDelegate(delegates, name);
}

//////////////////////////////////////////////////////////////////////////
void
QCefViewRenderApp::OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line)
{}

void
QCefViewRenderApp::OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar)
{}

CefRefPtr<CefRenderProcessHandler>
QCefViewRenderApp::GetRenderProcessHandler()
{
  return this;
}

CefRefPtr<CefResourceBundleHandler>
QCefViewRenderApp::GetResourceBundleHandler()
{
  return nullptr;
}

CefRefPtr<CefBrowserProcessHandler>
QCefViewRenderApp::GetBrowserProcessHandler()
{
  return nullptr;
}

//////////////////////////////////////////////////////////////////////////
void
QCefViewRenderApp::OnWebKitInitialized()
{
  CEF_REQUIRE_RENDERER_THREAD();

  RenderDelegateSet::iterator it = render_delegates_.begin();
  for (; it != render_delegates_.end(); ++it)
    (*it)->OnWebKitInitialized(this);
}

void
QCefViewRenderApp::OnBrowserCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDictionaryValue> extra_info)
{
  CEF_REQUIRE_RENDERER_THREAD();
  RenderDelegateSet::iterator it = render_delegates_.begin();
  for (; it != render_delegates_.end(); ++it)
    (*it)->OnBrowserCreated(this, browser, extra_info);
}

void
QCefViewRenderApp::OnBrowserDestroyed(CefRefPtr<CefBrowser> browser)
{
  CEF_REQUIRE_RENDERER_THREAD();
  RenderDelegateSet::iterator it = render_delegates_.begin();
  for (; it != render_delegates_.end(); ++it)
    (*it)->OnBrowserDestroyed(this, browser);
}

CefRefPtr<CefLoadHandler>
QCefViewRenderApp::GetLoadHandler()
{
  CefRefPtr<CefLoadHandler> load_handler;
  RenderDelegateSet::iterator it = render_delegates_.begin();
  for (; it != render_delegates_.end() && !load_handler.get(); ++it)
    load_handler = (*it)->GetLoadHandler(this);

  return load_handler;
}

void
QCefViewRenderApp::OnContextCreated(CefRefPtr<CefBrowser> browser,
                                    CefRefPtr<CefFrame> frame,
                                    CefRefPtr<CefV8Context> context)
{
  CEF_REQUIRE_RENDERER_THREAD();

  RenderDelegateSet::iterator it = render_delegates_.begin();
  for (; it != render_delegates_.end(); ++it)
    (*it)->OnContextCreated(this, browser, frame, context);
}

void
QCefViewRenderApp::OnContextReleased(CefRefPtr<CefBrowser> browser,
                                     CefRefPtr<CefFrame> frame,
                                     CefRefPtr<CefV8Context> context)
{
  CEF_REQUIRE_RENDERER_THREAD();
  RenderDelegateSet::iterator it = render_delegates_.begin();
  for (; it != render_delegates_.end(); ++it)
    (*it)->OnContextReleased(this, browser, frame, context);
}

void
QCefViewRenderApp::OnUncaughtException(CefRefPtr<CefBrowser> browser,
                                       CefRefPtr<CefFrame> frame,
                                       CefRefPtr<CefV8Context> context,
                                       CefRefPtr<CefV8Exception> exception,
                                       CefRefPtr<CefV8StackTrace> stackTrace)
{
  CEF_REQUIRE_RENDERER_THREAD();
  RenderDelegateSet::iterator it = render_delegates_.begin();
  for (; it != render_delegates_.end(); ++it)
    (*it)->OnUncaughtException(this, browser, frame, context, exception, stackTrace);
}

void
QCefViewRenderApp::OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser,
                                        CefRefPtr<CefFrame> frame,
                                        CefRefPtr<CefDOMNode> node)
{
  CEF_REQUIRE_RENDERER_THREAD();
  RenderDelegateSet::iterator it = render_delegates_.begin();
  for (; it != render_delegates_.end(); ++it)
    (*it)->OnFocusedNodeChanged(this, browser, frame, node);
}

bool
QCefViewRenderApp::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                            CefRefPtr<CefFrame> frame,
                                            CefProcessId source_process,
                                            CefRefPtr<CefProcessMessage> message)
{
  CEF_REQUIRE_RENDERER_THREAD();
  DCHECK_EQ(source_process, PID_BROWSER);

  bool handled = false;

  RenderDelegateSet::iterator it = render_delegates_.begin();
  for (; it != render_delegates_.end() && !handled; ++it)
    handled = (*it)->OnProcessMessageReceived(this, browser, frame, source_process, message);

  return handled;
}
