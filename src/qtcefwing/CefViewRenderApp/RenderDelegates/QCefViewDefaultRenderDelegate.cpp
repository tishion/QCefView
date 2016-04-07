#include "stdafx.h"

#pragma region project_headers
#include "QCefViewDefaultRenderDelegate.h"
#include "QCefClient.h"
#pragma endregion project_headers

namespace QCefViewDefaultRenderDelegate
{
	void CreateBrowserDelegate(QCefViewRenderApp::RenderDelegateSet& delegates)
	{
		delegates.insert(new RenderDelegate());
	}

	RenderDelegate::RenderDelegate()
	{

	}

	void RenderDelegate::OnWebKitInitialized(CefRefPtr<QCefViewRenderApp> app)
	{
		CefMessageRouterConfig config;
		config.js_query_function = QCEF_QUERY_NAME;
		config.js_cancel_function = QCEF_QUERY_CANCEL_NAME;
		render_message_router_ = CefMessageRouterRendererSide::Create(config);
	}

	void RenderDelegate::OnContextCreated(CefRefPtr<QCefViewRenderApp> app,
		CefRefPtr<CefBrowser> browser, 
		CefRefPtr<CefFrame> frame, 
		CefRefPtr<CefV8Context> context)
	{
		render_message_router_->OnContextCreated(browser, frame, context);

		// insert the QCefClient Object into this frame.window object
		CefRefPtr<CefV8Value> objWindow = context->GetGlobal();
		CefRefPtr<QCefClient> objClient = new QCefClient(browser, frame);
		objWindow->SetValue(QCEF_OBJECT_NAME, 
			objClient->GetObject(), V8_PROPERTY_ATTRIBUTE_READONLY);

		int browserId = browser->GetIdentifier();
		int64 frameId = frame->GetIdentifier();

		auto itb = mapBrowser_.find(browserId);
		if (itb != mapBrowser_.end())
		{
			FrameID2QCefClientMap& mapFrame = itb->second;
			mapFrame[frameId] = objClient;
		}
		else
		{
			FrameID2QCefClientMap mapFrame;
			mapFrame[frameId] = objClient;
			mapBrowser_[browserId] = mapFrame;
		}
	}

	void RenderDelegate::OnContextReleased(CefRefPtr<QCefViewRenderApp> app,
		CefRefPtr<CefBrowser> browser, 
		CefRefPtr<CefFrame> frame, 
		CefRefPtr<CefV8Context> context)
	{
		render_message_router_->OnContextReleased(browser, frame, context);

		int browserId = browser->GetIdentifier();
		int64 frameId = frame->GetIdentifier();

		auto itb = mapBrowser_.find(browserId);
		if (itb != mapBrowser_.end())
		{
			FrameID2QCefClientMap& mapFrame = itb->second;
			auto itf = mapFrame.find(frameId);
			if (itf != mapFrame.end())
			{
				mapFrame.erase(itf);
			}
			if (mapFrame.empty())
			{
				mapBrowser_.erase(itb);
			}
		}
	}

	bool RenderDelegate::OnProcessMessageReceived(CefRefPtr<QCefViewRenderApp> app,
		CefRefPtr<CefBrowser> browser, 
		CefProcessId source_process, 
		CefRefPtr<CefProcessMessage> message)
	{
		if (render_message_router_->OnProcessMessageReceived(browser, source_process, message))
		{
			return true;
		}

		if (OnTriggerEventNotifyMessage(browser, source_process, message))
		{
			return true;
		}

		return false;
	}

	bool RenderDelegate::OnTriggerEventNotifyMessage(CefRefPtr<CefBrowser> browser,
		CefProcessId source_process, 
		CefRefPtr<CefProcessMessage> message)
	{
		if (message->GetName() == TRIGGEREVENT_NOTIFY_MESSAGE)
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
				else if (messageArguments->GetType(i) == VTYPE_NULL)
				{
					arguments.push_back(
						CefV8Value::CreateInt(0));
				}
				else
				{
					// do log
					__noop(_T("QCefView"), _T("Unknow Type!"));
				}
			}

			ExecuteEventHandler(browser, funcName, arguments);
			return true;
		}

		return false;
	}

	void RenderDelegate::ExecuteEventHandler(CefRefPtr<CefBrowser> browser, 
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
			CefRefPtr<CefV8Value> qcef = window->GetValue(QCEF_OBJECT_NAME);
			CefRefPtr<CefV8Value> handler = qcef->GetValue(name);
			if (handler->IsFunction())
			{
				handler->ExecuteFunctionWithContext(context, qcef, arguments);
			}
		}
	}

}
