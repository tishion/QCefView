#ifndef QCEFSETTINGS_H
#define QCEFSETTINGS_H
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

namespace QCefSetting
{
	/// <summary>
	/// 
	/// </summary>
	void QCEFVIEW_EXPORT setBrowserSubProcessPath(const QString& path);

	/// <summary>
	/// 
	/// </summary>
	const QCEFVIEW_EXPORT QString browserSubProcessPath();

	/// <summary>
	/// 
	/// </summary>
	void QCEFVIEW_EXPORT setResourceDirectoryPath(const QString& path);

	/// <summary>
	/// 
	/// </summary>
	const QCEFVIEW_EXPORT QString resourceDirectoryPath();

	/// <summary>
	/// 
	/// </summary>
	void QCEFVIEW_EXPORT setLocalesDirectoryPath(const QString& path);

	/// <summary>
	/// 
	/// </summary>
	const QCEFVIEW_EXPORT QString localesDirectoryPath();

	/// <summary>
	/// 
	/// </summary>
	void QCEFVIEW_EXPORT setUserAgent(const QString& agent);

	/// <summary>
	/// 
	/// </summary>
	const QCEFVIEW_EXPORT QString userAgent();

	/// <summary>
	/// 
	/// </summary>
	void QCEFVIEW_EXPORT setCachePath(const QString& path);

	/// <summary>
	/// 
	/// </summary>
	const QCEFVIEW_EXPORT QString cachePath();

	/// <summary>
	/// 
	/// </summary>
	void QCEFVIEW_EXPORT setUserDataPath(const QString& path);

	/// <summary>
	/// 
	/// </summary>
	const QCEFVIEW_EXPORT QString userDataPath();

	/// <summary>
	/// 
	/// </summary>
	void QCEFVIEW_EXPORT setPersistSessionCookies(bool enabled);

	/// <summary>
	/// 
	/// </summary>
	const QCEFVIEW_EXPORT bool persistSessionCookies();

	/// <summary>
	/// 
	/// </summary>
	void QCEFVIEW_EXPORT setPersistUserPreferences(bool enabled);

	/// <summary>
	/// 
	/// </summary>
	const QCEFVIEW_EXPORT bool persistUserPreferences();

	/// <summary>
	/// 
	/// </summary>
	void QCEFVIEW_EXPORT setLocale(const QString& locale);

	/// <summary>
	/// 
	/// </summary>
	const QCEFVIEW_EXPORT QString locale();

	/// <summary>
	/// 
	/// </summary>
	void QCEFVIEW_EXPORT setRemoteDebuggingPort(int port);

	/// <summary>
	/// 
	/// </summary>
	const QCEFVIEW_EXPORT int remoteDebuggingPort();

	/// <summary>
	/// 
	/// </summary>
	void QCEFVIEW_EXPORT setBackgroundColor(const QColor& color);

	/// <summary>
	/// 
	/// </summary>
	const QCEFVIEW_EXPORT QColor backgroundColor();

	/// <summary>
	/// 
	/// </summary>
	void QCEFVIEW_EXPORT setAcceptLanguageList(const QString& languages);

	/// <summary>
	/// 
	/// </summary>
	const QCEFVIEW_EXPORT QString acceptLanguageList();
};

#endif
