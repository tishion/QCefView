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
	: pcb_(nullptr)
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
		pcb_ = cb;
	}
}

QCefQuery::QCefQuery(const QCefQuery& other)
	: reqeust_(other.reqeust_)
{
	if (other.pcb_)
	{
		other.pcb_->AddRef();
		pcb_ = other.pcb_;
	}
}

QCefQuery& QCefQuery::operator=(const QCefQuery& other)
{
	if (other.pcb_)
	{
		other.pcb_->AddRef();
	}

	CefBase* old_ptr = pcb_;
	pcb_ = other.pcb_;
	if (old_ptr)
	{
		old_ptr->Release();
	}
	return *this;
}

QCefQuery::~QCefQuery()
{
	if (pcb_)
	{
		pcb_->Release();
	}
}

const QString QCefQuery::reqeust() const
{
	return reqeust_;
}

void QCefQuery::responseSuccess(QString response) const
{
	if (pcb_)
	{
		CefString res;
		res.FromString(response.toStdString());
		((CefMessageRouterBrowserSide::Callback*)pcb_)->Success(res);
	}
}

void QCefQuery::responseFailure(int ec, QString response) const
{
	if (pcb_)
	{
		CefString res;
		res.FromString(response.toStdString());
		((CefMessageRouterBrowserSide::Callback*)pcb_)->Failure(ec, res);
	}
}
