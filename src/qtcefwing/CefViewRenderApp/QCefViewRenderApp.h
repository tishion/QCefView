#ifndef QCEFVIEWRENDERAPP_H_
#define QCEFVIEWRENDERAPP_H_
#pragma once

#pragma region stl_headers
#include <set>
#pragma endregion stl_headers

#pragma region cef_headers
#include <include/cef_app.h>
#pragma endregion cef_headers

class QCefViewRenderApp
	: public CefApp
	, public CefRenderProcessHandler
{
public:
	QCefViewRenderApp();
	~QCefViewRenderApp();

	class RenderDelegate 
		: public virtual CefBase 
	{
	public:
		virtual void OnRenderThreadCreated(CefRefPtr<QCefViewRenderApp> app,
			CefRefPtr<CefListValue> extra_info) {}

		virtual void OnWebKitInitialized(CefRefPtr<QCefViewRenderApp> app) {}

		virtual void OnBrowserCreated(CefRefPtr<QCefViewRenderApp> app,
			CefRefPtr<CefBrowser> browser) {}

		virtual void OnBrowserDestroyed(CefRefPtr<QCefViewRenderApp> app,
			CefRefPtr<CefBrowser> browser) {}

		virtual CefRefPtr<CefLoadHandler> GetLoadHandler(CefRefPtr<QCefViewRenderApp> app)
		{
			return NULL;
		}

		virtual bool OnBeforeNavigation(CefRefPtr<QCefViewRenderApp> app,
			CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefRequest> request,
			cef_navigation_type_t navigation_type,
			bool is_redirect) 
		{
			return false;
		}

		virtual void OnContextCreated(CefRefPtr<QCefViewRenderApp> app,
			CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefV8Context> context) {}

		virtual void OnContextReleased(CefRefPtr<QCefViewRenderApp> app,
			CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefV8Context> context) {}

		virtual void OnUncaughtException(CefRefPtr<QCefViewRenderApp> app,
			CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefV8Context> context,
			CefRefPtr<CefV8Exception> exception,
			CefRefPtr<CefV8StackTrace> stackTrace) {}

		virtual void OnFocusedNodeChanged(CefRefPtr<QCefViewRenderApp> app,
			CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefDOMNode> node) {}

		// Called when a process message is received. Return true if the message was
		// handled and should not be passed on to other handlers. RenderDelegates
		// should check for unique message names to avoid interfering with each
		// other.
		virtual bool OnProcessMessageReceived(
			CefRefPtr<QCefViewRenderApp> app,
			CefRefPtr<CefBrowser> browser,
			CefProcessId source_process,
			CefRefPtr<CefProcessMessage> message) 
		{
			return false;
		}
	};
	typedef std::set<CefRefPtr<RenderDelegate> > RenderDelegateSet;

private:
	// Creates all of the RenderDelegate objects. Implemented in
	// client_app_delegates.
	static void CreateRenderDelegates(RenderDelegateSet& delegates);

	//////////////////////////////////////////////////////////////////////////
	// CefApp methods:
	virtual void OnBeforeCommandLineProcessing(
		const CefString& process_type,
		CefRefPtr<CefCommandLine> command_line);

	virtual void OnRegisterCustomSchemes(
		CefRefPtr<CefSchemeRegistrar> registrar);

	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler();

	// CefRenderProcessHandler methods:
	virtual void OnRenderThreadCreated(
		CefRefPtr<CefListValue> extra_info);

	virtual void OnWebKitInitialized();

	virtual void OnBrowserCreated(
		CefRefPtr<CefBrowser> browser);

	virtual void OnBrowserDestroyed(
		CefRefPtr<CefBrowser> browser);

	virtual CefRefPtr<CefLoadHandler> GetLoadHandler();

	virtual bool OnBeforeNavigation(
		CefRefPtr<CefBrowser> browser, 
		CefRefPtr<CefFrame> frame, 
		CefRefPtr<CefRequest> request, 
		NavigationType navigation_type, 
		bool is_redirect);

	virtual void OnContextCreated(
		CefRefPtr<CefBrowser> browser, 
		CefRefPtr<CefFrame> frame, 
		CefRefPtr<CefV8Context> context);

	virtual void OnContextReleased(
		CefRefPtr<CefBrowser> browser, 
		CefRefPtr<CefFrame> frame, 
		CefRefPtr<CefV8Context> context);

	virtual void OnUncaughtException(
		CefRefPtr<CefBrowser> browser, 
		CefRefPtr<CefFrame> frame, 
		CefRefPtr<CefV8Context> context, 
		CefRefPtr<CefV8Exception> exception, 
		CefRefPtr<CefV8StackTrace> stackTrace);

	virtual void OnFocusedNodeChanged(
		CefRefPtr<CefBrowser> browser, 
		CefRefPtr<CefFrame> frame, 
		CefRefPtr<CefDOMNode> node);

	virtual bool OnProcessMessageReceived(
		CefRefPtr<CefBrowser> browser, 
		CefProcessId source_process, 
		CefRefPtr<CefProcessMessage> message);

private:
	// Set of supported RenderDelegates. Only used in the renderer process.
	RenderDelegateSet render_delegates_;
	
	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(QCefViewRenderApp);
};

#endif	// QCEFVIEWRENDERAPP_H_
