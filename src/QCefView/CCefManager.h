#pragma once

#include <mutex>
#include <QObject>
#include <QWidget>
#include <QThread>
#include <QCoreApplication>

#include "CefViewBrowserApp/QCefViewBrowserApp.h"
#include "CefViewBrowserApp/QCefViewBrowserHandler.h"

class CCefManager
	: public QObject
{
	Q_OBJECT
protected:
	CCefManager();
	~CCefManager();

protected slots :
	void releaseCef();

public:
	static CCefManager& getInstance();

	void AddBrowserRefCount();

	void ReleaseBrowserRefCount();

private:
	CefRefPtr<QCefViewBrowserApp> app_;
	CefSettings cef_settings_;

	int nBrowserRefCount_;
};

