#include "stdafx.h"
#include "inc/QCefSetting.h"
#include "CCefSetting.h"

#include <QColor.h>

void QCefSetting::setBrowserSubProcessPath(const QString& path)
{
	CCefSetting::initializeInstance();
	CCefSetting::browser_sub_process_path.FromString(path.toStdString());
}

const QString QCefSetting::browserSubProcessPath()
{
	CCefSetting::initializeInstance();
	return QString::fromStdString(
		CCefSetting::browser_sub_process_path.ToString());
}

void QCefSetting::setResourceDirectoryPath(const QString& path)
{
	CCefSetting::initializeInstance();
	CCefSetting::resource_directory_path.FromString(path.toStdString());
}

const QString QCefSetting::resourceDirectoryPath()
{
	CCefSetting::initializeInstance();
	return QString::fromStdString(
		CCefSetting::resource_directory_path.ToString());
}

void QCefSetting::setLocalesDirectoryPath(const QString& path)
{
	CCefSetting::initializeInstance();
	CCefSetting::locales_directory_path.FromString(path.toStdString());
}

const QString QCefSetting::localesDirectoryPath()
{
	CCefSetting::initializeInstance();
	return QString::fromStdString(
		CCefSetting::locales_directory_path.ToString());
}

void QCefSetting::setUserAgent(const QString& agent)
{
	CCefSetting::initializeInstance();
	CCefSetting::user_agent.FromString(agent.toStdString());
}

const QString QCefSetting::userAgent()
{
	CCefSetting::initializeInstance();
	return QString::fromStdString(
		CCefSetting::user_agent.ToString());
}

void QCefSetting::setCachePath(const QString& path)
{
	CCefSetting::initializeInstance();
	CCefSetting::cache_path.FromString(path.toStdString());
}

const QString QCefSetting::cachePath()
{
	CCefSetting::initializeInstance();
	return QString::fromStdString(
		CCefSetting::cache_path.ToString());
}

void QCefSetting::setUserDataPath(const QString& path)
{
	CCefSetting::initializeInstance();
	CCefSetting::user_data_path.FromString(path.toStdString());
}

const QString QCefSetting::userDataPath()
{
	CCefSetting::initializeInstance();
	return QString::fromStdString(
		CCefSetting::user_data_path.ToString());
}

void QCefSetting::setPersistSessionCookies(bool enabled)
{
	CCefSetting::initializeInstance();
	CCefSetting::persist_session_cookies = enabled ? TRUE : FALSE;
}

const bool QCefSetting::persistSessionCookies()
{
	CCefSetting::initializeInstance();
	return CCefSetting::persist_session_cookies ? true : false;
}

void QCefSetting::setPersistUserPreferences(bool enabled)
{
	CCefSetting::initializeInstance();
	CCefSetting::persist_user_preferences = enabled ? TRUE : FALSE;
}

const bool QCefSetting::persistUserPreferences()
{
	CCefSetting::initializeInstance();
	return CCefSetting::persist_user_preferences ? true : false;
}

void QCefSetting::setLocale(const QString& locale)
{
	CCefSetting::initializeInstance();
	CCefSetting::locale.FromString(locale.toStdString());
}

const QString QCefSetting::locale()
{
	CCefSetting::initializeInstance();
	return QString::fromStdString(
		CCefSetting::locale.ToString());
}

void QCefSetting::setRemoteDebuggingPort(int port)
{
	CCefSetting::initializeInstance();
	CCefSetting::remote_debugging_port = port;
}

const int QCefSetting::remoteDebuggingPort()
{
	CCefSetting::initializeInstance();
	return CCefSetting::remote_debugging_port;
}

void QCefSetting::setBackgroundColor(const QColor& color)
{
	CCefSetting::initializeInstance();
	CCefSetting::background_color = static_cast<cef_color_t>(color.rgba());
}

const QColor QCefSetting::backgroundColor()
{
	CCefSetting::initializeInstance();
	return QColor::fromRgba(static_cast<QRgb>(CCefSetting::background_color));
}

void QCefSetting::setAcceptLanguageList(const QString& languages)
{
	CCefSetting::initializeInstance();
	CCefSetting::accept_language_list.FromString(languages.toStdString());
}

const QString QCefSetting::acceptLanguageList()
{
	CCefSetting::initializeInstance();
	return QString::fromStdString(
		CCefSetting::accept_language_list.ToString());
}
