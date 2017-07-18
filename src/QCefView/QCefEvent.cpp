#include "stdafx.h"
#pragma region qt_headers
#include <QVariant>
#pragma endregion qt_headers

#pragma region cef_headers
#include <include/cef_app.h>
#include <include/wrapper/cef_message_router.h>
#pragma endregion cef_headers

#include "inc/QCefEvent.h"

QCefEvent::QCefEvent()
	: QObject(nullptr)
{

}

QCefEvent::QCefEvent(const char* name)
	: QObject()
{
	setObjectName(name);
}


void QCefEvent::setEventName(const char*  name)
{
	setObjectName(name);
}

void QCefEvent::setIntProperty(const char*  key, int value)
{
	Q_ASSERT(0 != QString::compare(key, "name", Qt::CaseInsensitive));
	setProperty(key, QVariant::fromValue(value));
}

void QCefEvent::setDoubleProperty(const char*  key, double value)
{
	Q_ASSERT(0 != QString::compare(key, "name", Qt::CaseInsensitive));
	setProperty(key, QVariant::fromValue(value));
}

void QCefEvent::setStringProperty(const char*  key, QString value)
{
	Q_ASSERT(0 != QString::compare(key, "name", Qt::CaseInsensitive));
	setProperty(key, QVariant::fromValue(value));
}

void QCefEvent::setBoolProperty(const char*  key, bool value)
{
	Q_ASSERT(0 != QString::compare(key, "name", Qt::CaseInsensitive));
	setProperty(key, QVariant::fromValue(value));
}
