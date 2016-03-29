#ifndef QCEFQUERY_H
#define QCEFQUERY_H
#pragma once
#pragma region qt_headers
#include <QtCore/qglobal.h>
#include <QString>
#include <QMetaType>
#pragma endregion qt_headers

#ifdef QCEFVIEW_LIB
	#define QCEFVIEW_EXPORT Q_DECL_EXPORT
#else
	#define QCEFVIEW_EXPORT Q_DECL_IMPORT
	#pragma comment(lib, "QCefView.lib")
#endif

class CefBase;
class QCEFVIEW_EXPORT QCefQuery
{
public:
	QCefQuery();

	QCefQuery(QString req,
		CefBase* cb);

	QCefQuery(const QCefQuery& other);

	QCefQuery& operator=(const QCefQuery& other);
	~QCefQuery();

	const QString reqeust() const;

	void responseSuccess(QString response) const;

	void responseFailure(int ec, QString response) const;

protected:
	CefBase* pcb_;

private:
	QString reqeust_;
};

Q_DECLARE_METATYPE(QCefQuery);

#endif	//QCEFQUERY_H