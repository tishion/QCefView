#ifndef QCEFEVENT_H
#define QCEFEVENT_H
#pragma once
#pragma region qt_headers
#include <QtCore/qglobal.h>
#include <QObject>
#include <QString>
#pragma endregion qt_headers

#ifdef QCEFVIEW_LIB
	#define QCEFVIEW_EXPORT Q_DECL_EXPORT
#else
	#define QCEFVIEW_EXPORT Q_DECL_IMPORT
	#pragma comment(lib, "QCefView.lib")
#endif

class QCEFVIEW_EXPORT QCefEvent
	: public QObject
{
	Q_OBJECT
public:
	QCefEvent();
	QCefEvent(const char* name);

	void setEventName(const char* name);

	void setIntProperty(const char* key, int value);
	
	void setDoubleProperty(const char*  key, double value);
	
	void setStringProperty(const char*  key, QString value);
	
	void setBoolProperty(const char*  key, bool value);
};

#endif	//QCEFEVENT_H