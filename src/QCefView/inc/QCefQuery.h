#ifndef QCEFQUERY_H
#define QCEFQUERY_H
#pragma once
#pragma region qt_headers
#include <QtCore/qglobal.h>
#include <QString>
#include <QPointer>
#include <QMetaType>
#pragma endregion qt_headers

#ifdef QCEFVIEW_LIB
	#define QCEFVIEW_EXPORT Q_DECL_EXPORT
#else
	#define QCEFVIEW_EXPORT Q_DECL_IMPORT
	#pragma comment(lib, "QCefView.lib")
#endif

class QCefView;
class QCEFVIEW_EXPORT QCefQuery
{
public:
	QCefQuery();

	QCefQuery(QPointer<QCefView> cefView, QString req, int64_t query);
	
	QCefQuery(const QCefQuery& other);

	QCefQuery& operator=(const QCefQuery& other);
	
	~QCefQuery();

	const QString reqeust() const;

	bool responseSuccess(const QString& response) const;

	bool responseFailure(int ec, const QString& response) const;

private:
	QPointer<QCefView>	pCefView_;
	int64_t				query_id_;
	QString				reqeust_;
	static int			TYPEID;
};
Q_DECLARE_METATYPE(QCefQuery);
#endif	//QCEFQUERY_H