#ifndef QCEFVIEWRENDERAPP_H_
#define QCEFVIEWRENDERAPP_H_
#pragma once

#pragma region std_headers
#include <set>
#pragma endregion std_headers

#pragma region cef_headers
#include <include/cef_app.h>
#pragma endregion cef_headers

/// <summary>
///
/// </summary>
class QCefViewRenderApp
  : public CefApp
  , public CefRenderProcessHandler
{
public:
  /// <summary>
  ///
  /// </summary>
  QCefViewRenderApp(const CefString& name);

  /// <summary>
  ///
  /// </summary>
  ~QCefViewRenderApp();

  /// <summary>
  ///
  /// </summary>
  class RenderDelegate : public virtual CefBaseRefCounted
  {
  public:
    /// <summary>
    ///
    /// </summary>
    /// <param name="app"></param>
    /// <param name="extra_info"></param>
    virtual void OnRenderThreadCreated(CefRefPtr<QCefViewRenderApp> app, CefRefPtr<CefListValue> extra_info) {}

    /// <summary>
    ///
    /// </summary>
    /// <param name="app"></param>
    virtual void OnWebKitInitialized(CefRefPtr<QCefViewRenderApp> app) {}

    /// <summary>
    ///
    /// </summary>
    /// <param name="app"></param>
    /// <param name="browser"></param>
    virtual void OnBrowserCreated(CefRefPtr<QCefViewRenderApp> app,
                                  CefRefPtr<CefBrowser> browser,
                                  CefRefPtr<CefDictionaryValue> extra_info)
    {}

    /// <summary>
    ///
    /// </summary>
    /// <param name="app"></param>
    /// <param name="browser"></param>
    virtual void OnBrowserDestroyed(CefRefPtr<QCefViewRenderApp> app, CefRefPtr<CefBrowser> browser) {}

    /// <summary>
    ///
    /// </summary>
    /// <param name="app"></param>
    /// <returns></returns>
    virtual CefRefPtr<CefLoadHandler> GetLoadHandler(CefRefPtr<QCefViewRenderApp> app) { return nullptr; }

    /// <summary>
    ///
    /// </summary>
    /// <param name="app"></param>
    /// <param name="browser"></param>
    /// <param name="frame"></param>
    /// <param name="context"></param>
    virtual void OnContextCreated(CefRefPtr<QCefViewRenderApp> app,
                                  CefRefPtr<CefBrowser> browser,
                                  CefRefPtr<CefFrame> frame,
                                  CefRefPtr<CefV8Context> context)
    {}

    /// <summary>
    ///
    /// </summary>
    /// <param name="app"></param>
    /// <param name="browser"></param>
    /// <param name="frame"></param>
    /// <param name="context"></param>
    virtual void OnContextReleased(CefRefPtr<QCefViewRenderApp> app,
                                   CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   CefRefPtr<CefV8Context> context)
    {}

    /// <summary>
    ///
    /// </summary>
    /// <param name="app"></param>
    /// <param name="browser"></param>
    /// <param name="frame"></param>
    /// <param name="context"></param>
    /// <param name="exception"></param>
    /// <param name="stackTrace"></param>
    virtual void OnUncaughtException(CefRefPtr<QCefViewRenderApp> app,
                                     CefRefPtr<CefBrowser> browser,
                                     CefRefPtr<CefFrame> frame,
                                     CefRefPtr<CefV8Context> context,
                                     CefRefPtr<CefV8Exception> exception,
                                     CefRefPtr<CefV8StackTrace> stackTrace)
    {}

    /// <summary>
    ///
    /// </summary>
    /// <param name="app"></param>
    /// <param name="browser"></param>
    /// <param name="frame"></param>
    /// <param name="node"></param>
    virtual void OnFocusedNodeChanged(CefRefPtr<QCefViewRenderApp> app,
                                      CefRefPtr<CefBrowser> browser,
                                      CefRefPtr<CefFrame> frame,
                                      CefRefPtr<CefDOMNode> node)
    {}

    // Called when a process message is received. Return true if the message was
    // handled and should not be passed on to other handlers. RenderDelegates
    // should check for unique message names to avoid interfering with each
    // other.
    /// <summary>
    ///
    /// </summary>
    /// <param name="app"></param>
    /// <param name="browser"></param>
    /// <param name="source_process"></param>
    /// <param name="message"></param>
    /// <returns></returns>
    virtual bool OnProcessMessageReceived(CefRefPtr<QCefViewRenderApp> app,
                                          CefRefPtr<CefBrowser> browser,
                                          CefRefPtr<CefFrame> frame,
                                          CefProcessId source_process,
                                          CefRefPtr<CefProcessMessage> message)
    {
      return false;
    }
  };

  /// <summary>
  ///
  /// </summary>
  typedef std::set<CefRefPtr<RenderDelegate>> RenderDelegateSet;

private:
  // Creates all of the RenderDelegate objects. Implemented in
  // client_app_delegates.
  /// <summary>
  ///
  /// </summary>
  /// <param name="delegates"></param>
  static void CreateRenderDelegates(RenderDelegateSet& delegates, const CefString& name);

#pragma region CefApp

  //////////////////////////////////////////////////////////////////////////
  // CefApp methods:
  /// <summary>
  ///
  /// </summary>
  /// <param name="process_type"></param>
  /// <param name="command_line"></param>
  virtual void OnBeforeCommandLineProcessing(const CefString& process_type,
                                             CefRefPtr<CefCommandLine> command_line) override;

  /// <summary>
  ///
  /// </summary>
  /// <param name="registrar"></param>
  virtual void OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) override;

  /// <summary>
  ///
  /// </summary>
  /// <returns></returns>
  virtual CefRefPtr<CefResourceBundleHandler> GetResourceBundleHandler() override;

  /// <summary>
  ///
  /// </summary>
  /// <returns></returns>
  virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;

  /// <summary>
  ///
  /// </summary>
  /// <returns></returns>
  virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override;

#pragma endregion CefApp

#pragma region CefRenderProcessHandler

  /// <summary>
  ///
  /// </summary>
  virtual void OnWebKitInitialized() override;

  /// <summary>
  ///
  /// </summary>
  /// <param name="browser"></param>
  /// <param name="extra_info"></param>
  virtual void OnBrowserCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDictionaryValue> extra_info) override;

  /// <summary>
  ///
  /// </summary>
  /// <param name="browser"></param>
  virtual void OnBrowserDestroyed(CefRefPtr<CefBrowser> browser) override;

  /// <summary>
  ///
  /// </summary>
  /// <returns></returns>
  virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override;

  /// <summary>
  ///
  /// </summary>
  /// <param name="browser"></param>
  /// <param name="frame"></param>
  /// <param name="context"></param>
  virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                CefRefPtr<CefV8Context> context) override;

  /// <summary>
  ///
  /// </summary>
  /// <param name="browser"></param>
  /// <param name="frame"></param>
  /// <param name="context"></param>
  virtual void OnContextReleased(CefRefPtr<CefBrowser> browser,
                                 CefRefPtr<CefFrame> frame,
                                 CefRefPtr<CefV8Context> context) override;

  /// <summary>
  ///
  /// </summary>
  /// <param name="browser"></param>
  /// <param name="frame"></param>
  /// <param name="context"></param>
  /// <param name="exception"></param>
  /// <param name="stackTrace"></param>
  virtual void OnUncaughtException(CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   CefRefPtr<CefV8Context> context,
                                   CefRefPtr<CefV8Exception> exception,
                                   CefRefPtr<CefV8StackTrace> stackTrace) override;

  /// <summary>
  ///
  /// </summary>
  /// <param name="browser"></param>
  /// <param name="frame"></param>
  /// <param name="node"></param>
  virtual void OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser,
                                    CefRefPtr<CefFrame> frame,
                                    CefRefPtr<CefDOMNode> node) override;

  /// <summary>
  ///
  /// </summary>
  /// <param name="browser"></param>
  /// <param name="frame"></param>
  /// <param name="source_process"></param>
  /// <param name="message"></param>
  /// <returns></returns>
  virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                        CefRefPtr<CefFrame> frame,
                                        CefProcessId source_process,
                                        CefRefPtr<CefProcessMessage> message) override;

#pragma endregion CefRenderProcessHandler

private:
  /// <summary>
  ///
  /// </summary>
  CefString bridge_object_name_;

  // Set of supported RenderDelegates. Only used in the renderer process.
  /// <summary>
  ///
  /// </summary>
  RenderDelegateSet render_delegates_;

  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(QCefViewRenderApp);
};

#endif // QCEFVIEWRENDERAPP_H_
