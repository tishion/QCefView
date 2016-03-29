#include "stdafx.h"

#pragma region project_headser
#include "QCefClientObjectManager.h"
#pragma endregion project_headser

QCefClientObjectManager::QCefClientObjectManager()
{
	frame_map_.clear();
}


QCefClientObjectManager::~QCefClientObjectManager()
{
	frame_map_.clear();
}

void QCefClientObjectManager::OnContextCreated(CefRefPtr<CefBrowser> browser, 
	CefRefPtr<CefFrame> frame, 
	CefRefPtr<CefV8Context> context)
{
	CefRefPtr<QCefClient> objGxxClient = new QCefClient(
		browser, frame);
	// Add GxxClientObject to windows object
	CefRefPtr<CefV8Value> objWindow = context->GetGlobal();
	objGxxClient->attatchToObject(objWindow);

	FrameGxxClient framGxxClient(frame, objGxxClient);
	frame_map_[frame->GetIdentifier()] = framGxxClient;
}

void QCefClientObjectManager::OnContextReleased(CefRefPtr<CefBrowser> browser, 
	CefRefPtr<CefFrame> frame, 
	CefRefPtr<CefV8Context> context)
{
	FrameMap::iterator it = frame_map_.find(frame->GetIdentifier());
	if (it != frame_map_.end())
	{
		frame_map_.erase(it);
	}
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
				__noop(_T("GxxCefView"), _T("Unknow Type!"));
			}
		}

		for (auto it = frame_map_.begin(); it != frame_map_.end(); it++)
		{
			FrameGxxClient& frameClient = it->second;
			CefRefPtr<CefFrame>& frame = frameClient.first;
			CefRefPtr<QCefClient>& client = frameClient.second;
			client->TriggerEvent(frame->GetV8Context(), funcName, arguments);
		}
		return true;
	}

	return false;
}
