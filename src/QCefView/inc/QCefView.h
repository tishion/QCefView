#ifndef QCEFVIEW_H
#define QCEFVIEW_H
#pragma once

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
 **		| QCefView(QWidget)                                          |
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
 **		The WindowWrapper and CefWindow are transparent
 **		to upper layer user.
 **
 **/

class CCefWindow;
class QCEFVIEW_EXPORT QCefView
	: public QWidget
{
	Q_OBJECT

protected slots:
	//************************************
	// Method:    processQCefUrlRequest
	// FullName:  QCefView::processQCefUrlRequest
	// Access:    virtual protected private 
	// Returns:   void
	// Qualifier:
	// Parameter: const QString & url
	// 
	// Remarks:
	//		this method is always called in the Qt Main UI Thread 
	//************************************
	virtual void processQCefUrlRequest(const QString& url);

	//************************************
	// Method:    processQCefQueryRequest
	// FullName:  QCefView::processQCefQueryRequest
	// Access:    virtual protected 
	// Returns:   void
	// Qualifier:
	// Parameter: QCefQuery reqeust
	// 
	// Remarks:
	//		this method is always called in the Qt Main UI thread.(event loop)
	//************************************
	virtual void processQCefQueryRequest(const QCefQuery& query);

	//************************************
	// Method:    onInvokeMethodNotify
	// FullName:  QCefView::onInvokeMethodNotify
	// Access:    virtual protected private 
	// Returns:   void
	// Qualifier:
	// Parameter: int browserId
	// Parameter: int frameId
	// Parameter: const QString method
	// Parameter: const QVariantList arguments
	//************************************
	virtual void onInvokeMethodNotify(
		int browserId,
		int frameId,
		const QString method,
		const QVariantList arguments);

public:
	QCefView(const QString url, QWidget* parent = 0);
	~QCefView();

	/**navigate to the content
	 **	content:
	 **		HTML content
	 **	url:
	 **		this url is just use to display
	 **
	 **/
	void navigateToString(const QString& content, const QString& url);

	/**navigate the browser to URL
	 **	url:
	 **		target address
	 **
	 **/
	void navigateToUrl(const QString& url);

	/**can the browser go back to previous page.
	 **
	 **/
	bool browserCanGoBack();

	/**can the browser go forward to the next page
	 **
	 **/
	bool browserCanGoForward();

	/**go back to the previous page
	 **
	 **/
	void browserGoBack();

	/**go forward to the next page
	 **
	 **/
	void browserGoForward();

	/**is browser busy loading content
	 **
	 **/
	bool browserIsLoading();

	/**reload the current page
	 **
	 **/
	void browserReload();

	/**stop current loading
	 **
	 **/
	void browserStopLoad();

	bool triggerEvent(int frameId, const QString& name, const QCefEvent& event);

	bool broadcastEvent(const QString& name, const QCefEvent& event);

	/**called when the browser loading state changed
	 **	isLoading:
	 **		if isLoading is true, means that the browser
	 **		is going to load contents, else means loading
	 **		operation is going to be done
	 **/
	virtual void onLoadStateChange(bool isLoading);

	/**called when the loading operation is started
	 **
	 **/
	virtual void onLoadStart();

	/**called when the loading operation is done successfully
	 **
	 **/
	virtual void onLoadEnd(int httpStatusCode);

	/**called when the loading operation is failed
	 **
	 **/
	virtual void onLoadError(int errorCode,
		const QString& errorMsg,
		const QString& failedUrl);

	WId getCefWinId();

protected:
	void notifyMoveOrResizeStarted();

	bool sendEVentNotifyMessage(int frameId,
		const QString& name,
		const QCefEvent& event);

private:
	friend class QCefQuery;
	bool responseQCefQuery(int64_t query, 
		bool success, const QString& response, int error);

private:
	QPointer<CCefWindow> pCefWindow_;
};

#endif // QCEFVIEW_H
