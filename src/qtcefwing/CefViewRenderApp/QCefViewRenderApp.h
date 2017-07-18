#ifndef QCEFVIEWRENDERAPP_H_
#define QCEFVIEWRENDERAPP_H_
#pragma once

#pragma region stl_headers
#include <set>
#pragma endregion stl_headers

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
	QCefViewRenderApp();

	/// <summary>
	/// 
	/// </summary>
	~QCefViewRenderApp();

	/// <summary>
	/// 
	/// </summary>
	class RenderDelegate 
		: public virtual CefBase 
	{
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="app"></param>
		/// <param name="extra_info"></param>
		virtual void OnRenderThreadCreated(CefRefPtr<QCefViewRenderApp> app,
			CefRefPtr<CefListValue> extra_info) {}

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
			CefRefPtr<CefBrowser> browser) {}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="app"></param>
		/// <param name="browser"></param>
		virtual void OnBrowserDestroyed(CefRefPtr<QCefViewRenderApp> app,
			CefRefPtr<CefBrowser> browser) {}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="app"></param>
		/// <returns></returns>
		virtual CefRefPtr<CefLoadHandler> GetLoadHandler(CefRefPtr<QCefViewRenderApp> app)
		{
			return nullptr;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="app"></param>
		/// <param name="browser"></param>
		/// <param name="frame"></param>
		/// <param name="request"></param>
		/// <param name="navigation_type"></param>
		/// <param name="is_redirect"></param>
		/// <returns></returns>
		virtual bool OnBeforeNavigation(CefRefPtr<QCefViewRenderApp> app,
			CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefRequest> request,
			cef_navigation_type_t navigation_type,
			bool is_redirect) 
		{
			return false;
		}

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
			CefRefPtr<CefV8Context> context) {}

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
			CefRefPtr<CefV8Context> context) {}

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
			CefRefPtr<CefV8StackTrace> stackTrace) {}

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
			CefRefPtr<CefDOMNode> node) {}

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
		virtual bool OnProcessMessageReceived(
			CefRefPtr<QCefViewRenderApp> app,
			CefRefPtr<CefBrowser> browser,
			CefProcessId source_process,
			CefRefPtr<CefProcessMessage> message) 
		{
			return false;
		}
	};

	/// <summary>
	/// 
	/// </summary>
	typedef std::set<CefRefPtr<RenderDelegate> > RenderDelegateSet;

private:
	// Creates all of the RenderDelegate objects. Implemented in
	// client_app_delegates.
	/// <summary>
	/// 
	/// </summary>
	/// <param name="delegates"></param>
	static void CreateRenderDelegates(RenderDelegateSet& delegates);

	//////////////////////////////////////////////////////////////////////////
	// CefApp methods:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="process_type"></param>
	/// <param name="command_line"></param>
	virtual void OnBeforeCommandLineProcessing(
		const CefString& process_type,
		CefRefPtr<CefCommandLine> command_line);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="registrar"></param>
	virtual void OnRegisterCustomSchemes(
		CefRefPtr<CefSchemeRegistrar> registrar);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler();

	// CefRenderProcessHandler methods:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="extra_info"></param>
	virtual void OnRenderThreadCreated(
		CefRefPtr<CefListValue> extra_info);

	/// <summary>
	/// 
	/// </summary>
	virtual void OnWebKitInitialized();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="browser"></param>
	virtual void OnBrowserCreated(
		CefRefPtr<CefBrowser> browser);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="browser"></param>
	virtual void OnBrowserDestroyed(
		CefRefPtr<CefBrowser> browser);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	virtual CefRefPtr<CefLoadHandler> GetLoadHandler();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="browser"></param>
	/// <param name="frame"></param>
	/// <param name="request"></param>
	/// <param name="navigation_type"></param>
	/// <param name="is_redirect"></param>
	/// <returns></returns>
	virtual bool OnBeforeNavigation(
		CefRefPtr<CefBrowser> browser, 
		CefRefPtr<CefFrame> frame, 
		CefRefPtr<CefRequest> request, 
		NavigationType navigation_type, 
		bool is_redirect);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="browser"></param>
	/// <param name="frame"></param>
	/// <param name="context"></param>
	virtual void OnContextCreated(
		CefRefPtr<CefBrowser> browser, 
		CefRefPtr<CefFrame> frame, 
		CefRefPtr<CefV8Context> context);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="browser"></param>
	/// <param name="frame"></param>
	/// <param name="context"></param>
	virtual void OnContextReleased(
		CefRefPtr<CefBrowser> browser, 
		CefRefPtr<CefFrame> frame, 
		CefRefPtr<CefV8Context> context);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="browser"></param>
	/// <param name="frame"></param>
	/// <param name="context"></param>
	/// <param name="exception"></param>
	/// <param name="stackTrace"></param>
	virtual void OnUncaughtException(
		CefRefPtr<CefBrowser> browser, 
		CefRefPtr<CefFrame> frame, 
		CefRefPtr<CefV8Context> context, 
		CefRefPtr<CefV8Exception> exception, 
		CefRefPtr<CefV8StackTrace> stackTrace);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="browser"></param>
	/// <param name="frame"></param>
	/// <param name="node"></param>
	virtual void OnFocusedNodeChanged(
		CefRefPtr<CefBrowser> browser, 
		CefRefPtr<CefFrame> frame, 
		CefRefPtr<CefDOMNode> node);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="browser"></param>
	/// <param name="source_process"></param>
	/// <param name="message"></param>
	/// <returns></returns>
	virtual bool OnProcessMessageReceived(
		CefRefPtr<CefBrowser> browser, 
		CefProcessId source_process, 
		CefRefPtr<CefProcessMessage> message);

private:
	// Set of supported RenderDelegates. Only used in the renderer process.
	/// <summary>
	/// 
	/// </summary>
	RenderDelegateSet render_delegates_;
	
	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(QCefViewRenderApp);
};

#endif	// QCEFVIEWRENDERAPP_H_
