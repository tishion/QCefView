#pragma once

#pragma region cef_headers
#include <include/cef_v8.h>
#pragma endregion cef_headers

class QCefClient
	: public CefV8Value
{
	class Accessor
		: public CefV8Accessor
	{
	public:
		virtual bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception) override;

		virtual bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception) override;

	private:
		IMPLEMENT_REFCOUNTING(Accessor);
	};

	class V8Handler
		: public CefV8Handler
	{
	public:
		V8Handler(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame);
		virtual bool Execute(const CefString& function, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) override;

	private:
		CefRefPtr<CefBrowser>	browser_;
		CefRefPtr<CefFrame>		frame_;

	private:
		IMPLEMENT_REFCOUNTING(V8Handler);
	};

public:
	QCefClient(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame);

#pragma region CefV8Value interface forwarder
	virtual bool IsValid() override
	{
		return object_->IsValid();
	}

	virtual bool IsUndefined() override
	{
		return object_->IsUndefined();
	}

	virtual bool IsNull() override 
	{
		return object_->IsNull();
	}

	virtual bool IsBool() override
	{
		return object_->IsBool();
	}

	virtual bool IsInt() override
	{
		return object_->IsInt();
	}

	virtual bool IsUInt() override
	{
		return object_->IsUInt();
	}

	virtual bool IsDouble() override
	{
		return object_->IsDouble();
	}

	virtual bool IsDate() override
	{
		return object_->IsDate();
	}

	virtual bool IsString() override
	{
		return object_->IsString();
	}

	virtual bool IsObject() override
	{
		return object_->IsObject();
	}

	virtual bool IsArray() override
	{
		return object_->IsArray();
	}

	virtual bool IsFunction() override
	{
		return object_->IsFunction();
	}

	virtual bool IsSame(CefRefPtr<CefV8Value> that) override
	{
		return object_->IsSame(that);
	}

	virtual bool GetBoolValue() override
	{
		return object_->GetBoolValue();
	}

	virtual int32 GetIntValue() override
	{
		return object_->GetIntValue();
	}

	virtual uint32 GetUIntValue() override
	{
		return object_->GetUIntValue();
	}

	virtual double GetDoubleValue() override
	{
		return object_->GetDoubleValue();
	}

	virtual CefTime GetDateValue() override
	{
		return object_->GetDateValue();
	}

	virtual CefString GetStringValue() override
	{
		return object_->GetStringValue();
	}

	virtual bool IsUserCreated() override
	{
		return object_->IsUserCreated();
	}

	virtual bool HasException() override
	{
		return object_->HasException();
	}

	virtual CefRefPtr<CefV8Exception> GetException() override
	{
		return object_->GetException();
	}

	virtual bool ClearException() override
	{
		return object_->ClearException();
	}

	virtual bool WillRethrowExceptions() override
	{
		return object_->WillRethrowExceptions();
	}

	virtual bool SetRethrowExceptions(bool rethrow) override
	{
		return object_->SetRethrowExceptions(rethrow);
	}

	virtual bool HasValue(const CefString& key) override
	{
		return object_->HasValue(key);
	}

	virtual bool HasValue(int index) override
	{
		return object_->HasValue(index);
	}

	virtual bool DeleteValue(const CefString& key) override
	{
		return object_->DeleteValue(key);
	}

	virtual bool DeleteValue(int index) override
	{
		return object_->DeleteValue(index);
	}

	virtual CefRefPtr<CefV8Value> GetValue(const CefString& key) override
	{
		return object_->GetValue(key);
	}

	virtual CefRefPtr<CefV8Value> GetValue(int index) override
	{
		return object_->GetValue(index);
	}

	virtual bool SetValue(const CefString& key, CefRefPtr<CefV8Value> value, PropertyAttribute attribute) override
	{
		return object_->SetValue(key, value, attribute);
	}

	virtual bool SetValue(int index, CefRefPtr<CefV8Value> value) override
	{
		return object_->SetValue(index, value);
	}

	virtual bool SetValue(const CefString& key, AccessControl settings, PropertyAttribute attribute) override
	{
		return object_->SetValue(key, settings, attribute);
	}

	virtual bool GetKeys(std::vector<CefString>& keys) override
	{
		return object_->GetKeys(keys);
	}

	virtual bool SetUserData(CefRefPtr<CefBase> user_data) override
	{
		return object_->SetUserData(user_data);
	}

	virtual CefRefPtr<CefBase> GetUserData() override
	{
		return object_->GetUserData();
	}

	virtual int GetExternallyAllocatedMemory() override
	{
		return object_->GetExternallyAllocatedMemory();
	}

	virtual int AdjustExternallyAllocatedMemory(int change_in_bytes) override
	{
		return object_->AdjustExternallyAllocatedMemory(change_in_bytes);
	}

	virtual int GetArrayLength() override
	{
		return object_->GetArrayLength();
	}

	virtual CefString GetFunctionName() override
	{
		return object_->GetFunctionName();
	}

	virtual CefRefPtr<CefV8Handler> GetFunctionHandler() override
	{
		return object_->GetFunctionHandler();
	}

	virtual CefRefPtr<CefV8Value> ExecuteFunction(CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments) override
	{
		return object_->ExecuteFunction(object, arguments);
	}

	virtual CefRefPtr<CefV8Value> ExecuteFunctionWithContext(CefRefPtr<CefV8Context> context, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments) override
	{
		return object_->ExecuteFunctionWithContext(context, object, arguments);
	}
#pragma endregion

	 operator CefRefPtr<CefV8Value>();

private:
	CefRefPtr<CefV8Value>	object_;
	CefRefPtr<CefBrowser>	browser_;
	CefRefPtr<CefFrame>		frame_;

private:
	IMPLEMENT_REFCOUNTING(QCefClient);

};
