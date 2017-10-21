#ifndef QCEFVIEW_H
#define QCEFVIEW_H
#pragma once

#pragma region std_headers
#include <memory>
#pragma endregion std_headers

#pragma region qt_headers
#include <QtCore/qglobal.h>
#include <QWidget>
#include <QVariantList>
#pragma endregion qt_headers

#include "QCefQuery.h"
#include "QCefEvent.h"

#ifdef QCEFVIEW_LIB
#define QCEFVIEW_EXPORT Q_DECL_EXPORT
#else
#define QCEFVIEW_EXPORT Q_DECL_IMPORT
#pragma comment(lib, "QCefView.lib")
#endif

/** Outline of QCefView:
 **
 **		+--------------------------------------------------------------+
 **		| QCefView(QWidget)                                            |
 **		|  						                                       |
 **		|    +----------------------------------------------------+    |
 **		|    | WindowWrapper(QWidget)                             |    |
 **		|    |                                                    |    |
 **		|    |    +-------------------------------------------+   |    |
 **		|    |	  | CefWindow(QWindow)                        |   |    |
 **		|    |	  |					                          |   |    |
 **		|    |	  |					                          |   |    |
 **		|    |	  |					                          |   |    |
 **		|    |	  +-------------------------------------------+   |    |
 **		|    |                                                    |    |
 **		|    +----------------------------------------------------+    |
 **		|                                                              |
 **		+--------------------------------------------------------------+
 **
 **	Remarks:
 **		The WindowWrapper and CefWindow are transparent to upper layer user.
 **
 **/

/// <summary>
/// 
/// </summary>
class QCEFVIEW_EXPORT QCefView
	: public QWidget
{
	/// <summary>
	/// 
	/// </summary>
	Q_OBJECT

public:
	/// <summary>
	/// 
	/// </summary>
	QCefView(const QString url, QWidget* parent = 0);

	/// <summary>
	/// 
	/// </summary>
	~QCefView();

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	WId getCefWinId();

	/// <summary>
	/// Navigates to the content.
	/// </summary>
	/// <param name="content"></param>
	/// <param name="url"></param>
	void navigateToString(const QString& content, const QString& url);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="url"></param>
	void navigateToUrl(const QString& url);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool browserCanGoBack();

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool browserCanGoForward();

	/// <summary>
	/// 
	/// </summary>
	void browserGoBack();

	/// <summary>
	/// 
	/// </summary>
	void browserGoForward();

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool browserIsLoading();

	/// <summary>
	/// 
	/// </summary>
	void browserReload();

	/// <summary>
	/// 
	/// </summary>
	void browserStopLoad();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="frameId"></param>
	/// <param name="name"></param>
	/// <param name="event"></param>
	/// <returns></returns>
	bool triggerEvent(int frameId, const QString& name, const QCefEvent& event);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="name"></param>
	/// <param name="event"></param>
	/// <returns></returns>
	bool broadcastEvent(const QString& name, const QCefEvent& event);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="query"></param>
	/// <returns></returns>
	bool responseQCefQuery(const QCefQuery& query);

protected:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="event"></param>
	virtual void changeEvent(QEvent * event) override;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="watched"></param>
	/// <param name="event"></param>
	/// <returns></returns>
	virtual bool eventFilter(QObject *watched, QEvent *event) override;

protected slots:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="isLoading"></param>
	/// <param name="canGoBack"></param>
	/// <param name="canGoForward"></param>
	virtual void onLoadingStateChanged(bool isLoading, bool canGoBack, bool canGoForward);

	/// <summary>
	/// 
	/// </summary>
	virtual void onLoadStart();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="httpStatusCode"></param>
	virtual void onLoadEnd(int httpStatusCode);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="errorCode"></param>
	/// <param name="errorMsg"></param>
	/// <param name="failedUrl"></param>
	virtual void onLoadError(int errorCode, const QString& errorMsg, const QString& failedUrl);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="url"></param>
	virtual void onQCefUrlRequest(const QString& url);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="query"></param>
	virtual void onQCefQueryRequest(const QCefQuery& query);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="browserId"></param>
	/// <param name="frameId"></param>
	/// <param name="method"></param>
	/// <param name="arguments"></param>
	virtual void onInvokeMethodNotify(int browserId, int frameId, const QString& method, const QVariantList& arguments);

private:
	/// <summary>
	/// 
	/// </summary>
	class Implementation;
	std::unique_ptr<Implementation> pImpl_;
};

#endif // QCEFVIEW_H
