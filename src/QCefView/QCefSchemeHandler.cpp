#pragma region qt_headers
#pragma endregion qt_headers

#pragma region cef_headers
#include <include/cef_app.h>
#include <include/wrapper/cef_message_router.h>
#pragma endregion cef_headers

#include "Include/QCefSchemeHandler.h"

//////////////////////////////////////////////////////////////////////////
QCefSchemeHandler::QCefSchemeHandler()
{}

QCefSchemeHandler::~QCefSchemeHandler()
{}

bool
QCefSchemeHandler::Skip(const int bytesToSkip)
{
  return false;
}

void
QCefSchemeHandler::Close()
{}
