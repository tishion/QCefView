#pragma once
#include <QWindow>
#include <QPointer>

#include <include/cef_app.h>

#include "inc/QCefView.h"
#include "CefViewBrowserApp/QCefViewBrowserApp.h"
#include "CefViewBrowserApp/QCefViewBrowserHandler.h"

class CCefWindow :
	public QWindow
{
	Q_OBJECT
public:
	explicit CCefWindow(const QString& url, QCefView* host, QWindow *parent = 0);
	~CCefWindow();

	static QPointer<QCefView> GetHostWidget(HWND h);

	const CefRefPtr<QCefViewBrowserHandler>& cefViewHandler() const;

protected:
	virtual void exposeEvent(QExposeEvent *e);
	virtual void resizeEvent(QResizeEvent *e);

public:
	operator HWND();

private:
	QPointer<QCefView> host_;

	HWND hwndCefBrowser_;
	CefRefPtr<QCefViewBrowserHandler> handler_;

	typedef std::map<HWND, QPointer<QCefView>> HostWidgetInstanceMap;
	static HostWidgetInstanceMap instance_map_;
};

