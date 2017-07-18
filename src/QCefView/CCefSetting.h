#pragma once

#pragma region cef_headers
#include <include\cef_base.h>
#pragma endregion cef_headers

/// <summary>
/// 
/// </summary>
class CCefSetting
{
protected:
	/// <summary>
	/// 
	/// </summary>
	CCefSetting();

	/// <summary>
	/// 
	/// </summary>
	~CCefSetting() {};

public:
	/// <summary>
	/// 
	/// </summary>
	static void initializeInstance();

public:
	/// <summary>
	/// 
	/// </summary>
	static CefString browser_sub_process_path;

	/// <summary>
	/// 
	/// </summary>
	static CefString resource_directory_path;

	/// <summary>
	/// 
	/// </summary>
	static CefString locales_directory_path;

	/// <summary>
	/// 
	/// </summary>
	static CefString user_agent;
};

