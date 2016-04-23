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
		mtxCallbackMap_.lock();
		mapCallback_[query_id] = callback;
		mtxCallbackMap_.unlock();

		QString strRequest = QString::fromStdString(request.ToString());
		QMetaObject::invokeMethod(hostWidget_,
			"processQCefQueryRequest",
			Qt::QueuedConnection,
			Q_ARG(QCefQuery, QCefQuery(hostWidget_, strRequest, query_id)));
		return true;
	}
	return false;
}

void QCefQueryHandler::OnQueryCanceled(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	int64 query_id)
{
	mtxCallbackMap_.lock();
	auto it = mapCallback_.find(query_id);
	if (it != mapCallback_.end())
	{
		mapCallback_.erase(it);
	}
	mtxCallbackMap_.unlock();
}

bool QCefQueryHandler::Response(int64_t query, 
	bool success, const CefString& response, int error)
{
	CefRefPtr<Callback> cb;
	mtxCallbackMap_.lock();
	auto it = mapCallback_.find(query);
	if (it != mapCallback_.end())
	{
		cb = it->second;
		mapCallback_.erase(it);
	}
	mtxCallbackMap_.unlock();

	if (!cb)
	{
		return false;
	}

	if (success)
	{
		cb->Success(response);
	}
	else
	{
		cb->Failure(error, response);
	}

	return true;
}

