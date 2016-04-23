#include "stdafx.h"
#pragma region qt_headers
#include <QCoreApplication>
#include <QResizeEvent>
#include <QPaintDevice>
#include <QPainter>
#pragma endregion qt_headers

#include "CCefManager.h"
#include "CCefWindow.h"

#define CEF_BROWSER_WINDOW_CLASS_NAME_A "CefBrowserWindow"

CCefWindow::HostWidgetInstanceMap CCefWindow::instance_map_;
QPointer<QCefView> CCefWindow::GetHostWidget(HWND h)
{
	auto it = instance_map_.find(h);
	if (it != instance_map_.end())
	{
		return it->second;
	}
	return QPointer<QCefView>();
}

CCefWindow::CCefWindow(const QString& url, QCefView* host, QWindow *parent /*= 0*/)
	: QWindow(parent)
	, pQCefViewWidget_(host)
	, hwndCefBrowser_(NULL)
	, pQCefViewHandler(NULL)
{
	CCefManager::getInstance().AddBrowserRefCount();

	setFlags(Qt::FramelessWindowHint);
	
	// Create native window
	create();

	// Set window info
	CefWindowInfo window_info;
	RECT rc = { 0 };
	window_info.SetAsChild((HWND)winId(), rc);

	CefBrowserSettings browserSettings;
	browserSettings.plugins = STATE_DISABLED;	// disable all plugins

	pQCefViewHandler = new QCefViewBrowserHandler(host);
	instance_map_[(HWND)winId()] = pQCefViewWidget_;

	// Create the main browser window.
	if (!CefBrowserHost::CreateBrowser(
		window_info,			// window info
		pQCefViewHandler.get(),	// handler
		url.toStdString(),		// url
		browserSettings,		// settings
		NULL))
	{
		QLOG() << QStringLiteral("Failed to create browser.");
	}
}

CCefWindow::~CCefWindow()
{
	pQCefViewWidget_ = NULL;

	auto it = instance_map_.find((HWND)winId());
	if (it != instance_map_.end())
	{
		instance_map_.erase(it);
	}

	destroy();
	
	if (hwndCefBrowser_)
	{
		hwndCefBrowser_ = NULL;
	}

	if (pQCefViewHandler)
	{
		pQCefViewHandler = NULL;
	}

	CCefManager::getInstance().ReleaseBrowserRefCount();
}

void CCefWindow::updateCefBrowserWindow()
{
	if (!hwndCefBrowser_)
	{
		hwndCefBrowser_ = ::FindWindowExA((HWND)winId(),
			NULL, CEF_BROWSER_WINDOW_CLASS_NAME_A, NULL);
	}

	if (hwndCefBrowser_)
	{
		::MoveWindow(hwndCefBrowser_, 0, 0,
			width(), height(), TRUE);
	}
}

void CCefWindow::exposeEvent(QExposeEvent *e)
{
	updateCefBrowserWindow();
	return __super::exposeEvent(e);
}

void CCefWindow::resizeEvent(QResizeEvent *e)
{
	updateCefBrowserWindow();
	return __super::resizeEvent(e);
}

CCefWindow::operator HWND()
{
	return (HWND)winId();
}

const CefRefPtr<QCefViewBrowserHandler>& CCefWindow::cefViewHandler() const
{
	return pQCefViewHandler;
}


