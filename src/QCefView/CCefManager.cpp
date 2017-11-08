#include "stdafx.h"

#pragma region cef_headers
#include <include/cef_sandbox_win.h>
#pragma endregion cef_headers

#include "CCefManager.h"
#include "CCefSetting.h"

CCefManager::CCefManager()
{
	nBrowserRefCount_ = 0;

}

CCefManager& CCefManager::getInstance()
{
	static CCefManager s_instance;
	return s_instance;
}

void CCefManager::initializeCef()
{
	// This is not the first time initialization
	if (++nBrowserRefCount_ > 1)
		return;

	// This is the first time initialization
	CCefSetting::initializeInstance();

	CefString(&cef_settings_.browser_subprocess_path)
		= CCefSetting::browser_sub_process_path;
	CefString(&cef_settings_.resources_dir_path)
		= CCefSetting::resource_directory_path;
	CefString(&cef_settings_.locales_dir_path)
		= CCefSetting::locales_directory_path;

	::CefString(&cef_settings_.user_agent)
		= CCefSetting::user_agent;

	CefString(&cef_settings_.cache_path)
		= CCefSetting::cache_path;
	CefString(&cef_settings_.user_data_path)
		= CCefSetting::user_data_path;
	CefString(&cef_settings_.locale)
		= CCefSetting::locale;
	CefString(&cef_settings_.accept_language_list)
		= CCefSetting::accept_language_list;

	cef_settings_.persist_session_cookies = CCefSetting::persist_session_cookies;
	cef_settings_.persist_user_preferences = CCefSetting::persist_user_preferences;
	cef_settings_.remote_debugging_port = CCefSetting::remote_debugging_port;
	cef_settings_.background_color = CCefSetting::background_color;

	cef_settings_.multi_threaded_message_loop = TRUE;

#ifndef NDEBUG
	cef_settings_.log_severity = LOGSEVERITY_DEFAULT;
	cef_settings_.remote_debugging_port = 7777;
#else
	cef_settings_.log_severity = LOGSEVERITY_DISABLE;
#endif

	app_ = new QCefViewBrowserApp();

	HINSTANCE hInstance = ::GetModuleHandle(nullptr);
	CefMainArgs main_args(hInstance);

	// Initialize CEF.
	void* sandboxInfo = nullptr;
	if (CefInitialize(main_args, cef_settings_, app_.get(), sandboxInfo))
		__noop(_T("CefManager"), _T("Failed at CefInitialize"));
}

void CCefManager::uninitializeCef()
{
	// This is not the last time release
	if (--nBrowserRefCount_ > 0)
		return;

	// The last time release 
	releaseCef();
	app_ = nullptr;
}

void CCefManager::releaseCef()
{
	CefShutdown();
}