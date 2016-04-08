#pragma once
#pragma region stl_headers
#include <unordered_map>
#pragma endregion


#pragma region cef_headers
#include <include/wrapper/cef_message_router.h>
#pragma endregion cef_headers

#pragma region project_headers
#include "../QCefViewRenderApp.h"
#pragma endregion project_headers


namespace QCefViewDefaultRenderDelegate
{
	void CreateBrowserDelegate(QCefViewRenderApp::RenderDelegateSet& delegates);

	class RenderDelegate
		: public QCefViewRenderApp::RenderDelegate
	{
		typedef std::unordered_map<int64, CefRefPtr<CefBase>> FrameID2QCefClientMap;
		typedef std::unordered_map<int, FrameID2QCefClientMap> BrowserID2FramesMap;
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

	protected:
		bool OnTriggerEventNotifyMessage(
			CefRefPtr<CefBrowser> browser,
			CefProcessId source_process,
			CefRefPtr<CefProcessMessage> message);

		void ExecuteEventListener(CefRefPtr<CefBrowser> browser,
			int frameId,
			const CefString& name,
			const CefV8ValueList& arguments);

	private:
		CefRefPtr<CefMessageRouterRendererSide> render_message_router_;
		BrowserID2FramesMap mapBrowser_;

	private:
		IMPLEMENT_REFCOUNTING(RenderDelegate);
	};

}
