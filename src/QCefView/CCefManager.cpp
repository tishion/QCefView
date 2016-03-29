#include "stdafx.h"

#pragma region cef_headers
#include <include/cef_sandbox_win.h>
#pragma endregion cef_headers

#include "CCefManager.h"
#include "CCefSetting.h"

#define CEF_AIO_FOLDER_NAME		_T("cef")
#define CEF_RENDER_PROCESS_NAME	_T("qtcefwing.exe")
#define CEF_PAKRES_FOLDER_NAME	_T("resources")
#define CEF_LOCALES_FOLDER_NAME	_T("locales")

CCefManager::CCefManager()
{
	nBrowserRefCount_ = 0;

}

CCefManager::~CCefManager()
{
}

void CCefManager::releaseCef()
{
	CefShutdown();
}

CCefManager& CCefManager::getInstance()
{
	static CCefManager s_instance;
	return s_instance;
}

void CCefManager::AddBrowserRefCount()
{
	if (++nBrowserRefCount_ == 1)
	{
		CCefSetting::initializeInstance();

		CefString(&cef_settings_.browser_subprocess_path)
			= CCefSetting::browser_sub_process_path;
		CefString(&cef_settings_.resources_dir_path) 
			= CCefSetting::resource_directory_path;
		CefString(&cef_settings_.locales_dir_path) 
			= CCefSetting::locales_directory_path;

		::CefString(&cef_settings_.user_agent)
			= CCefSetting::user_agent;

		cef_settings_.multi_threaded_message_loop = TRUE;

#ifndef NDEBUG
		cef_settings_.log_severity = LOGSEVERITY_DEFAULT;
		cef_settings_.remote_debugging_port = 8080;
#else
		cef_settings_.log_severity = LOGSEVERITY_DISABLE;
#endif

		app_ = new QCefViewBrowserApp();

		HINSTANCE hInstance = ::GetModuleHandle(NULL);
		CefMainArgs main_args(hInstance);

		// Initialize CEF.
		void* sandboxInfo = NULL;
		if (CefInitialize(main_args, cef_settings_, app_.get(), sandboxInfo))
		{
			// log
			__noop(_T("CefManager"), _T("Failed at CefInitialize"));
		}
	}
}

void CCefManager::ReleaseBrowserRefCount()
{
	if (--nBrowserRefCount_ == 0)
	{
		releaseCef();
		app_ = NULL;
	}
}