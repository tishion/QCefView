#include "stdafx.h"

#pragma region cef_headers
#include <include/cef_app.h>
#pragma endregion cef_headers

#pragma region project_heasers
#include "CefViewRenderApp/QCefViewRenderApp.h"
#include "qtcefwing.h"
#pragma endregion project_heasers

int APIENTRY _tWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR lpCmdLine,
	_In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	CefRefPtr<QCefViewRenderApp> app(new QCefViewRenderApp);
	CefMainArgs main_args(hInstance);
	void* sandboxInfo = NULL;
	int exit_code = CefExecuteProcess(
		main_args, app.get(), sandboxInfo);
	if (exit_code >= 0)
	{
		return exit_code;
	}
	return 0;
}