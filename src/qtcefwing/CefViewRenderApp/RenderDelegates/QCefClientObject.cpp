#include "stdafx.h"
#pragma region projet_headers
#include "QCefClientObject.h"
#pragma endregion projet_headers


CefString QCefClient::versionInt_ = "";
CefString QCefClient::versionStr_ = "";

QCefClient::QCefClient(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame)
	: browser_(browser), frame_(frame)
{
	self_ = CefV8Value::CreateObject(this);

	//auto appVersion = GxxUtils::IAppVersion::getInstance();
	//if (appVersion)
	//{
	//	uint32_t version = appVersion->getVersionInt();
	//	versionInt_ = boost::lexical_cast<std::string>(version);

	//	std::wstring versionStr = appVersion->getVersionString();
	//	versionStr_ = StringHelper::WtoUTF8(versionStr);
	//}

	//CREATE_PROPERTY(PROP_VERSION_INT, versionInt_);
	//CREATE_PROPERTY(PROP_VERSION_STRING, versionStr_);

	//CREATE_METHOD(MTD_CLOSEWINDOW);
	//CREATE_METHOD(MTD_MAXIMISEWINDOW);
	//CREATE_METHOD(MTD_MINIMISEWINDOW);
	//CREATE_METHOD(MTD_NORMALISEWINDOW);
	//CREATE_METHOD(MTD_DRAGWINDOW);
	//CREATE_METHOD(MTD_OPENSETTINGSWINDOW);
	//CREATE_METHOD(MTD_ADJUSTRECENTCONTACTWIDGET);
	//CREATE_METHOD(MTD_ADJUSTSTATUSMENU);
	//CREATE_METHOD(MTD_LAUNCH_URL);
	//CREATE_METHOD(MTD_OPEN_NOTIFICATION_CENTER);
	//CREATE_METHOD(MTD_SIGNOUT);

	//CREATE_EVENT(EV_THEME_CHANGED);
	//CREATE_EVENT(EV_SHOW_RECENT_CONTACT);
	//CREATE_EVENT(EV_SHOW_SPECIFIC_APPPAGE);
	//CREATE_EVENT(EV_REQUEST_RECENT_CONTACT_COORDINATES);
	//CREATE_EVENT(EV_COUNTRY_LANGUAGE_UPDATED);
	//CREATE_EVENT(EV_IM_USERINFO_UPDATED);
	//CREATE_EVENT(EV_AVATAR_UPDATED);
	//CREATE_EVENT(EV_IM_USERGPPINFO_UPDATED);
	//CREATE_EVENT(EV_AVATAR_UPDATED);
	//CREATE_EVENT(EV_IM_USERSTATUS_UPDATED);
	//CREATE_EVENT(EV_CCU_UPDATED);
	//CREATE_EVENT(EV_APP_LAUNCHED);
	//CREATE_EVENT(EV_APP_QUIT);
	//CREATE_EVENT(EV_INSTALLED_APPS_UPDATED);
	//CREATE_EVENT(EV_INSTALLED_UNITS_UPDATED);
	//CREATE_EVENT(EV_APP_INSTALL_START);
	//CREATE_EVENT(EV_APP_UNINSTALLED);
	//CREATE_EVENT(EV_IM_USER_ACCOUNTINFO_UPDATED);

	//CREATE_EVENT(EV_WINDOWSIZE_CHANGED);
	//CREATE_EVENT(EV_UPDATE_UNREAD_NOTIFICATIONS);
}

CefRefPtr<CefV8Value> QCefClient::self()
{
	return self_;
}

void QCefClient::TriggerEvent(CefRefPtr<CefV8Context> context, 
	const CefString& name, 
	const CefV8ValueList& args)
{
	auto it = eventMap_.find(name);
	if (it != eventMap_.end() && it->second)
	{
		if (it->second->IsFunction())
		{
			it->second->ExecuteFunctionWithContext(context, self_, args);
		}
	}
	
}

void QCefClient::attatchToObject(CefRefPtr<CefV8Value> obj)
{
	obj->SetValue(OBJECT_NAME, self_,
		V8_PROPERTY_ATTRIBUTE_READONLY);
}

bool QCefClient::Execute(const CefString& name,
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

	return browser_->SendProcessMessage(PID_BROWSER, msg);
}

bool QCefClient::Get(const CefString& name,
	const CefRefPtr<CefV8Value> object,
	CefRefPtr<CefV8Value>& retval,
	CefString& exception)
{
	return true;
}

bool QCefClient::Set(const CefString& name,
	const CefRefPtr<CefV8Value> object,
	const CefRefPtr<CefV8Value> value,
	CefString& exception)
{
	auto it = eventMap_.find(name);
	if (it != eventMap_.end())
	{
		if (!value->IsFunction())
		{
			exception = "Invalid arguments; expecting a single function";
		}
		else
		{
			it->second = value;
		}
	}
	
	return false;
}

