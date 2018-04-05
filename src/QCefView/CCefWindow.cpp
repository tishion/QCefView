#pragma region qt_headers
#include <QCoreApplication>
#include <QResizeEvent>
#include <QPaintDevice>
#include <QPainter>
#pragma endregion qt_headers

#include "CCefWindow.h"
#include "CCefManager.h"

#define CEF_BROWSER_WINDOW_CLASS_NAME_A "CefBrowserWindow"

CCefWindow::CCefWindow(QWindow* parent /*= 0*/)
  : QWindow(parent)
  , hwndCefBrowser_(nullptr)
{
  setFlags(Qt::FramelessWindowHint);

  CCefManager::getInstance().initializeCef();
}

CCefWindow::~CCefWindow()
{
  destroy();

  if (hwndCefBrowser_)
    hwndCefBrowser_ = nullptr;

  CCefManager::getInstance().uninitializeCef();
}

void
CCefWindow::setCefBrowserWindow(CefWindowHandle wnd)
{
  hwndCefBrowser_ = wnd;
  syncCefBrowserWindow();
}

void
CCefWindow::syncCefBrowserWindow()
{
  if (hwndCefBrowser_)
    ::MoveWindow(hwndCefBrowser_, 0, 0, width(), height(), TRUE);
}

void
CCefWindow::exposeEvent(QExposeEvent* e)
{
  syncCefBrowserWindow();
  return __super::exposeEvent(e);
}

void
CCefWindow::resizeEvent(QResizeEvent* e)
{
  syncCefBrowserWindow();
  return __super::resizeEvent(e);
}
