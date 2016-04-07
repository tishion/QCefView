#include "stdafx.h"
#pragma region projet_headers
#include "QCefClient.h"
#pragma endregion projet_headers

bool QCefClient::Accessor::Get(const CefString& name, 
	const CefRefPtr<CefV8Value> object, 
	CefRefPtr<CefV8Value>& retval, 
	CefString& exception)
{
	return true;
}

bool QCefClient::Accessor::Set(const CefString& name,
	const CefRefPtr<CefV8Value> object,
	const CefRefPtr<CefV8Value> value, 
	CefString& exception)
{
	return true;
}

//////////////////////////////////////////////////////////////////////////

QCefClient::V8Handler::V8Handler(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	QCefClient::EventHandlerMap& eventHandlerMap)
	: browser_(browser), frame_(frame), eventHandlerMap_(eventHandlerMap)
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
	else if (function == QCEF_REGISTEREVENTHANDLER)
	{
		ExecuteRegisterEventHandler(function, object, arguments, retval, exception);
	}
	else if (function == QCEF_UNREGISTEREVENTHANDLER)
	{
		ExecuteUnregisterEventHandler(function, object, arguments, retval, exception);
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

void QCefClient::V8Handler::ExecuteRegisterEventHandler(const CefString& function,
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
				CefRefPtr<CefV8Handler> eventHandler = arguments[1]->GetFunctionHandler();
				eventHandlerMap_[eventName] = eventHandler;
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

void QCefClient::V8Handler::ExecuteUnregisterEventHandler(const CefString& function,
	CefRefPtr<CefV8Value> object,
	const CefV8ValueList& arguments,
	CefRefPtr<CefV8Value>& retval,
	CefString& exception)
{
	bool bRet = false;

	if (arguments.size() == 1)
	{
		if (arguments[0]->IsString())
		{
			CefString eventName = arguments[0]->GetStringValue();
			auto it = eventHandlerMap_.find(eventName);
			if (it != eventHandlerMap_.end())
			{
				eventHandlerMap_.erase(it);
			}
			bRet = true;
		}
		else
		{
			exception = "Invalid parameters; parameter 1 is expecting a string";
		}
	}
	else
	{
		exception = "Invalid parameters; expecting 1 parameters";
	}

	retval = CefV8Value::CreateBool(bRet);
}

//////////////////////////////////////////////////////////////////////////

QCefClient::QCefClient(CefRefPtr<CefBrowser> browser, 
	CefRefPtr<CefFrame> frame)
	: object_(CefV8Value::CreateObject(new Accessor()))
	, browser_(browser)
	, frame_(frame)
{
	// create function handler
	CefRefPtr<V8Handler> handler = new V8Handler(browser_, frame_, eventHandlerMap_);

	// create function function
	CefRefPtr<CefV8Value> funcInvokeMethod = 
		CefV8Value::CreateFunction(QCEF_INVOKEMETHOD, handler);
	// add this function to window object
	object_->SetValue(QCEF_INVOKEMETHOD, funcInvokeMethod, 
		V8_PROPERTY_ATTRIBUTE_READONLY);

	// create function function
	CefRefPtr<CefV8Value> funcRegisterEventHandler = 
		CefV8Value::CreateFunction(QCEF_REGISTEREVENTHANDLER, handler);
	// add this function to window object
	object_->SetValue(QCEF_REGISTEREVENTHANDLER, funcRegisterEventHandler,
		V8_PROPERTY_ATTRIBUTE_READONLY);

	// create function function
	CefRefPtr<CefV8Value> funcUnregisterEventHandler =
		CefV8Value::CreateFunction(QCEF_UNREGISTEREVENTHANDLER, handler);
	// add this function to window object
	object_->SetValue(QCEF_UNREGISTEREVENTHANDLER, funcUnregisterEventHandler,
		V8_PROPERTY_ATTRIBUTE_READONLY);
}

CefRefPtr<CefV8Value> QCefClient::GetObject()
{
	return object_;
}

