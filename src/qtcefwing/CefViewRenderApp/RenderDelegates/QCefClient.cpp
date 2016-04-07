#include "stdafx.h"
#pragma region projet_headers
#include "QCefClient.h"
#pragma endregion projet_headers

bool QCefClient::Accessor::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
	return true;
}

bool QCefClient::Accessor::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
	if (value->IsFunction())
	{
		object->SetValue(name, value, V8_PROPERTY_ATTRIBUTE_NONE);
	}
	else
	{
		exception = "Invalid arguments; expecting a single function";
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////

QCefClient::V8Handler::V8Handler(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame)
	: browser_(browser), frame_(frame)
{

}

bool QCefClient::V8Handler::Execute(const CefString& function, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
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

	if (browser_)
	{
		return browser_->SendProcessMessage(PID_BROWSER, msg);
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////

QCefClient::QCefClient(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame)
	: object_(CefV8Value::CreateObject(new Accessor()))
	, browser_(browser)
	, frame_(frame)
{
	// create function handler
	CefRefPtr<V8Handler> handler = new V8Handler(browser_, frame_);
	// create function function
	CefRefPtr<CefV8Value> function = CefV8Value::CreateFunction(QCEF_INVOKEMETHOD, handler);
	// add this function to window object
	object_->SetValue(QCEF_INVOKEMETHOD, function, V8_PROPERTY_ATTRIBUTE_READONLY);

	// create event list
	//CefRefPtr<CefV8Value> events = CefV8Value::CreateArray(0);
	//object_->SetValue(QCEF_EVENTLIST, events, V8_PROPERTY_ATTRIBUTE_NONE);
}

QCefClient::operator CefRefPtr<CefV8Value>()
{
	CefRefPtr<CefV8Value> p = object_;
	return p;
}
