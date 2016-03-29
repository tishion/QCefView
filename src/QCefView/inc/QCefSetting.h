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
	void QCEFVIEW_EXPORT setBrowserSubProcessPath(const QString& path);
	const QCEFVIEW_EXPORT QString browserSubProcessPath();

	void QCEFVIEW_EXPORT setResourceDirectoryPath(const QString& path);
	const QCEFVIEW_EXPORT QString resourceDirectoryPath();

	void QCEFVIEW_EXPORT setLocalesDirectoryPath(const QString& path);
	const QCEFVIEW_EXPORT QString localesDirectoryPath();

	void QCEFVIEW_EXPORT setUserAgent(const QString& agent);
	const QCEFVIEW_EXPORT QString userAgent();
};

#endif
