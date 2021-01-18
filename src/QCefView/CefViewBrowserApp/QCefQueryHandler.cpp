#include "QCefQueryHandler.h"

#include "Include/QCefQuery.h"

QCefQueryHandler::QCefQueryHandler(QCefViewDelegate* pDelegate)
  : pQcefViewDelegate_(pDelegate)
{}

QCefQueryHandler::~QCefQueryHandler()
{
  pQcefViewDelegate_ = nullptr;
}

bool
QCefQueryHandler::OnQuery(CefRefPtr<CefBrowser> browser,
                          CefRefPtr<CefFrame> frame,
                          int64 query_id,
                          const CefString& request,
                          bool persistent,
                          CefRefPtr<Callback> callback)
{
  if (pQcefViewDelegate_) {
    mtxCallbackMap_.lock();
    mapCallback_[query_id] = callback;
    mtxCallbackMap_.unlock();

    pQcefViewDelegate_->onQCefQueryRequest(request, query_id);

    return true;
  }

  return false;
}

void
QCefQueryHandler::OnQueryCanceled(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64 query_id)
{
  mtxCallbackMap_.lock();
  auto it = mapCallback_.find(query_id);
  if (it != mapCallback_.end())
    mapCallback_.erase(it);

  mtxCallbackMap_.unlock();
}

bool
QCefQueryHandler::Response(int64_t query, bool success, const CefString& response, int error)
{
  CefRefPtr<Callback> cb;
  mtxCallbackMap_.lock();
  auto it = mapCallback_.find(query);
  if (it != mapCallback_.end()) {
    cb = it->second;
    mapCallback_.erase(it);
  }
  mtxCallbackMap_.unlock();

  if (!cb)
    return false;

  if (success)
    cb->Success(response);
  else
    cb->Failure(error, response);

  return true;
}
