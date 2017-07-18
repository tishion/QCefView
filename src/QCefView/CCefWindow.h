#pragma once

#pragma region qt_headers
#include <QWindow>
#include <QPointer>
#pragma endregion qt_headers

#pragma region cef_headers
#include <include/cef_app.h>
#pragma endregion cef_headers

#include "../inc/QCefQuery.h"

/// <summary>
/// 
/// </summary>
class CCefWindow : public QWindow
{
	Q_OBJECT

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="parent"></param>
	explicit CCefWindow(QWindow *parent = 0);

	/// <summary>
	/// 
	/// </summary>
	~CCefWindow();

signals:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="isLoading"></param>
	/// <param name="canGoBack"></param>
	/// <param name="canGoForward"></param>
	void loadingStateChanged(bool isLoading, bool canGoBack, bool canGoForward);

	/// <summary>
	/// 
	/// </summary>
	void loadStart();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="httpStatusCode"></param>
	void loadEnd(int httpStatusCode);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="errorCode"></param>
	/// <param name="errorMsg"></param>
	/// <param name="failedUrl"></param>
	void loadError(int errorCode, const QString& errorMsg, const QString& failedUrl);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="url"></param>
	void processUrlRequest(const QString& url);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="query"></param>
	void processQueryRequest(const QCefQuery& query);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="browserId"></param>
	/// <param name="frameId"></param>
	/// <param name="method"></param>
	/// <param name="arguments"></param>
	void invokeMethodNotify(int browserId, int frameId, const QString method, const QVariantList arguments);

public:
	/// <summary>
	/// 
	/// </summary>
	void updateCefBrowserWindow();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="e"></param>
	virtual void exposeEvent(QExposeEvent *e);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="e"></param>
	virtual void resizeEvent(QResizeEvent *e);

private:
	/// <summary>
	/// 
	/// </summary>
	HWND	hwndCefBrowser_;
};

