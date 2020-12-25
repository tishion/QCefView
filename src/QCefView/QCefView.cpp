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
#include <include/cef_parser.h>
#include <include/cef_sandbox_win.h>
#pragma endregion cef_headers

#include <QCefProtocol.h>

#include "Include/QCefQuery.h"
#include "Include/QCefView.h"
#include "Include/QCefEvent.h"
#include "CCefWindow.h"
#include "CefViewBrowserApp/QCefViewBrowserHandler.h"

//////////////////////////////////////////////////////////////////////////
class QCefView::Implementation
{
public:
  explicit Implementation(const QString& url, QWindow* parent)
    : pCefWindow_(nullptr)
    , pQCefViewHandler_(nullptr)
  {
    // Here we must create a QWidget as a wrapper to encapsulate the QWindow
    pCefWindow_ = new CCefWindow(parent);
    pCefWindow_->create();

    // Set window info
    CefWindowInfo window_info;
    RECT rc = { 0 };
    window_info.SetAsChild((HWND)pCefWindow_->winId(), rc);

    CefBrowserSettings browserSettings;
    browserSettings.plugins = STATE_DISABLED; // disable all plugins

    // Create the browser
    pQCefViewHandler_ = new QCefViewBrowserHandler(pCefWindow_);

    // Create the main browser window.
    if (!CefBrowserHost::CreateBrowser(window_info,       // window info
                                       pQCefViewHandler_, // handler
                                       url.toStdString(), // url
                                       browserSettings,   // settings
                                       nullptr,
                                       CefRequestContext::GetGlobalContext())) {
      throw std::exception("Failed to create browser.");
    }
  }

  ~Implementation()
  {
    if (pQCefViewHandler_) {
      // Wait for all browser to close
      pQCefViewHandler_->CloseAllBrowsers(true);
      pQCefViewHandler_ = nullptr;
    }
  }

  void closeAllBrowsers() {}

  CCefWindow* cefWindow() { return pCefWindow_; }

  WId getCefWinId()
  {
    if (pCefWindow_)
      return pCefWindow_->winId();

    return 0;
  }

  void navigateToString(const QString& content)
  {
    if (pQCefViewHandler_) {
      std::string data = content.toStdString();
      data = CefURIEncode(CefBase64Encode(data.c_str(), data.size()), false).ToString();
      data = "data:text/html;base64," + data;
      pQCefViewHandler_->GetBrowser()->GetMainFrame()->LoadURL(data);
    }
  }

  void navigateToUrl(const QString& url)
  {
    if (pQCefViewHandler_) {
      CefString strUrl;
      strUrl.FromString(url.toStdString());
      pQCefViewHandler_->GetBrowser()->GetMainFrame()->LoadURL(strUrl);
    }
  }

  bool browserCanGoBack()
  {
    if (pQCefViewHandler_)
      return pQCefViewHandler_->GetBrowser()->CanGoBack();

    return false;
  }

  bool browserCanGoForward()
  {
    if (pQCefViewHandler_)
      return pQCefViewHandler_->GetBrowser()->CanGoForward();

    return false;
  }

  void browserGoBack()
  {
    if (pQCefViewHandler_)
      pQCefViewHandler_->GetBrowser()->GoBack();
  }

  void browserGoForward()
  {
    if (pQCefViewHandler_)
      pQCefViewHandler_->GetBrowser()->GoForward();
  }

  bool browserIsLoading()
  {
    if (pQCefViewHandler_)
      return pQCefViewHandler_->GetBrowser()->IsLoading();

    return false;
  }

  void browserReload()
  {
    if (pQCefViewHandler_)
      pQCefViewHandler_->GetBrowser()->Reload();
  }

  void browserStopLoad()
  {
    if (pQCefViewHandler_)
      pQCefViewHandler_->GetBrowser()->StopLoad();
  }

  bool triggerEvent(const QString& name, const QCefEvent& event, int frameId = QCefViewBrowserHandler::MAIN_FRAME)
  {
    if (!name.isEmpty()) {
      return sendEventNotifyMessage(frameId, name, event);
    }

    return false;
  }

  bool responseQCefQuery(const QCefQuery& query)
  {
    if (pQCefViewHandler_) {
      CefString res;
      res.FromString(query.response().toStdString());
      return pQCefViewHandler_->ResponseQuery(query.id(), query.result(), res, query.error());
    }
    return false;
  }

  void notifyMoveOrResizeStarted()
  {
    if (pQCefViewHandler_) {
      CefRefPtr<CefBrowser> browser = pQCefViewHandler_->GetBrowser();
      if (browser) {
        CefRefPtr<CefBrowserHost> host = browser->GetHost();
        if (host)
          host->NotifyMoveOrResizeStarted();
      }
    }
  }

  bool sendEventNotifyMessage(int frameId, const QString& name, const QCefEvent& event)
  {
    CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(TRIGGEREVENT_NOTIFY_MESSAGE);
    CefRefPtr<CefListValue> arguments = msg->GetArgumentList();

    int idx = 0;
    CefString eventName = name.toStdString();
    arguments->SetString(idx++, eventName);

    CefRefPtr<CefDictionaryValue> dict = CefDictionaryValue::Create();

    CefString cefStr;
    cefStr.FromWString(event.objectName().toStdWString());
    dict->SetString("name", cefStr);

    QList<QByteArray> keys = event.dynamicPropertyNames();
    for (QByteArray key : keys) {
      QVariant value = event.property(key.data());
      if (value.type() == QMetaType::Bool)
        dict->SetBool(key.data(), value.toBool());
      else if (value.type() == QMetaType::Int || value.type() == QMetaType::UInt)
        dict->SetInt(key.data(), value.toInt());
      else if (value.type() == QMetaType::Double)
        dict->SetDouble(key.data(), value.toDouble());
      else if (value.type() == QMetaType::QString) {
        cefStr.FromWString(value.toString().toStdWString());
        dict->SetString(key.data(), cefStr);
      } else {
      }
    }

    arguments->SetDictionary(idx++, dict);

    return pQCefViewHandler_->TriggerEvent(frameId, msg);
  }

  void onToplevelWidgetMoveOrResize() { notifyMoveOrResizeStarted(); }

  void setContextMenuHandler(CefContextMenuHandler* handler)
  {
    if (pQCefViewHandler_)
      pQCefViewHandler_->SetContextMenuHandler(handler);
  }

  void setDialogHandler(CefDialogHandler* handler)
  {
    if (pQCefViewHandler_)
      pQCefViewHandler_->SetDialogHandler(handler);
  }

  void setDisplayHandler(CefDisplayHandler* handler)
  {
    if (pQCefViewHandler_)
      pQCefViewHandler_->SetDisplayHandler(handler);
  }

  void setDownloadHandler(CefDownloadHandler* handler)
  {
    if (pQCefViewHandler_)
      pQCefViewHandler_->SetDownloadHandler(handler);
  }

  void setJSDialogHandler(CefJSDialogHandler* handler)
  {
    if (pQCefViewHandler_)
      pQCefViewHandler_->SetJSDialogHandler(handler);
  }

  void setKeyboardHandler(CefKeyboardHandler* handler)
  {
    if (pQCefViewHandler_)
      pQCefViewHandler_->SetKeyboardHandler(handler);
  }

private:
  /// <summary>
  ///
  /// </summary>
  QPointer<CCefWindow> pCefWindow_;

  /// <summary>
  ///
  /// </summary>
  CefRefPtr<QCefViewBrowserHandler> pQCefViewHandler_;
};

QCefView::QCefView(const QString url, QWidget* parent /*= 0*/)
  : QWidget(parent)
  , pImpl_(nullptr)
{
  pImpl_ = std::make_unique<Implementation>(url, windowHandle());

  QGridLayout* layout = new QGridLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  QWidget* windowContainer = createWindowContainer(pImpl_->cefWindow(), this);
  layout->addWidget(windowContainer);
  setLayout(layout);

  connect(pImpl_->cefWindow(),
          SIGNAL(loadingStateChanged(bool, bool, bool)),
          this,
          SLOT(onLoadingStateChanged(bool, bool, bool)));

  connect(pImpl_->cefWindow(), SIGNAL(loadStart()), this, SLOT(onLoadStart()));

  connect(pImpl_->cefWindow(), SIGNAL(loadEnd(int)), this, SLOT(onLoadEnd(int)));

  connect(pImpl_->cefWindow(),
          SIGNAL(loadError(int, const QString&, const QString&, bool&)),
          this,
          SLOT(onLoadError(int, const QString&, const QString&, bool&)));

  connect(pImpl_->cefWindow(),
          SIGNAL(draggableRegionChanged(const QRegion&)),
          this,
          SLOT(onDraggableRegionChanged(const QRegion&)));

  connect(pImpl_->cefWindow(), SIGNAL(takeFocus(bool)), this, SLOT(onTakeFocus(bool)));

  connect(pImpl_->cefWindow(), SIGNAL(processUrlRequest(const QString&)), this, SLOT(onQCefUrlRequest(const QString&)));

  connect(pImpl_->cefWindow(),
          SIGNAL(processQueryRequest(const QCefQuery&)),
          this,
          SLOT(onQCefQueryRequest(const QCefQuery&)));

  connect(pImpl_->cefWindow(),
          SIGNAL(invokeMethodNotify(int, int, const QString&, const QVariantList&)),
          this,
          SLOT(onInvokeMethodNotify(int, int, const QString&, const QVariantList&)));

  // If we're already part of a window, we'll install our event handler
  // If our parent changes later, this will be handled in QCefView::changeEvent()
  if (this->window())
    this->window()->installEventFilter(this);
}

QCefView::QCefView(QWidget* parent /*= 0*/)
  : QCefView("about:blank", parent)
{}

QCefView::~QCefView()
{
  if (pImpl_) {
    pImpl_ = nullptr;
  }

  disconnect();
}

WId
QCefView::getCefWinId()
{
  if (pImpl_)
    return pImpl_->getCefWinId();

  return 0;
}

void
QCefView::navigateToString(const QString& content)
{
  if (pImpl_)
    pImpl_->navigateToString(content);
}

void
QCefView::navigateToUrl(const QString& url)
{
  if (pImpl_)
    pImpl_->navigateToUrl(url);
}

bool
QCefView::browserCanGoBack()
{
  if (pImpl_)
    return pImpl_->browserCanGoBack();

  return false;
}

bool
QCefView::browserCanGoForward()
{
  if (pImpl_)
    return pImpl_->browserCanGoForward();

  return false;
}

void
QCefView::browserGoBack()
{
  if (pImpl_)
    pImpl_->browserGoBack();
}

void
QCefView::browserGoForward()
{
  if (pImpl_)
    pImpl_->browserGoForward();
}

bool
QCefView::browserIsLoading()
{
  if (pImpl_)
    return pImpl_->browserIsLoading();

  return false;
}

void
QCefView::browserReload()
{
  if (pImpl_)
    pImpl_->browserReload();
}

void
QCefView::browserStopLoad()
{
  if (pImpl_)
    pImpl_->browserStopLoad();
}

bool
QCefView::triggerEvent(const QString& name, const QCefEvent& event)
{
  if (pImpl_)
    return pImpl_->triggerEvent(name, event, QCefViewBrowserHandler::MAIN_FRAME);

  return false;
}

bool
QCefView::triggerEvent(const QString& name, const QCefEvent& event, int frameId)
{
  if (pImpl_)
    return pImpl_->triggerEvent(name, event, frameId);

  return false;
}

bool
QCefView::broadcastEvent(const QString& name, const QCefEvent& event)
{
  if (pImpl_)
    return pImpl_->triggerEvent(name, event, QCefViewBrowserHandler::ALL_FRAMES);

  return false;
}

bool
QCefView::responseQCefQuery(const QCefQuery& query)
{
  if (pImpl_)
    return pImpl_->responseQCefQuery(query);

  return false;
}

void
QCefView::setContextMenuHandler(CefContextMenuHandler* handler)
{
  if (pImpl_)
    return pImpl_->setContextMenuHandler(handler);
}

void
QCefView::setDialogHandler(CefDialogHandler* handler)
{
  if (pImpl_)
    return pImpl_->setDialogHandler(handler);
}

void
QCefView::setDisplayHandler(CefDisplayHandler* handler)
{
  if (pImpl_)
    return pImpl_->setDisplayHandler(handler);
}

void
QCefView::setDownloadHandler(CefDownloadHandler* handler)
{
  if (pImpl_)
    return pImpl_->setDownloadHandler(handler);
}

void
QCefView::setJSDialogHandler(CefJSDialogHandler* handler)
{
  if (pImpl_)
    return pImpl_->setJSDialogHandler(handler);
}

void
QCefView::setKeyboardHandler(CefKeyboardHandler* handler)
{
  if (pImpl_)
    return pImpl_->setKeyboardHandler(handler);
}

void
QCefView::changeEvent(QEvent* event)
{
  if (QEvent::ParentAboutToChange == event->type()) {
    if (this->window())
      this->window()->removeEventFilter(this);
  } else if (QEvent::ParentChange == event->type()) {
    if (this->window())
      this->window()->installEventFilter(this);
  }
  QWidget::changeEvent(event);
}

bool
QCefView::eventFilter(QObject* watched, QEvent* event)
{
  if (pImpl_ && watched == this->window()) {
    if (QEvent::Resize == event->type() || QEvent::Move == event->type())
      pImpl_->onToplevelWidgetMoveOrResize();
  }
  return QWidget::eventFilter(watched, event);
}

void
QCefView::onLoadingStateChanged(bool isLoading, bool canGoBack, bool canGoForward)
{}

void
QCefView::onLoadStart()
{}

void
QCefView::onLoadEnd(int httpStatusCode)
{}

void
QCefView::onLoadError(int errorCode, const QString& errorMsg, const QString& failedUrl, bool& handled)
{}

void
QCefView::onDraggableRegionChanged(const QRegion& region)
{}

void
QCefView::onTakeFocus(bool next)
{}

void
QCefView::onQCefUrlRequest(const QString& url)
{}

void
QCefView::onQCefQueryRequest(const QCefQuery& query)
{}

void
QCefView::onInvokeMethodNotify(int browserId, int frameId, const QString& method, const QVariantList& arguments)
{}
