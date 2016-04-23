#include "stdafx.h"
#pragma region qt_headers
#pragma endregion qt_headers

#pragma region cef_headers
#include <include/cef_app.h>
#include <include/wrapper/cef_message_router.h>
#pragma endregion cef_headers

#include "inc/QCefQuery.h"
#include "inc/QCefView.h"

int QCefQuery::TYPEID = qRegisterMetaType<QCefQuery>("QCefQuery");

//////////////////////////////////////////////////////////////////////////
QCefQuery::QCefQuery(QPointer<QCefView> cefView, QString req, int64_t query)
	: pCefView_(cefView), reqeust_(req), query_id_(query)
{
}

QCefQuery::QCefQuery()
	: pCefView_(NULL), query_id_(-1)
{

}

QCefQuery::QCefQuery(const QCefQuery& other)
{
	pCefView_ = other.pCefView_;
	reqeust_ = other.reqeust_;
	query_id_ = other.query_id_;
}

QCefQuery& QCefQuery::operator=(const QCefQuery& other)
{
	pCefView_ = other.pCefView_;
	reqeust_ = other.reqeust_;
	query_id_ = other.query_id_;
	return *this;
}

QCefQuery::~QCefQuery()
{

}

const QString QCefQuery::reqeust() const
{
	return reqeust_;
}

bool QCefQuery::responseSuccess(const QString& response) const
{
	if (pCefView_)
	{
		return pCefView_->responseQCefQuery(query_id_, true, response, 0);
	}
	return false;
}

bool QCefQuery::responseFailure(int ec, const QString& response) const
{
	if (pCefView_)
	{
		return pCefView_->responseQCefQuery(query_id_, false, response, ec);
	}
	return false;
}
