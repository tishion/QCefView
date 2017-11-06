#include "stdafx.h"
#include "inc/QCefSetting.h"
#include "CCefSetting.h"

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
