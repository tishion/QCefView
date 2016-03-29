#ifndef GXXCEFVIEWHANDLER_H_
#define GXXCEFVIEWHANDLER_H_
#pragma once

#include <list>
#include <map>
#include <set>
#include <string>
#include <mutex>
#include <QPointer>

#include "include/cef_client.h"
#include "include/wrapper/cef_message_router.h"
#include "../../inc/QCefView.h"

class QCefQueryHandler;

class QCefViewBrowserHandler
	: public CefClient
	, public CefContextMenuHandler
	//, public CefDialogHandler
	, public CefDisplayHandler
	//, public CefDownloadHandler
	, public CefDragHandler
	//, public CefGeolocationHandler
	, public CefJSDialogHandler
	, public CefKeyboardHandler
	, public CefLifeSpanHandler
	, public CefLoadHandler
	, public CefRequestHandler
{
	typedef CefRefPtr<CefMessageRouterBrowserSide>	MessageRouterPtr;
	typedef std::set<CefMessageRouterBrowserSide::Handler*> MessageHandlerSet;
	typedef std::list<CefRefPtr<CefBrowser> > BrowserList;
public:

	QCefViewBrowserHandler(QCefView* host);
	~QCefViewBrowserHandler();

	//////////////////////////////////////////////////////////////////////////
	// CefClient methods:
	virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler()
	{
		return this;
	}
	//virtual CefRefPtr<CefDialogHandler> GetDialogHandler()
	//{
	//	return this;
	//}
	virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler()
	{
		return this;
	}
	//virtual CefRefPtr<CefDownloadHandler> GetDownloadHandler()
	//{
	//	return this;
	//}
	virtual CefRefPtr<CefDragHandler> GetDragHandler()
	{
		return this;
	}
	//virtual CefRefPtr<CefGeolocationHandler> GetGeolocationHandler()
	//{
	//	return this;
	//}
	virtual CefRefPtr<CefJSDialogHandler> GetJSDialogHandler()
	{
		return this;
	}
	virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler()
	{
		return this;
	}
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler()
	{
		return this;
	}
	virtual CefRefPtr<CefLoadHandler> GetLoadHandler()
	{
		return this;
	}
	virtual CefRefPtr<CefRequestHandler> GetRequestHandler()
	{
		return this;
	}

	virtual bool OnProcessMessageReceived(
		CefRefPtr<CefBrowser> browser,
		CefProcessId source_process,
		CefRefPtr<CefProcessMessage> message);

	// CefContextMenuHandler methods
	virtual void OnBeforeContextMenu(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefContextMenuParams> params,
		CefRefPtr<CefMenuModel> model);
	virtual bool OnContextMenuCommand(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefContextMenuParams> params,
		int command_id,
		EventFlags event_flags);

	// CefDialogHandler methods
	//virtual bool OnFileDialog(
	//	CefRefPtr<CefBrowser> browser,
	//	FileDialogMode mode,
	//	const CefString& title,
	//	const CefString& default_file_name,
	//	const std::vector<CefString>& accept_types,
	//	CefRefPtr<CefFileDialogCallback> callback);

	// CefDisplayHandler methods
	virtual void OnAddressChange(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& url);
	virtual void OnTitleChange(
		CefRefPtr<CefBrowser> browser,
		const CefString& title);
	virtual bool OnConsoleMessage(
		CefRefPtr<CefBrowser> browser,
		const CefString& message,
		const CefString& source,
		int line);

	// CefDownloadHandler methods
	//virtual void OnBeforeDownload(
	//	CefRefPtr<CefBrowser> browser,
	//	CefRefPtr<CefDownloadItem> download_item,
	//	const CefString& suggested_name,
	//	CefRefPtr<CefBeforeDownloadCallback> callback);
	//virtual void OnDownloadUpdated(
	//	CefRefPtr<CefBrowser> browser,
	//	CefRefPtr<CefDownloadItem> download_item,
	//	CefRefPtr<CefDownloadItemCallback> callback);

	//CefDragHandler methods
	virtual bool OnDragEnter(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDragData> dragData,
		CefDragHandler::DragOperationsMask mask);

	// CefGeolocationHandler methods
	//virtual bool OnRequestGeolocationPermission(
	//	CefRefPtr<CefBrowser> browser,
	//	const CefString& requesting_url,
	//	int request_id,
	//	CefRefPtr<CefGeolocationCallback> callback);

	// CefJSDialogHandler methods
	virtual bool OnJSDialog(
		CefRefPtr<CefBrowser> browser,
		const CefString& origin_url,
		const CefString& accept_lang,
		JSDialogType dialog_type,
		const CefString& message_text,
		const CefString& default_prompt_text,
		CefRefPtr<CefJSDialogCallback> callback,
		bool& suppress_message);
	virtual bool OnBeforeUnloadDialog(
		CefRefPtr<CefBrowser> browser,
		const CefString& message_text,
		bool is_reload,
		CefRefPtr<CefJSDialogCallback> callback);
	virtual void OnResetDialogState(
		CefRefPtr<CefBrowser> browser);

	// CefKeyboardHandler methods
	virtual bool OnPreKeyEvent(
		CefRefPtr<CefBrowser> browser,
		const CefKeyEvent& event,
		CefEventHandle os_event,
		bool* is_keyboard_shortcut);

	// CefLifeSpanHandler methods:
	virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& target_url,
		const CefString& target_frame_name,
		CefLifeSpanHandler::WindowOpenDisposition target_disposition,
		bool user_gesture,
		const CefPopupFeatures& popupFeatures,
		CefWindowInfo& windowInfo,
		CefRefPtr<CefClient>& client,
		CefBrowserSettings& settings,
		bool* no_javascript_access);
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser);
	virtual bool DoClose(CefRefPtr<CefBrowser> browser);
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser);

	// CefLoadHandler methods
	virtual void OnLoadingStateChange(
		CefRefPtr<CefBrowser> browser,
		bool isLoading,
		bool canGoBack,
		bool canGoForward);
	virtual void OnLoadStart(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame);
	virtual void OnLoadEnd(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		int httpStatusCode);
	virtual void OnLoadError(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		ErrorCode errorCode,
		const CefString& errorText,
		const CefString& failedUrl);

	// CefRequestHandler methods
	virtual bool OnBeforeBrowse(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request,
		bool is_redirect);
	virtual bool OnOpenURLFromTab(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& target_url,
		CefRequestHandler::WindowOpenDisposition target_disposition,
		bool user_gesture);
	virtual CefRefPtr<CefResourceHandler> GetResourceHandler(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request);
	virtual bool OnQuotaRequest(
		CefRefPtr<CefBrowser> browser,
		const CefString& origin_url,
		int64 new_size,
		CefRefPtr<CefRequestCallback> callback);
	virtual void OnProtocolExecution(
		CefRefPtr<CefBrowser> browser,
		const CefString& url,
		bool& allow_os_execution);
	virtual void OnRenderProcessTerminated(
		CefRefPtr<CefBrowser> browser,
		TerminationStatus status);

	//////////////////////////////////////////////////////////////////////////

	void setHostWidget(QCefView* host);

	CefRefPtr<CefBrowser> GetBrowser() const;

	int GetBrowserId() const;

	// Request that all existing browser windows close.
	void CloseAllBrowsers(bool force_close);

	void CloseAllPopupBrowsers(bool force_close);

	bool IsClosing() const;

	bool TriggerEvent(const CefRefPtr<CefProcessMessage> msg);

	bool DispatchNotifyRequest(CefRefPtr<CefBrowser> browser,
		CefProcessId source_process,
		CefRefPtr<CefProcessMessage> message);

private:
	int browser_count_;
	int main_browser_id_;
	bool is_closing_;
	mutable std::mutex	mtx_;

	CefRefPtr<CefBrowser> main_browser_;

	QPointer<QCefView> hostWidget_;

	MessageRouterPtr message_router_;

	//MessageHandlerSet message_handler_set_;
	QCefQueryHandler* cefquery_handler_;
	
	// List of existing browser windows. Only accessed on the CEF UI thread.
	BrowserList popup_browser_list_;

	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(QCefViewBrowserHandler);
};

#endif

