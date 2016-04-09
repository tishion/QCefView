#include "stdafx.h"
#pragma region qt_headers
#include <QVBoxLayout>
#include <QWindow>
#include <QResizeEvent>
#include <QVariant>
#pragma endregion qt_headers

#pragma region cef_headers
#include <include/cef_app.h>
#include <include/cef_browser.h>
#include <include/cef_frame.h>
#include <include/cef_sandbox_win.h>
#pragma endregion cef_headers

#include "inc/QCefQuery.h"
#include "inc/QCefView.h"
#include "inc/QCefEvent.h"
#include "CCefManager.h"
#include "CCefWindow.h"

//////////////////////////////////////////////////////////////////////////
QCefView::QCefView(const QString url, QWidget* parent /*= 0*/)
	: QWidget(parent)
	, cefWindow_(NULL)
{
	QGridLayout* layout = new QGridLayout;
	layout->setContentsMargins(0, 0, 0, 0);

	/*
	 * Here we must create a QWidget as a wrapper 
	 * to encapsulate the QWindow
	 */
	cefWindow_ = new CCefWindow(url, this, window()->windowHandle());
	QWidget* windowContainer = createWindowContainer(cefWindow_, this);
	if (windowContainer)
	{
		layout->addWidget(windowContainer);
	}

	setLayout(layout);
}

QCefView::~QCefView()
{

}

void QCefView::processQCefUrlRequest(const QString& url)
{

}

void QCefView::processQCefQueryRequest(QCefQuery query)
{

}

void QCefView::onInvokeMethodNotify(
	int browserId, 
	int frameId, 
	const QString method,
	const QVariantList arguments)
{

}

void QCefView::navigateToString(const QString& content, const QString& url)
{
	if (cefWindow_)
	{
		CefString strContent;
		strContent.FromString(content.toStdString());
		CefString strUrl;
		strUrl.FromString(url.toStdString());
		cefWindow_->cefViewHandler()->GetBrowser()->GetMainFrame()->LoadString(strContent, strUrl);
	}
}

void QCefView::navigateToUrl(const QString& url)
{
	if (cefWindow_)
	{
		CefString strUrl;
		strUrl.FromString(url.toStdString());
		cefWindow_->cefViewHandler()->GetBrowser()->GetMainFrame()->LoadURL(strUrl);
	}
}

bool QCefView::browserCanGoBack()
{
	if (cefWindow_)
	{
		return cefWindow_->cefViewHandler()->GetBrowser()->CanGoBack();
	}
	return false;
}

bool QCefView::browserCanGoForward()
{
	if (cefWindow_)
	{
		return cefWindow_->cefViewHandler()->GetBrowser()->CanGoForward();
	}
	return false;
}

void QCefView::browserGoBack()
{
	if (cefWindow_)
	{
		cefWindow_->cefViewHandler()->GetBrowser()->GoBack();
	}
}

void QCefView::browserGoForward()
{
	if (cefWindow_)
	{
		cefWindow_->cefViewHandler()->GetBrowser()->CanGoForward();
	}
}

bool QCefView::browserIsLoading()
{
	if (cefWindow_)
	{
		return cefWindow_->cefViewHandler()->GetBrowser()->IsLoading();
	}
	return false;
}

void QCefView::browserReload()
{
	if (cefWindow_)
	{
		cefWindow_->cefViewHandler()->GetBrowser()->Reload();
	}
}

void QCefView::browserStopLoad()
{
	if (cefWindow_)
	{
		cefWindow_->cefViewHandler()->GetBrowser()->StopLoad();
	}
}

bool QCefView::triggerEvent(int frameId, const QString& name, const QCefEvent& event)
{
	if (!name.isEmpty())
	{
		if (cefWindow_)
		{
			auto frame = cefWindow_->cefViewHandler()->GetBrowser()->GetFrame(frameId);
			if (frame)
			{
				return sendEVentNotifyMessage(frameId, name, event);
			}
		}
	}

	return false;
}

bool QCefView::broadcastEvent(const QString& name, const QCefEvent& event)
{
	if (!name.isEmpty())
	{
		if (cefWindow_)
		{
			return sendEVentNotifyMessage(0, name, event);
		}
	}
	return false;
}

void QCefView::onLoadStateChange(bool isLoading)
{

}

void QCefView::onLoadStart()
{

}

void QCefView::onLoadEnd(int httpStatusCode)
{

}

void QCefView::onLoadError(int errorCode,
	const QString& errorMsg,
	const QString& failedUrl)
{

}

WId QCefView::getCefWinId()
{
	return (WId)(HWND)(*cefWindow_);
}

void QCefView::notifyMoveOrResizeStarted()
{
	if (cefWindow_)
	{
		CefRefPtr<QCefViewBrowserHandler> handler = cefWindow_->cefViewHandler();
		if (handler)
		{
			CefRefPtr<CefBrowser> browser = handler->GetBrowser();
			if (browser)
			{
				CefRefPtr<CefBrowserHost> host = browser->GetHost();
				if (host)
				{
					host->NotifyMoveOrResizeStarted();
				}
			}
		}
	}
}

bool QCefView::sendEVentNotifyMessage(int frameId, const QString& name, const QCefEvent& event)
{
	CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(
		TRIGGEREVENT_NOTIFY_MESSAGE);
	CefRefPtr<CefListValue> arguments = msg->GetArgumentList();

	int idx = 0;
	arguments->SetInt(idx++, frameId);

	CefString eventName = name.toStdString();
	arguments->SetString(idx++, eventName);

	CefRefPtr<CefDictionaryValue> dict = CefDictionaryValue::Create();

	CefString cefStr;
	cefStr.FromWString(event.objectName().toStdWString());
	dict->SetString("name", cefStr);

	QList<QByteArray> keys = event.dynamicPropertyNames();
	for (QByteArray key : keys)
	{
		QVariant value = event.property(key.data());
		if (value.type() == QMetaType::Bool)
		{
			dict->SetBool(key.data(), value.toBool());
		}
		else if (value.type() == QMetaType::Int || value.type() == QMetaType::UInt)
		{
			dict->SetInt(key.data(), value.toInt());
		}
		else if (value.type() == QMetaType::Double)
		{
			dict->SetDouble(key.data(), value.toDouble());
		}
		else if (value.type() == QMetaType::QString)
		{
			cefStr.FromWString(value.toString().toStdWString());
			dict->SetString(key.data(), cefStr);
		}
		else
		{
			__noop(_T("QCefView"), _T("Unknow Type!"));
		}
	}

	arguments->SetDictionary(idx++, dict);

	return cefWindow_->cefViewHandler()->TriggerEvent(msg);
}
