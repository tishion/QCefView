QCefView - A Qt widget integrated with CEF
===============

QCefView is a Qt widget integrated with Chrome Embedded Framework. You can use QCefView without writing any code relating to CEF code. This Qt widget is distributed in binary module and **LGPL** licensed.

Why use QCefView
----------------

There are some UI frameworks developed with CEF, such as Electron and others. But Electron is over-encapsulated with CEF, you can only develop your application with it by writing javascript code. If you need to use native code in your application while CEF is also needed, Electron is not the good choice in this situation. You can do the integration by youself totally, of cause you need to do much work about communication between web code and native code. And most time this is repetitive work.

Now you can try to use QCefView to develop your application. Just use it like any other QWidgets. QCefView widget provides several methods to do communication between native C++ code and web javascript code. You don't need to write the communicating business logical. 

----------

How to use QCefView
----------

* First of all, check out the QCefView repository. 

* Deploy Qt SDK

    Because there are different versions of Qt and Visual Studio, you need to determine the version of Qt and Visual Studio you want to use in your development. As you know, once you have settled down with specified version of Visual Studio, you must use the corresponding version of Qt SDK. Here we use Visual Studio 2015. 

* Download CEF binary distribution files
    
    We use the binary distribution version, you can get them from here

    > [https://cefbuilds.com/](https://cefbuilds.com/)
    
    Here we use branch 2526, download the **cef_binary_3.2526.1373.gb660893_windows32**. 

* Build **libcef_dll_wrapper.lib**

    You need to build the libcef_dll_wrapper.lib with your development environment
    > **Note**:
    
    > - Use the same configuration of Runtime Library as the QT SDK you used 

* Collect CEF files
    
    Put header files, lib files and binary files into QCefView\dep\cef folder, keep the structure of this folder the same with [this](https://github.com/tishion/QCefView/tree/master/dep/cef)
   
* Build QCefViewSDK & Test Demo
    
    Open the QCefView solution and build all the projects. Make sure to build the Test project last. After you build the QCefView you will get the QCefViewSdk folder, this includes all the files QCefView needed. You can deploy this SDK into your development environment and develop Qt+CEF applications with it.

There is one test demo project in the QCefView Solution

![](https://raw.githubusercontent.com/tishion/QCefView/gh-pages/images/Test.jpg)

---------

Document
---------

- Qt Side:
---

---
- QCefView Class

    Consturtors: 
    > QCefView(const QString url, QWidget* parent = 0)
    >
    > url:
    >
    > parent:
        
    Methods:
    > void navigateToString(const QString& content, const QString& url)
    >
    > void navigateToUrl(const QString& url)
    >
    > bool browserCanGoBack()
    >
    > bool browserCanGoForward()
    >
    > void browserGoBack()
    >
    > void browserGoForward()
    >
    > bool browserIsLoading()
    >
    > void browserReload()
    >
    > void browserStopLoad()
    >
    > bool triggerEvent(int frameId, const QString& name, const QCefEvent& event)
    >
    > bool broadcastEvent(const QString& name, const QCefEvent& event)
    >
    > virtual void onLoadStateChange(bool isLoading)
    >	
    > virtual void onLoadStart()
    >	
    > virtual void onLoadEnd(int httpStatusCode)
    >	
    > virtual void onLoadError(int errorCode, const QString& errorMsg, const QString& failedUrl)
    >
    > WId getCefWinId()
        
    Slots:
    > virtual void processQCefUrlRequest(const QString& url);
    >	
    > virtual void processQCefQueryRequest(QCefQuery query);
    >
    > virtual void onInvokeMethodNotify(int browserId, int frameId,const QString method, const QVariantList arguments);

---
- QCefSettings Class

    > void setBrowserSubProcessPath(const QString& path)
    >
    > const QString browserSubProcessPath()
    > 
    > void setResourceDirectoryPath(const QString& path)
    >
    > const QString resourceDirectoryPath()
    > 
    > void setLocalesDirectoryPath(const QString& path)
    >
    > const QString localesDirectoryPath()
    > 
    > void setUserAgent(const QString& agent)
    >
    > const QString userAgent()
    
---
- QCefQuery Class

    Methods: 
    > const QString reqeust() const
    > 
    > void responseSuccess(const QString& response) const
    > 
    > void responseFailure(int ec, const QString& response) const
    > 
    > QCefQuery& operator=(const QCefQuery& other)
    
---
- QCefEvent Class

    Constuctors:
    > QCefEvent();
    >
    > QCefEvent(const char* name);
    > 
    Methods:
    > void setEventName(const char* name);
    > 
    > void setIntProperty(const char* key, int value);
    > 
    > void setDoubleProperty(const char*  key, double value);
    > 
    > void setStringProperty(const char*  key, QString value);
    > 
    > void setBoolProperty(const char*  key, bool value);


---

Web Side:
---

---
- QCefClient Object

    Methods:
    > invokeMethod(name, args, ...)
    >
    > addEventListener(name, listener)
    >
    > removeEventListener(name, listener)
 
---
    

- QCef Query

    Functions:
    > QCefQuery
    >
    > QCefQueryCancel

---
  
- QCef Url Request

    Protocol:
    > qcef://xxxxxx
---