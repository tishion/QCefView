#include "stdafx.h"

#pragma region project_headser
#include "QCefClientObjectManager.h"
#include "QCefClientAccessor.h"
#pragma endregion project_headser

QCefClientObjectManager::QCefClientObjectManager()
{
}


QCefClientObjectManager::~QCefClientObjectManager()
{
}

void QCefClientObjectManager::OnContextCreated(CefRefPtr<CefBrowser> browser, 
	CefRefPtr<CefFrame> frame, 
	CefRefPtr<CefV8Context> context)
{
	//CefRefPtr<QCefClientAccessor> accessor = new QCefClientAccessor();
	//CefRefPtr<CefV8Value> objQCefClient = CefV8Value::CreateObject(accessor);

	//// Add methods and event handler for objQCefClient
	//InitializeQCefClientObject(objQCefClient, browser, frame);

	//CefRefPtr<CefV8Value> objWindow = context->GetGlobal();
	//objWindow->SetValue(OBJECT_NAME, objQCefClient, V8_PROPERTY_ATTRIBUTE_READONLY);
}

void QCefClientObjectManager::OnContextReleased(CefRefPtr<CefBrowser> browser, 
	CefRefPtr<CefFrame> frame, 
	CefRefPtr<CefV8Context> context)
{
}

bool QCefClientObjectManager::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
	CefProcessId source_process, 
	CefRefPtr<CefProcessMessage> message)
{
	if (message->GetName() == TRIGGER_EVENT_MESSAGE_NAME)
	{
		CefRefPtr<CefListValue> messageArguments = message->GetArgumentList();
		if (messageArguments == NULL
			|| (messageArguments->GetSize() == 0))
		{
			return false;
		}
		CefString funcName = messageArguments->GetString(0);

		CefV8ValueList arguments;
		for (std::size_t i = 1; i < messageArguments->GetSize(); ++i)
		{
			if (messageArguments->GetType(i) == VTYPE_BOOL)
			{
				arguments.push_back(
					CefV8Value::CreateBool(messageArguments->GetBool(i)));
			}
			else if (messageArguments->GetType(i) == VTYPE_INT)
			{
				arguments.push_back(
					CefV8Value::CreateInt(messageArguments->GetInt(i)));
			}
			else if (messageArguments->GetType(i) == VTYPE_DOUBLE)
			{
				arguments.push_back(
					CefV8Value::CreateDouble(messageArguments->GetDouble(i)));
			}
			else if (messageArguments->GetType(i) == VTYPE_STRING)
			{
				arguments.push_back(
					CefV8Value::CreateString(messageArguments->GetString(i)));
			}
			else
			{
				__noop(_T("QCefView"), _T("Unknow Type!"));
			}
		}

		TriggerEventMessage(browser, funcName, arguments);
		return true;
	}

	return false;
}

void QCefClientObjectManager::InitializeQCefClientObject(CefRefPtr<CefV8Value> obj,
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame)
{
	// create property
	CefRefPtr<CefV8Value> property = CefV8Value::CreateString("PROPERTY_VAL");
	obj->SetValue("PROPERTY_NAME", property, V8_PROPERTY_ATTRIBUTE_READONLY);

	// create function
	CefRefPtr<QCefClientV8Handler> handler = new QCefClientV8Handler(browser, frame);
	CefRefPtr<CefV8Value> funtion = CefV8Value::CreateFunction("METHOD_NAME", handler);
	obj->SetValue("METHOD_NAME", funtion, V8_PROPERTY_ATTRIBUTE_READONLY);

	// create event
	CefRefPtr<CefV8Value> eventHandler = CefV8Value::CreateUndefined();
	obj->SetValue("EVENT_NAME", V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE);
}

void QCefClientObjectManager::TriggerEventMessage(CefRefPtr<CefBrowser> browser, 
	const CefString& name,
	const CefV8ValueList& arguments)
{
	std::vector<int64> idList;
	browser->GetFrameIdentifiers(idList);
	for (int64 id : idList)
	{
		CefRefPtr<CefFrame> frame = browser->GetFrame(id);
		CefRefPtr<CefV8Context> context = frame->GetV8Context();
		CefRefPtr<CefV8Value> window = context->GetGlobal();
		CefRefPtr<CefV8Value> qcef = window->GetValue(OBJECT_NAME);
		CefRefPtr<CefV8Value> handler = qcef->GetValue(name);
		if (handler->IsFunction())
		{
			handler->ExecuteFunctionWithContext(context, qcef, arguments);
		}
	}
}
