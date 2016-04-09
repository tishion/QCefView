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
		auto it = mapBrowser_.find(browser->GetIdentifier());
		if (it != mapBrowser_.end())
		{
			if (message->GetName() == TRIGGEREVENT_NOTIFY_MESSAGE)
			{
				CefRefPtr<CefListValue> messageArguments = message->GetArgumentList();
				if (messageArguments && (messageArguments->GetSize() >= 2))
				{
					int idx = 0;
					if (CefValueType::VTYPE_INT == messageArguments->GetType(idx))
					{
						int frameId = messageArguments->GetInt(idx++);

						if (CefValueType::VTYPE_STRING == messageArguments->GetType(idx))
						{
							CefString eventName = messageArguments->GetString(idx++);

							if (CefValueType::VTYPE_DICTIONARY == messageArguments->GetType(idx))
							{
								CefRefPtr<CefDictionaryValue> dict = messageArguments->GetDictionary(idx++);
								std::vector<int64> frameIdList;
								if (frameId)
								{
									frameIdList.push_back(frameId);
								}
								else
								{
									// broadcast
									browser->GetFrameIdentifiers(frameIdList);
								}
								ExecuteEventListener(browser, frameIdList, eventName, dict);
								return true;
							}
						}
					}
				}
			}
		}

		return false;
	}

	void RenderDelegate::ExecuteEventListener(CefRefPtr<CefBrowser> browser,
		std::vector<int64> frameIdList,
		const CefString& name,
		CefRefPtr<CefDictionaryValue> dict)
	{
		auto itb = mapBrowser_.find(browser->GetIdentifier());
		if (itb != mapBrowser_.end())
		{
			FrameID2QCefClientMap& frameMap = itb->second;

			for (int64 frameId : frameIdList)
			{
				CefRefPtr<CefFrame> frame = browser->GetFrame(frameId);
				if (frame)
				{
					auto itf = frameMap.find(frameId);
					if (itf != frameMap.end())
					{
						const CefRefPtr<QCefClient>& objClient = itf->second;
						objClient->ExecuteEventListener(name, dict);
					}
				}
			}
		}
	}

}
