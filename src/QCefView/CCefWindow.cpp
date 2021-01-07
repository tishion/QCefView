#pragma region qt_headers
#include <QCoreApplication>
#include <QResizeEvent>
#include <QPaintDevice>
#include <QPainter>
#include <QDebug>
#pragma endregion qt_headers

#include "CCefWindow.h"
#include "CCefManager.h"

#define CEF_BROWSER_WINDOW_CLASS_NAME_A "CefBrowserWindow"

QHash<CefWindowHandle, CCefWindow*> CCefWindow::instanceMap_;

QMutex CCefWindow::instanceMtx_;

CCefWindow*
CCefWindow::lookupInstance(CefWindowHandle wnd)
{
  QMutexLocker locker(&instanceMtx_);
  return instanceMap_[wnd];
}

CCefWindow::CCefWindow(QWindow* parent /*= 0*/)
  : QWindow(parent)
  , hwndCefBrowser_(nullptr)
{
  setFlags(Qt::FramelessWindowHint);

  CCefManager::getInstance().initializeCef();
}

CCefWindow::~CCefWindow()
{
  if (hwndCefBrowser_)
    hwndCefBrowser_ = nullptr;

  CCefManager::getInstance().uninitializeCef();
}

void
CCefWindow::setCefBrowserWindow(CefWindowHandle wnd)
{
  hwndCefBrowser_ = wnd;
  syncCefBrowserWindow();

  {
    QMutexLocker locker(&instanceMtx_);
    instanceMap_[wnd] = this;
  }
}

void
CCefWindow::syncCefBrowserWindow()
{
  double w = width() * devicePixelRatio();
  double h = height() * devicePixelRatio();
  if (hwndCefBrowser_)
    ::SetWindowPos(hwndCefBrowser_, NULL, 0, 0, w, h, SWP_NOZORDER | SWP_NOSENDCHANGING | SWP_DEFERERASE);
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
  __super::resizeEvent(e);

  return;
}
