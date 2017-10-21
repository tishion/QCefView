#pragma once

#pragma region std_headers
#include <mutex>
#pragma endregion std_headers

#pragma region qt_headers
#include <QObject>
#include <QWidget>
#include <QThread>
#include <QCoreApplication>
#pragma endregion qt_headers

#include "CefViewBrowserApp/QCefViewBrowserApp.h"

/// <summary>
/// 
/// </summary>
class CCefManager
	: public QObject
{
	Q_OBJECT

protected:
	/// <summary>
	/// 
	/// </summary>
	CCefManager();

	/// <summary>
	/// 
	/// </summary>
	~CCefManager() {};

public:
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	static CCefManager& getInstance();

	/// <summary>
	/// 
	/// </summary>
	void initializeCef();

	/// <summary>
	/// 
	/// </summary>
	void uninitializeCef();

protected slots :
	/// <summary>
	/// 
	/// </summary>
	void releaseCef();

private:
	/// <summary>
	/// 
	/// </summary>
	CefRefPtr<QCefViewBrowserApp> app_;

	/// <summary>
	/// 
	/// </summary>
	CefSettings cef_settings_;

	/// <summary>
	/// 
	/// </summary>
	int64_t nBrowserRefCount_;
};

