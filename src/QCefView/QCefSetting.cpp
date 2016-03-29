#include "stdafx.h"
#include "inc/QCefSetting.h"
#include "CCefSetting.h"

void QCefSetting::setBrowserSubProcessPath(const QString& path)
{
	CCefSetting::browser_sub_process_path.FromString(path.toStdString());
}

const QString QCefSetting::browserSubProcessPath()
{
	return QString::fromStdString(
		CCefSetting::browser_sub_process_path.ToString());
}

void QCefSetting::setResourceDirectoryPath(const QString& path)
{
	CCefSetting::resource_directory_path.FromString(path.toStdString());
}

const QString QCefSetting::resourceDirectoryPath()
{
	return QString::fromStdString(
		CCefSetting::resource_directory_path.ToString());
}

void QCefSetting::setLocalesDirectoryPath(const QString& path)
{
	CCefSetting::locales_directory_path.FromString(path.toStdString());
}

const QString QCefSetting::localesDirectoryPath()
{
	return QString::fromStdString(
		CCefSetting::locales_directory_path.ToString());
}

void QCefSetting::setUserAgent(const QString& agent)
{
	CCefSetting::user_agent.FromString(agent.toStdString());
}

const QString QCefSetting::userAgent()
{
	return QString::fromStdString(
		CCefSetting::user_agent.ToString());
}
