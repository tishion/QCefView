#pragma once
#pragma region std_headers
#include <unordered_map>
#pragma endregion

#pragma region cef_headers
#include <include/wrapper/cef_message_router.h>
#pragma endregion cef_headers

#pragma region project_headers
#include "../QCefViewRenderApp.h"
#include "QCefClient.h"
#pragma endregion project_headers

namespace QCefViewDefaultRenderDelegate {
/// <summary>
///
/// </summary>
void
CreateBrowserDelegate(QCefViewRenderApp::RenderDelegateSet& delegates);

/// <summary>
///
/// </summary>
class RenderDelegate : public QCefViewRenderApp::RenderDelegate
{
  /// <summary>
  ///
  /// </summary>
  typedef std::unordered_map<int64, CefRefPtr<QCefClient>> FrameID2QCefClientMap;

public:
  /// <summary>
  ///
  /// </summary>
  RenderDelegate();

  /// <summary>
  ///
  /// </summary>
  /// <param name="app"></param>
  virtual void OnWebKitInitialized(CefRefPtr<QCefViewRenderApp> app);

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
                                CefRefPtr<CefV8Context> context);

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
                                 CefRefPtr<CefV8Context> context);

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
                                        CefRefPtr<CefProcessMessage> message);

protected:
  /// <summary>
  ///
  /// </summary>
  /// <param name="browser"></param>
  /// <param name="frame"></param>
  /// <param name="source_process"></param>
  /// <param name="message"></param>
  /// <returns></returns>
  bool OnTriggerEventNotifyMessage(CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   CefProcessId source_process,
                                   CefRefPtr<CefProcessMessage> message);

  /// <summary>
  ///
  /// </summary>
  /// <param name="browser"></param>
  /// <param name="frame"></param>
  /// <param name="name"></param>
  /// <param name="dict"></param>
  void ExecuteEventListener(CefRefPtr<CefBrowser> browser,
                            CefRefPtr<CefFrame> frame,
                            const CefString& name,
                            CefRefPtr<CefDictionaryValue> dict);

private:
  /// <summary>
  ///
  /// </summary>
  CefRefPtr<CefMessageRouterRendererSide> render_message_router_;

  /// <summary>
  ///
  /// </summary>
  FrameID2QCefClientMap frame_id_to_client_map_;

private:
  IMPLEMENT_REFCOUNTING(RenderDelegate);
};

}
