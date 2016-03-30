#include "stdafx.h"
#pragma region projet_headers
#include "QCefClientV8Handler.h"
#pragma endregion projet_headers

QCefClientV8Handler::QCefClientV8Handler(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame)
	: browser_(browser)
	, frame_(frame)
{

}

bool QCefClientV8Handler::Execute(const CefString& name,
	CefRefPtr<CefV8Value> object,
	const CefV8ValueList& arguments,
	CefRefPtr<CefV8Value>& retval,
	CefString& exception)
{
	CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(
		NOTIFY_REQUTEST_MESSAGE_NAME);
	CefRefPtr<CefListValue> args = msg->GetArgumentList();
	args->SetString(0, name);

	for (std::size_t i = 0; i < arguments.size(); i++)
	{
		if (arguments[i]->IsBool())
		{
			args->SetBool(i + 1,
				arguments[i]->GetBoolValue());
		}
		else if (arguments[i]->IsInt())
		{
			args->SetInt(i + 1,
				arguments[i]->GetIntValue());
		}
		else if (arguments[i]->IsDouble())
		{
			args->SetDouble(i + 1,
				arguments[i]->GetDoubleValue());
		}
		else if (arguments[i]->IsString())
		{
			args->SetString(i + 1,
				arguments[i]->GetStringValue());
		}
		else
		{
			args->SetNull(i + 1);
		}
	}

	if (browser_)
	{
		return browser_->SendProcessMessage(PID_BROWSER, msg);
	}

	return false;
}

