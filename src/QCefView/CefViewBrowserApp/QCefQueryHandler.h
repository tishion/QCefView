#pragma once

#pragma region cef_headers
#include <include/wrapper/cef_stream_resource_handler.h>
#include <include/wrapper/cef_message_router.h>
#pragma endregion cef_headers

#include "../inc/QCefView.h"
#include "../CCefWindow.h"

class QCefQueryHandler 
	: public CefMessageRouterBrowserSide::Handler
{
public:
	QCefQueryHandler(QCefView* host);
	~QCefQueryHandler();

	virtual bool OnQuery(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		int64 query_id,
		const CefString& request,
		bool persistent,
		CefRefPtr<Callback> callback) OVERRIDE;

private:
	QPointer<QCefView> hostWidget_;
};

