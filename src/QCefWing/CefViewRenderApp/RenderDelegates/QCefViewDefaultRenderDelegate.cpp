#pragma region project_headers
#include "QCefViewDefaultRenderDelegate.h"
#include "QCefClient.h"
#pragma endregion project_headers

namespace QCefViewDefaultRenderDelegate {
void
CreateBrowserDelegate(QCefViewRenderApp::RenderDelegateSet& delegates)
{
  delegates.insert(new RenderDelegate());
}

RenderDelegate::RenderDelegate() {}

void
RenderDelegate::OnWebKitInitialized(CefRefPtr<QCefViewRenderApp> app)
{
  CefMessageRouterConfig config;
  config.js_query_function = QCEF_QUERY_NAME;
  config.js_cancel_function = QCEF_QUERY_CANCEL_NAME;
  render_message_router_ = CefMessageRouterRendererSide::Create(config);
}

void
RenderDelegate::OnContextCreated(CefRefPtr<QCefViewRenderApp> app,
                                 CefRefPtr<CefBrowser> browser,
                                 CefRefPtr<CefFrame> frame,
                                 CefRefPtr<CefV8Context> context)
{
  render_message_router_->OnContextCreated(browser, frame, context);

  int64 frameId = frame->GetIdentifier();
  auto it = frame_id_to_client_map_.find(frameId);
  if (it == frame_id_to_client_map_.end()) {
    // create and insert the QCefClient Object into this frame.window object
    CefRefPtr<CefV8Value> objWindow = context->GetGlobal();
    CefRefPtr<QCefClient> objClient = new QCefClient(browser, frame);
    objWindow->SetValue(QCEF_OBJECT_NAME, objClient->GetObject(), V8_PROPERTY_ATTRIBUTE_READONLY);
    frame_id_to_client_map_[frameId] = objClient;
  }
}

void
RenderDelegate::OnContextReleased(CefRefPtr<QCefViewRenderApp> app,
                                  CefRefPtr<CefBrowser> browser,
                                  CefRefPtr<CefFrame> frame,
                                  CefRefPtr<CefV8Context> context)
{
  render_message_router_->OnContextReleased(browser, frame, context);

  int64 frameId = frame->GetIdentifier();
  auto it = frame_id_to_client_map_.find(frameId);
  if (it != frame_id_to_client_map_.end()) {
    frame_id_to_client_map_.erase(it);
  }
}

bool
RenderDelegate::OnProcessMessageReceived(CefRefPtr<QCefViewRenderApp> app,
                                         CefRefPtr<CefBrowser> browser,
                                         CefRefPtr<CefFrame> frame,
                                         CefProcessId source_process,
                                         CefRefPtr<CefProcessMessage> message)
{
  if (render_message_router_->OnProcessMessageReceived(browser, frame, source_process, message)) {
    return true;
  }

  if (OnTriggerEventNotifyMessage(browser, frame, source_process, message)) {
    return true;
  }

  return false;
}

bool
RenderDelegate::OnTriggerEventNotifyMessage(CefRefPtr<CefBrowser> browser,
                                            CefRefPtr<CefFrame> frame,
                                            CefProcessId source_process,
                                            CefRefPtr<CefProcessMessage> message)
{
  if (message->GetName() == TRIGGEREVENT_NOTIFY_MESSAGE) {
    CefRefPtr<CefListValue> messageArguments = message->GetArgumentList();
    if (messageArguments && (messageArguments->GetSize() >= 2)) {
      int idx = 0;
      if (CefValueType::VTYPE_STRING == messageArguments->GetType(idx)) {
        CefString eventName = messageArguments->GetString(idx++);

        if (CefValueType::VTYPE_DICTIONARY == messageArguments->GetType(idx)) {
          CefRefPtr<CefDictionaryValue> dict = messageArguments->GetDictionary(idx++);

          ExecuteEventListener(browser, frame, eventName, dict);
          return true;
        }
      }
    }
  }

  return false;
}

void
RenderDelegate::ExecuteEventListener(CefRefPtr<CefBrowser> browser,
                                     CefRefPtr<CefFrame> frame,
                                     const CefString& name,
                                     CefRefPtr<CefDictionaryValue> dict)
{
  if (browser && frame) {
    int64 frameId = frame->GetIdentifier();
    auto it = frame_id_to_client_map_.find(frameId);
    if (it != frame_id_to_client_map_.end()) {
      const CefRefPtr<QCefClient>& objClient = it->second;
      objClient->ExecuteEventListener(name, dict);
    }
  }
}

}
