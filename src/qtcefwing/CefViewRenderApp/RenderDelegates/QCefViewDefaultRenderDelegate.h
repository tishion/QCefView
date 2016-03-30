#pragma once
#pragma region cef_headers
#include <include/wrapper/cef_message_router.h>
#pragma endregion cef_headers

#pragma region project_headers
#include "../QCefViewRenderApp.h"
#include "QCefClientObjectManager.h"
#pragma endregion project_headers

namespace QCefViewDefaultRenderDelegate
{
	void CreateBrowserDelegate(QCefViewRenderApp::RenderDelegateSet& delegates);

	class RenderDelegate
		: public QCefViewRenderApp::RenderDelegate
	{
	public:
		RenderDelegate();

		virtual void OnWebKitInitialized(CefRefPtr<QCefViewRenderApp> app);

		virtual void OnContextCreated(CefRefPtr<QCefViewRenderApp> app,
			CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefV8Context> context);

		virtual void OnContextReleased(CefRefPtr<QCefViewRenderApp> app,
			CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefV8Context> context);

		virtual bool OnProcessMessageReceived(
			CefRefPtr<QCefViewRenderApp> app,
			CefRefPtr<CefBrowser> browser,
			CefProcessId source_process,
			CefRefPtr<CefProcessMessage> message);

	private:
		CefRefPtr<CefMessageRouterRendererSide> render_message_router_;
		CefRefPtr<QCefClientObjectManager>	qcefclientobject_manager_;

	private:
		IMPLEMENT_REFCOUNTING(RenderDelegate);
	};

}
