#ifdef _WIN32
#pragma region windows_headers
#include <tchar.h>
#include <windows.h>
#pragma endregion windows_headers
#endif

#pragma region cef_headers
#include <include/cef_app.h>
#pragma endregion cef_headers

#pragma region project_heasers
#include "CefViewRenderApp/QCefViewRenderApp.h"
#include "QCefWing.h"
#pragma endregion project_heasers

#ifdef _WIN32
int APIENTRY
_tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  CefEnableHighDPISupport();

  CefRefPtr<QCefViewRenderApp> app(new QCefViewRenderApp);
  CefMainArgs main_args(hInstance);
  void* sandboxInfo = nullptr;
  return CefExecuteProcess(main_args, app, sandboxInfo);
}
#else  // _WIN32
int
main(int argc, char* argv[])
{
  CefEnableHighDPISupport();

  CefRefPtr<QCefViewRenderApp> app(new QCefViewRenderApp);
  CefMainArgs main_args();
  void* sandboxInfo = nullptr;
  return CefExecuteProcess(main_args, app.get(), sandboxInfo);
}
#endif // _WIN32
