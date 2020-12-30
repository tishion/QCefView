#ifndef QCEFCOMMON_H
#define QCEFCOMMON_H
#if defined(_MSVC_) && _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// <summary>
///
/// </summary>
#define QCEF_SCHEMA "qcef"

/// <summary>
///
/// </summary>
#define QCEF_QUERY_NAME "QCefQuery"

/// <summary>
///
/// </summary>
#define QCEF_QUERY_CANCEL_NAME "QCefQueryCancel"

/// <summary>
///
/// </summary>
#define QCEF_OBJECT_NAME "QCefClient"

/// <summary>
///
/// </summary>
#define QCEF_BRIDGE_OBJ_NAME_KEY "bridge-obj-name"

/// <summary>
/// QCefClient.invokeMethod("method_name", ...)
/// </summary>
#define QCEF_INVOKEMETHOD "invokeMethod"

/// <summary>
/// QCefClient.addEventListener(type, listener)
/// </summary>
#define QCEF_ADDEVENTLISTENER "addEventListener"

/// <summary>
/// QCefClient.removeEventListener(type, listener)
/// </summary>
#define QCEF_REMOVEEVENTLISTENER "removeEventListener"

/// <summary>
/// this message is sent from render process to browser process
/// and is processed in the Qt UI thread
///
/// format
/// msg.name
///   msg.arg[0]: frame id
///   msg.arg[1]: function name
///   msg.arg[2~...]: function parameters
/// </summary>
#define INVOKEMETHOD_NOTIFY_MESSAGE "QCefClient#InvokeMethodNotify"

/// <summary>
/// this message is sent from browser process to render process
/// and is processed in the CefRenderer_Main thread
///
/// format:
///   msg.name:
///	  msg.arg[0]: frame id
///	  msg.arg[1]: function name
///	  msg.arg[2~...]: function parameters
/// </summary>
#define TRIGGEREVENT_NOTIFY_MESSAGE "QCefClient#TriggerEventNotify"

/// <summary>
///
/// </summary>
#define RENDER_PROCESS_NAME "QCefWing.exe"

/// <summary>
///
/// </summary>
#define RESOURCE_DIRECTORY_NAME "resources"

/// <summary>
///
/// </summary>
#define LOCALES_DIRECTORY_NAME "locales"

/// <summary>
///
/// </summary>
#define QCEF_USER_AGENT "START/1.0 (Windows; en-us)"

#endif
