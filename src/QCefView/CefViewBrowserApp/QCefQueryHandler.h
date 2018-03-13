#pragma once
#pragma region std_headers
#include <map>
#include <mutex>
#pragma endregion std_headers

#pragma region cef_headers
#include <include/cef_base.h>
#include <include/wrapper/cef_stream_resource_handler.h>
#include <include/wrapper/cef_message_router.h>
#pragma endregion cef_headers

#include "CCefWindow.h"

class QCefQueryHandler 
	: public CefBaseRefCounted
	, public CefMessageRouterBrowserSide::Handler
{
public:
	QCefQueryHandler(CCefWindow* pQCefWin);
	~QCefQueryHandler();

	virtual bool OnQuery(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		int64 query_id,
		const CefString& request,
		bool persistent,
		CefRefPtr<Callback> callback) OVERRIDE;

	virtual void OnQueryCanceled(CefRefPtr<CefBrowser> browser, 
		CefRefPtr<CefFrame> frame, 
		int64 query_id) override;

	bool Response(int64_t query,
		bool success, const CefString& response, int error);

private:
	QPointer<CCefWindow> pQCefWindow_;
	std::map<int64, CefRefPtr<Callback>>	mapCallback_;
	std::mutex	mtxCallbackMap_;

private:
	IMPLEMENT_REFCOUNTING(QCefQueryHandler);
};

