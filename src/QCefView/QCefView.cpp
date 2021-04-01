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
#include "CCefManager.h"
#include "CCefWindow.h"
#include "CCefSetting.h"
#include "CefViewBrowserApp/QCefViewBrowserHandler.h"
#include "CefViewBrowserApp/SchemeHandlers/QCefViewDelegatedSchemeHandler.h"

//////////////////////////////////////////////////////////////////////////
class QCefView::Implementation
{
public:
  explicit Implementation(const QString& url, QCefView* view)
    : pCefWindow_(nullptr)
    , pQCefViewHandler_(nullptr)
    , nextFindId_(0)
  {
    // Here we must create a QWidget as a wrapper to encapsulate the QWindow
    pCefWindow_ = new CCefWindow(view);
    pCefWindow_->create();

    // Set window info
    CefWindowInfo window_info;
    RECT rc = { 0 };
    window_info.SetAsChild((HWND)pCefWindow_->winId(), rc);

    for (auto cookieItem : CCefSetting::global_cookie_list) {
      CCefManager::getInstance().addCookie(cookieItem.name, cookieItem.value, cookieItem.domain, cookieItem.url);
    }

    CefBrowserSettings browserSettings;
    browserSettings.plugins = STATE_DISABLED; // disable all plugins

    // Create the browser
    pQCefViewHandler_ = new QCefViewBrowserHandler(pCefWindow_);

    // add archive mapping
    for (auto archiveMapping : archiveMappingList_) {
      pQCefViewHandler_->AddArchiveResourceProvider(
        archiveMapping.path.toStdString(), archiveMapping.url.toStdString(), archiveMapping.psw.toStdString());
    }

    // add local folder mapping
    for (auto folderMapping : folderMappingList_) {
      pQCefViewHandler_->AddLocalDirectoryResourceProvider(
        folderMapping.path.toStdString(), folderMapping.url.toStdString(), folderMapping.priority);
    }

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
      pQCefViewHandler_->CloseAllBrowsers(true);
      pQCefViewHandler_ = nullptr;
    }
  }

  void closeAllBrowsers()
  {
    if (pQCefViewHandler_) {
      pQCefViewHandler_->CloseAllBrowsers(true);
    }
  }

  CCefWindow* cefWindow() { return pCefWindow_; }

  WId getCefWinId()
  {
    if (pCefWindow_)
      return pCefWindow_->winId();

    return 0;
  }

  void addLocalFolderResource(const QString& path, const QString& url)
  {
    if (pQCefViewHandler_) {
      pQCefViewHandler_->AddLocalDirectoryResourceProvider(path.toStdString(), url.toStdString());
    }
  }

  void addArchiveResource(const QString& path, const QString& url, const QString& password)
  {
    if (pQCefViewHandler_) {
      pQCefViewHandler_->AddArchiveResourceProvider(path.toStdString(), url.toStdString(), password.toStdString());
    }
  }

  void navigateToString(const QString& content)
  {
    if (pQCefViewHandler_ && pQCefViewHandler_->GetBrowser() && pQCefViewHandler_->GetBrowser()->GetMainFrame()) {
      std::string data = content.toStdString();
      data = CefURIEncode(CefBase64Encode(data.c_str(), data.size()), false).ToString();
      data = "data:text/html;base64," + data;
      pQCefViewHandler_->GetBrowser()->GetMainFrame()->LoadURL(data);
    }
  }

  void navigateToUrl(const QString& url)
  {
    if (pQCefViewHandler_ && pQCefViewHandler_->GetBrowser() && pQCefViewHandler_->GetBrowser()->GetMainFrame()) {
      CefString strUrl;
      strUrl.FromString(url.toStdString());
      pQCefViewHandler_->GetBrowser()->GetMainFrame()->LoadURL(strUrl);
    }
  }

  qreal getZoomLevel()
  {
    double zoomLevel = pQCefViewHandler_->GetBrowser()->GetHost()->GetZoomLevel();
    if (zoomLevel == 0.0) {
      zoomLevel = 1.0;
    }
    return zoomLevel;
  }

  void setZoomLevel(qreal zoomLevel)
  {
    pQCefViewHandler_->GetBrowser()->GetHost()->SetZoomLevel(zoomLevel);
  }

  void runJavaScript(const QString& scriptSource)
  {
    if (pQCefViewHandler_ && pQCefViewHandler_->GetBrowser() && pQCefViewHandler_->GetBrowser()->GetMainFrame()) {
      CefString strScriptSource;
      strScriptSource.FromString(scriptSource.toStdString());
      CefString strScriptSourceFile;
      strScriptSourceFile.FromASCII("");

      pQCefViewHandler_->GetBrowser()->GetMainFrame()->ExecuteJavaScript(strScriptSource, strScriptSourceFile, 1);
    }
  }

  void registerSchemeHandler(const QString& scheme, QCefSchemeHandler::SchemeHandlerCreator creator)
  {
    CefString strScheme;
    strScheme.FromString(scheme.toStdString());

    QCefViewDelegatedSchemeHandler::RegisterSchemeHandlerFactory(strScheme, creator);
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

  int findText(QString text, bool forward, bool matchCase, int previousId)
  {
    int findId = -1;
    if (pQCefViewHandler_) {
      CefRefPtr<CefBrowser> browser = pQCefViewHandler_->GetBrowser();
      if (browser) {
        CefRefPtr<CefBrowserHost> host = browser->GetHost();
        if (host) {
          if (!text.isEmpty()) {
            bool followUp = previousId > 0;
            findId = followUp ? previousId : nextFindId_++;
            CefString ctext;
            ctext.FromString(text.toStdString());
            host->Find(findId, ctext, forward, matchCase, followUp);
          } else {
            host->StopFinding(true);
          }
        }
      }
    }
    return findId;
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
    cefStr.FromString(event.objectName().toUtf8().constData());
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
        cefStr.FromString(value.toString().toUtf8().constData());
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

public:
  /// <summary>
  ///
  /// </summary>
  typedef struct FolderMapping
  {
    QString path;
    QString url;
    int priority;
  } FolderMapping;
  static QList<FolderMapping> folderMappingList_;

  /// <summary>
  ///
  /// </summary>
  typedef struct ArchiveMapping
  {
    QString path;
    QString url;
    QString psw;
  } ArchiveMapping;
  static QList<ArchiveMapping> archiveMappingList_;

private:
  /// <summary>
  ///
  /// </summary>
  QPointer<CCefWindow> pCefWindow_;

  /// <summary>
  ///
  /// </summary>
  CefRefPtr<QCefViewBrowserHandler> pQCefViewHandler_;

  QAtomicInt nextFindId_;
};

QList<QCefView::Implementation::FolderMapping> QCefView::Implementation::folderMappingList_;
QList<QCefView::Implementation::ArchiveMapping> QCefView::Implementation::archiveMappingList_;

QCefView::QCefView(const QString url, QWidget* parent /*= 0*/)
  : QWidget(parent)
  , pImpl_(nullptr)
  , initSemaphore_(new QSemaphore())
{
  pImpl_ = std::make_unique<Implementation>(url, this);

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  setLayout(layout);

  QWidget* windowContainer = createWindowContainer(pImpl_->cefWindow(), this);
  layout->addWidget(windowContainer);

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
  disconnect();

  if (pImpl_)
    pImpl_.reset();
}

void
QCefView::addLocalFolderResource(const QString& path, const QString& url, int priority /* = 0*/)
{
  Implementation::folderMappingList_.push_back({ path, url, priority });
}

void
QCefView::addArchiveResource(const QString& path, const QString& url, const QString& password /* = ""*/)
{
  Implementation::archiveMappingList_.push_back({ path, url, password });
}

void
QCefView::addCookie(const QString& name, const QString& value, const QString& domain, const QString& url)
{
  CCefManager::getInstance().addCookie(
    name.toStdString(), value.toStdString(), domain.toStdString(), url.toStdString());
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
  if (!waitForInit())
    return;
  if (pImpl_)
    pImpl_->navigateToString(content);
}

void
QCefView::navigateToUrl(const QString& url)
{
  if (!waitForInit())
    return;
  if (pImpl_)
    pImpl_->navigateToUrl(url);
}

qreal
QCefView::getZoomLevel()
{
  if (!waitForInit())
    return 0.0;
  if (pImpl_)
    return pImpl_->getZoomLevel();
}

void
QCefView::setZoomLevel(qreal zoomLevel)
{
  if (!waitForInit())
    return;
  if (pImpl_)
    pImpl_->setZoomLevel(zoomLevel);
}

void
QCefView::runJavaScript(const QString& script)
{
  if (!waitForInit())
    return;
  if (pImpl_)
    pImpl_->runJavaScript(script);
}

void
QCefView::registerSchemeHandler(const QString& scheme, QCefSchemeHandler::SchemeHandlerCreator handlerCreator)
{
  if (pImpl_)
    pImpl_->registerSchemeHandler(scheme, handlerCreator);
}

int
QCefView::findText(const QString& text, bool forward, bool matchCase, int previousId)
{
  if (pImpl_)
    return pImpl_->findText(text, forward, matchCase, previousId);
  return -1;
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
QCefView::triggerEvent(const QCefEvent& event)
{
  if (pImpl_)
    return pImpl_->triggerEvent(event.objectName(), event, QCefViewBrowserHandler::MAIN_FRAME);

  return false;
}

bool
QCefView::triggerEvent(const QCefEvent& event, int frameId)
{
  if (pImpl_)
    return pImpl_->triggerEvent(event.objectName(), event, frameId);

  return false;
}

bool
QCefView::broadcastEvent(const QCefEvent& event)
{
  if (pImpl_)
    return pImpl_->triggerEvent(event.objectName(), event, QCefViewBrowserHandler::ALL_FRAMES);

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
QCefView::onAddressChange(int browserId, int frameId, const QString& url)
{}

void
QCefView::onTitleChange(int browserId, const QString& title)
{}

void
QCefView::onConsoleMessage(const QString& message, int level, const QString& source, int line)
{}

void
QCefView::onTakeFocus(bool next)
{}

void
QCefView::onFindResult(int browserId, int identifier, int count, const QRect& selectionRect, int activeMatchOrdinal, bool finalUpdate)
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

bool
QCefView::isInitialized(int timeout)
{
  return !initSemaphore_ || waitForInit(timeout);
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
QCefView::onLoadEndInternal(int httpStatusCode)
{
  if (initSemaphore_) {
    initSemaphore_->release();
  }
}

bool
QCefView::waitForInit(int timeOut)
{
  if (initSemaphore_) {
    if (!initSemaphore_->tryAcquire(1, timeOut)) {
      return false;
    }
    delete initSemaphore_;
    initSemaphore_ = nullptr;
  }
  return true;
}
