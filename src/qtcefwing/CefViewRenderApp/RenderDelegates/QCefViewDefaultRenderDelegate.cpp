#include "stdafx.h"

#pragma region project_headers
#include "QCefViewDefaultRenderDelegate.h"
#pragma endregion project_headers

namespace QCefViewDefaultRenderDelegate
{
	void CreateBrowserDelegate(QCefViewRenderApp::RenderDelegateSet& delegates)
	{
		delegates.insert(new RenderDelegate());
	}

	RenderDelegate::RenderDelegate()
	{

	}

	void RenderDelegate::OnWebKitInitialized(CefRefPtr<QCefViewRenderApp> app)
	{
		CefMessageRouterConfig config;
		config.js_query_function = QTCEF_QUERY_NAME;
		config.js_cancel_function = QTCEF_QUERY_CANCEL_NAME;
		render_message_router_ = CefMessageRouterRendererSide::Create(config);
		gxxclientobject_manager_ = new QCefClientObjectManager;
	}

	void RenderDelegate::OnContextCreated(CefRefPtr<QCefViewRenderApp> app,
		CefRefPtr<CefBrowser> browser, 
		CefRefPtr<CefFrame> frame, 
		CefRefPtr<CefV8Context> context)
	{
		render_message_router_->OnContextCreated(browser, frame, context);
		gxxclientobject_manager_->OnContextCreated(browser, frame, context);
	}

	void RenderDelegate::OnContextReleased(CefRefPtr<QCefViewRenderApp> app,
		CefRefPtr<CefBrowser> browser, 
		CefRefPtr<CefFrame> frame, 
		CefRefPtr<CefV8Context> context)
	{
		render_message_router_->OnContextReleased(browser, frame, context);
		gxxclientobject_manager_->OnContextReleased(browser, frame, context);
	}

	bool RenderDelegate::OnProcessMessageReceived(CefRefPtr<QCefViewRenderApp> app,
		CefRefPtr<CefBrowser> browser, 
		CefProcessId source_process, 
		CefRefPtr<CefProcessMessage> message)
	{
		if (render_message_router_->OnProcessMessageReceived(browser, source_process, message))
		{
			return true;
		}

		if (gxxclientobject_manager_->OnProcessMessageReceived(browser, source_process, message))
		{
			return true;
		}

		return false;
	}
}
