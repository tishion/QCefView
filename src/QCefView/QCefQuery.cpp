#include "stdafx.h"
#pragma region qt_headers
#pragma endregion qt_headers

#pragma region cef_headers
#include <include/cef_app.h>
#include <include/wrapper/cef_message_router.h>
#pragma endregion cef_headers

#include "inc/QCefQuery.h"

//////////////////////////////////////////////////////////////////////////
QCefQuery::QCefQuery()
	: pCefQueryCallBack_(nullptr)
{

}

QCefQuery::QCefQuery(
	QString req,
	CefBase* cb)
	: reqeust_(req)
{
	if (cb)
	{
		cb->AddRef();
		pCefQueryCallBack_ = cb;
	}
}

QCefQuery::QCefQuery(const QCefQuery& other)
	: reqeust_(other.reqeust_)
{
	if (other.pCefQueryCallBack_)
	{
		other.pCefQueryCallBack_->AddRef();
		pCefQueryCallBack_ = other.pCefQueryCallBack_;
	}
}

QCefQuery& QCefQuery::operator=(const QCefQuery& other)
{
	if (other.pCefQueryCallBack_)
	{
		other.pCefQueryCallBack_->AddRef();
	}

	CefBase* old_ptr = pCefQueryCallBack_;
	pCefQueryCallBack_ = other.pCefQueryCallBack_;
	if (old_ptr)
	{
		old_ptr->Release();
	}
	return *this;
}

QCefQuery::~QCefQuery()
{
	if (pCefQueryCallBack_)
	{
		pCefQueryCallBack_->Release();
	}
}

const QString QCefQuery::reqeust() const
{
	return reqeust_;
}

void QCefQuery::responseSuccess(const QString& response) const
{
	if (pCefQueryCallBack_)
	{
		CefString res;
		res.FromString(response.toStdString());
		((CefMessageRouterBrowserSide::Callback*)pCefQueryCallBack_)->Success(res);
	}
}

void QCefQuery::responseFailure(int ec, const QString& response) const
{
	if (pCefQueryCallBack_)
	{
		CefString res;
		res.FromString(response.toStdString());
		((CefMessageRouterBrowserSide::Callback*)pCefQueryCallBack_)->Failure(ec, res);
	}
}
