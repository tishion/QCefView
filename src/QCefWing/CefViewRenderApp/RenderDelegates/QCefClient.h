#pragma once
#pragma region std_headers
#include <map>
#include <list>
#pragma endregion

#pragma region cef_headers
#include <include/cef_v8.h>
#pragma endregion cef_headers

#include <QCefProtocol.h>

/// <summary>
///
/// </summary>
class QCefClient : public CefBaseRefCounted
{
  // class Accessor
  //	: public CefV8Accessor
  //{
  // public:
  //	virtual bool Get(const CefString& name,
  //		const CefRefPtr<CefV8Value> object,
  //		CefRefPtr<CefV8Value>& retval,
  //		CefString& exception) override;

  //	virtual bool Set(const CefString& name,
  //		const CefRefPtr<CefV8Value> object,
  //		const CefRefPtr<CefV8Value> value,
  //		CefString& exception) override;

  // private:
  //	IMPLEMENT_REFCOUNTING(Accessor);
  //};

  /// <summary>
  ///
  /// </summary>
  typedef struct _EventListener
  {
    CefRefPtr<CefV8Value> callback_;
    CefRefPtr<CefV8Context> context_;
  } EventListener;

  /// <summary>
  ///
  /// </summary>
  typedef std::list<EventListener> EventListenerList;

  /// <summary>
  ///
  /// </summary>
  typedef std::map<CefString, std::list<EventListener>> EventListenerListMap;

  /// <summary>
  ///
  /// </summary>
  class V8Handler : public CefV8Handler
  {
  public:
    /// <summary>
    ///
    /// </summary>
    /// <param name="browser"></param>
    /// <param name="frame"></param>
    /// <param name="eventListenerListMap"></param>
    V8Handler(CefRefPtr<CefBrowser> browser,
              CefRefPtr<CefFrame> frame,
              QCefClient::EventListenerListMap& eventListenerListMap);

    /// <summary>
    ///
    /// </summary>
    /// <param name="function"></param>
    /// <param name="object"></param>
    /// <param name="arguments"></param>
    /// <param name="retval"></param>
    /// <param name="exception"></param>
    /// <returns></returns>
    virtual bool Execute(const CefString& function,
                         CefRefPtr<CefV8Value> object,
                         const CefV8ValueList& arguments,
                         CefRefPtr<CefV8Value>& retval,
                         CefString& exception) override;

  protected:
    /// <summary>
    ///
    /// </summary>
    /// <param name="function"></param>
    /// <param name="object"></param>
    /// <param name="arguments"></param>
    /// <param name="retval"></param>
    /// <param name="exception"></param>
    void ExecuteInvokeMethod(const CefString& function,
                             CefRefPtr<CefV8Value> object,
                             const CefV8ValueList& arguments,
                             CefRefPtr<CefV8Value>& retval,
                             CefString& exception);

    /// <summary>
    ///
    /// </summary>
    /// <param name="function"></param>
    /// <param name="object"></param>
    /// <param name="arguments"></param>
    /// <param name="retval"></param>
    /// <param name="exception"></param>
    void ExecuteAddEventListener(const CefString& function,
                                 CefRefPtr<CefV8Value> object,
                                 const CefV8ValueList& arguments,
                                 CefRefPtr<CefV8Value>& retval,
                                 CefString& exception);

    /// <summary>
    ///
    /// </summary>
    /// <param name="function"></param>
    /// <param name="object"></param>
    /// <param name="arguments"></param>
    /// <param name="retval"></param>
    /// <param name="exception"></param>
    void ExecuteRemoveEventListener(const CefString& function,
                                    CefRefPtr<CefV8Value> object,
                                    const CefV8ValueList& arguments,
                                    CefRefPtr<CefV8Value>& retval,
                                    CefString& exception);

  private:
    /// <summary>
    ///
    /// </summary>
    CefRefPtr<CefBrowser> browser_;

    /// <summary>
    ///
    /// </summary>
    CefRefPtr<CefFrame> frame_;

    /// <summary>
    ///
    /// </summary>
    QCefClient::EventListenerListMap& eventListenerListMap_;

  private:
    IMPLEMENT_REFCOUNTING(V8Handler);
  };

public:
  /// <summary>
  ///
  /// </summary>
  /// <param name="browser"></param>
  /// <param name="frame"></param>
  QCefClient(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame);

  /// <summary>
  ///
  /// </summary>
  /// <returns></returns>
  CefRefPtr<CefV8Value> GetObject();

  /// <summary>
  ///
  /// </summary>
  /// <param name="eventName"></param>
  /// <param name="dict"></param>
  void ExecuteEventListener(const CefString eventName, CefRefPtr<CefDictionaryValue> dict);

private:
  /// <summary>
  ///
  /// </summary>
  CefRefPtr<CefV8Value> object_;

  /// <summary>
  ///
  /// </summary>
  CefRefPtr<CefBrowser> browser_;

  /// <summary>
  ///
  /// </summary>
  CefRefPtr<CefFrame> frame_;

  /// <summary>
  ///
  /// </summary>
  EventListenerListMap eventListenerListMap_;

private:
  IMPLEMENT_REFCOUNTING(QCefClient);
};
