#pragma once

#include <include\cef_base.h>

class CCefSetting
{
public:
	static CefString browser_sub_process_path;
	static CefString resource_directory_path;
	static CefString locales_directory_path;
	static CefString user_agent;

protected:
	CCefSetting();
	~CCefSetting();
};

