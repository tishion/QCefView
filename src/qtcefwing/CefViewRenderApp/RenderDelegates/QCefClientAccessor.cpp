#include "stdafx.h"
#pragma region projet_headers
#include "QCefClientAccessor.h"
#pragma endregion projet_headers

//////////////////////////////////////////////////////////////////////////

bool QCefClientAccessor::Get(const CefString& name,
	const CefRefPtr<CefV8Value> object,
	CefRefPtr<CefV8Value>& retval,
	CefString& exception)
{
	return true;
}

bool QCefClientAccessor::Set(const CefString& name,
	const CefRefPtr<CefV8Value> object,
	const CefRefPtr<CefV8Value> value,
	CefString& exception)
{
	if (!value->IsFunction())
	{
		exception = "Invalid arguments; expecting a single function";
	}
	else
	{
		object->SetValue(name, value, V8_PROPERTY_ATTRIBUTE_NONE);
	}

	return false;
}


