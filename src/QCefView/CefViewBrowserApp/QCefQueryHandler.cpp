#include "stdafx.h"

#include "QCefQueryHandler.h"
#include "inc/QCefQuery.h"


QCefQueryHandler::QCefQueryHandler(QCefView* host)
	: hostWidget_(host)
{
}


QCefQueryHandler::~QCefQueryHandler()
{
}

bool QCefQueryHandler::OnQuery(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	int64 query_id,
	const CefString& request,
	bool persistent,
	CefRefPtr<Callback> callback)
{
	if (hostWidget_)
	{
		qRegisterMetaType<QCefQuery>("QCefQuery");
		QString strRequest = QString::fromStdString(request.ToString());
		QMetaObject::invokeMethod(hostWidget_,
			"processQCefQueryRequest",
			Qt::QueuedConnection,
			Q_ARG(QCefQuery, QCefQuery(strRequest, callback)));
		return true;
	}
	return false;
}

