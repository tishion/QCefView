#include "stdafx.h"
#pragma region projet_headers
#include "QCefClient.h"
#pragma endregion projet_headers

//bool QCefClient::Accessor::Get(const CefString& name, 
//	const CefRefPtr<CefV8Value> object, 
//	CefRefPtr<CefV8Value>& retval, 
//	CefString& exception)
//{
//	return true;
//}
//
//bool QCefClient::Accessor::Set(const CefString& name,
//	const CefRefPtr<CefV8Value> object,
//	const CefRefPtr<CefV8Value> value, 
//	CefString& exception)
//{
//	return true;
//}

//////////////////////////////////////////////////////////////////////////

QCefClient::V8Handler::V8Handler(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	QCefClient::EventListenerListMap& eventListenerListMap)
	: browser_(browser)
	, frame_(frame)
	, eventListenerListMap_(eventListenerListMap)
{

}

bool QCefClient::V8Handler::Execute(const CefString& function, 
	CefRefPtr<CefV8Value> object, 
	const CefV8ValueList& arguments, 
	CefRefPtr<CefV8Value>& retval, 
	CefString& exception)
{
	if (function == QCEF_INVOKEMETHOD)
	{
		ExecuteInvokeMethod(function, object, arguments, retval, exception);
	}
	else if (function == QCEF_ADDEVENTLISTENER)
	{
		ExecuteAddEventListener(function, object, arguments, retval, exception);
	}
	else if (function == QCEF_REMOVEEVENTLISTENER)
	{
		ExecuteRemoveEventListener(function, object, arguments, retval, exception);
	}
	else
	{
		return false;
	}

	return true;
}

void QCefClient::V8Handler::ExecuteInvokeMethod(const CefString& function,
	CefRefPtr<CefV8Value> object,
	const CefV8ValueList& arguments, 
	CefRefPtr<CefV8Value>& retval, 
	CefString& exception)
{
	CefRefPtr<CefProcessMessage> msg
		= CefProcessMessage::Create(INVOKEMETHOD_NOTIFY_MESSAGE);

	CefRefPtr<CefListValue> args = msg->GetArgumentList();
	int frameId = (int)frame_->GetIdentifier();

	int idx = 0;
	args->SetInt(idx++, frameId);
	args->SetString(idx++, function);

	for (std::size_t i = 0; i < arguments.size(); i++)
	{
		if (arguments[i]->IsBool())
		{
			args->SetBool(idx++,
				arguments[i]->GetBoolValue());
		}
		else if (arguments[i]->IsInt())
		{
			args->SetInt(idx++,
				arguments[i]->GetIntValue());
		}
		else if (arguments[i]->IsDouble())
		{
			args->SetDouble(idx++,
				arguments[i]->GetDoubleValue());
		}
		else if (arguments[i]->IsString())
		{
			args->SetString(idx++,
				arguments[i]->GetStringValue());
		}
		else
		{
			args->SetNull(idx++);
		}
	}

	bool bRet = false;
	if (browser_)
	{	
		bRet = browser_->SendProcessMessage(PID_BROWSER, msg);
	}
	retval = CefV8Value::CreateBool(bRet);
}

void QCefClient::V8Handler::ExecuteAddEventListener(const CefString& function,
	CefRefPtr<CefV8Value> object, 
	const CefV8ValueList& arguments, 
	CefRefPtr<CefV8Value>& retval, 
	CefString& exception)
{
	bool bRet = false;

	if (arguments.size() == 2)
	{
		if (arguments[0]->IsString())
		{
			if (arguments[1]->IsFunction())
			{
				CefString eventName = arguments[0]->GetStringValue();
				EventListener listener;
				listener.callback_ = arguments[1];
				listener.context_ = CefV8Context::GetCurrentContext();

				auto itListenerList = eventListenerListMap_.find(eventName);
				if (itListenerList == eventListenerListMap_.end())
				{
					EventListenerList eventListenerList;
					eventListenerList.push_back(listener);
					eventListenerListMap_[eventName] = eventListenerList;
				}
				else
				{
					EventListenerList& eventListenerList = itListenerList->second;
					// does this listener exist?
					bool found = false;
					for (auto item: eventListenerList)
					{
						if (item.callback_->IsSame(listener.callback_))
						{
							found = true;
							break;
						}
					}

					if (!found)
					{
						eventListenerList.push_back(listener);
					}
				}
				bRet = true;
			}
			else
			{
				exception = "Invalid parameters; parameter 2 is expecting a function";
			}
		}
		else
		{
			exception = "Invalid parameters; parameter 1 is expecting a string";
		}
	}
	else
	{
		exception = "Invalid parameters; expecting 2 parameters";
	}

	retval = CefV8Value::CreateBool(bRet);
}

void QCefClient::V8Handler::ExecuteRemoveEventListener(const CefString& function,
	CefRefPtr<CefV8Value> object,
	const CefV8ValueList& arguments,
	CefRefPtr<CefV8Value>& retval,
	CefString& exception)
{
	bool bRet = false;

	if (arguments.size() == 2)
	{
		if (arguments[0]->IsString())
		{
			if (arguments[1]->IsFunction())
			{
				CefString eventName = arguments[0]->GetStringValue();
				EventListener listener;
				listener.callback_ = arguments[1];
				listener.context_ = CefV8Context::GetCurrentContext();

				auto itListenerList = eventListenerListMap_.find(eventName);
				if (itListenerList != eventListenerListMap_.end())
				{
					EventListenerList& eventListenerList = itListenerList->second;
					for (auto itListener = eventListenerList.begin();
						itListener != eventListenerList.end();
						itListener ++)
					{
						if (itListener->callback_->IsSame(listener.callback_))
						{
							eventListenerList.erase(itListener);
						}
					}
				}
			}
			else
			{
				exception = "Invalid parameters; parameter 2 is expecting a function";
			}
		}
		else
		{
			exception = "Invalid parameters; parameter 1 is expecting a string";
		}
	}
	else
	{
		exception = "Invalid parameters; expecting 2 parameters";
	}

	retval = CefV8Value::CreateBool(bRet);
}

//////////////////////////////////////////////////////////////////////////

QCefClient::QCefClient(CefRefPtr<CefBrowser> browser, 
	CefRefPtr<CefFrame> frame)
	: object_(CefV8Value::CreateObject(NULL))
	, browser_(browser)
	, frame_(frame)
{
	// create function handler
	CefRefPtr<V8Handler> handler = new V8Handler(browser_, frame_, eventListenerListMap_);

	// create function function
	CefRefPtr<CefV8Value> funcInvokeMethod = 
		CefV8Value::CreateFunction(QCEF_INVOKEMETHOD, handler);
	// add this function to window object
	object_->SetValue(QCEF_INVOKEMETHOD, funcInvokeMethod, 
		V8_PROPERTY_ATTRIBUTE_READONLY);

	// create function function
	CefRefPtr<CefV8Value> funcAddEventListener = 
		CefV8Value::CreateFunction(QCEF_ADDEVENTLISTENER, handler);
	// add this function to window object
	object_->SetValue(QCEF_ADDEVENTLISTENER, funcAddEventListener,
		V8_PROPERTY_ATTRIBUTE_READONLY);

	// create function function
	CefRefPtr<CefV8Value> funcRemoveEventListener =
		CefV8Value::CreateFunction(QCEF_REMOVEEVENTLISTENER, handler);
	// add this function to window object
	object_->SetValue(QCEF_REMOVEEVENTLISTENER, funcRemoveEventListener,
		V8_PROPERTY_ATTRIBUTE_READONLY);
}

CefRefPtr<CefV8Value> QCefClient::GetObject()
{
	return object_;
}

void QCefClient::ExecuteEventListener(const CefString eventName,
	CefRefPtr<CefDictionaryValue> dict)
{
	auto itListenerList = eventListenerListMap_.find(eventName);
	if (itListenerList != eventListenerListMap_.end())
	{
		EventListenerList& eventListenerList = itListenerList->second;
		for (auto listener : eventListenerList)
		{
			listener.context_->Enter();

			CefRefPtr<CefV8Value> eventObject = CefV8Value::CreateObject(NULL);
			CefDictionaryValue::KeyList kyes;
			dict->GetKeys(kyes);
			CefRefPtr<CefValue> value;
			CefRefPtr<CefV8Value> v8Value;
			for (const CefString key : kyes)
			{
				value = dict->GetValue(key);
				if (VTYPE_BOOL == value->GetType())
				{
					v8Value = CefV8Value::CreateBool(value->GetBool());
				}
				else if (VTYPE_INT == value->GetType())
				{
					v8Value = CefV8Value::CreateInt(value->GetInt());

				}
				else if (VTYPE_DOUBLE == value->GetType())
				{
					v8Value = CefV8Value::CreateDouble(value->GetDouble());
				}
				else if (VTYPE_STRING == value->GetType())
				{
					v8Value = CefV8Value::CreateString(value->GetString());
				}
				else
				{
					// unknown type
					continue;
				}

				eventObject->SetValue(key, v8Value,
					V8_PROPERTY_ATTRIBUTE_READONLY);
			}

			CefV8ValueList arguments;
			arguments.push_back(eventObject);

			listener.callback_->ExecuteFunction(object_, arguments);
			listener.context_->Exit();
		}
	}
}

