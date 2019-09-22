QCefView - A Qt widget integrated with CEF
===============

QCefView is a Qt widget integrated with Chrome Embedded Framework. You can use QCefView without writing any code relating to CEF code. This Qt widget is distributed in binary module and **LGPL** licensed.

Why use QCefView
----------------

There are some UI frameworks developed with CEF, such as Electron and others. But Electron is over-encapsulated with CEF, you can only develop your application with it by writing javascript code. If you need to use native code in your application while CEF is also needed, Electron is not the good choice in this situation. You can do the integration by youself totally, of cause you need to do much work about communication between web code and native code. And most time this is repetitive work.

Now you can try to use QCefView to develop your application. Just use it like any other QWidgets. QCefView widget provides several methods to do communication between native C++ code and web javascript code. You don't need to write the communicating business logical. 

----------

Build instruction:
----------

1. Download and install [CMake](https://cmake.org/)
2. Download and install Qt SDK from [Qt Downloads](https://download.qt.io/archive/qt/)
3. Download CEF binary distribution [Chromium Embedded Framework (CEF) Automated Builds](http://opensource.spotify.com/cefbuilds/index.html) and extract it to ***dep*** directory, for example:
    ```
    root
    ├─dep
    │  └─cef_binary_76.1.13+gf19c584+chromium-76.0.3809.132_windows64
    ├─src
    └─test
    ```
4. Modify the [config.cmake](config.cmake) to set the required build configurations
5. Just use CMake to build the project, for example:
    ``` bat
    REM create the build folder 
    mkdir build.win && cd build.win

    REM generate and build the project
    cmake .. && cmake --build .
    ```

> Note:
When I start the reforming I use Qt 5.12.4 and CEF cef_binary_76.1.13+gf19c584+chromium-76.0.3809.132_windows64. You need to make sure the version you are choosing is compatible with the code in this repo.

6. Collect all build artifacts in ***outpu*** folder

![](https://raw.githubusercontent.com/tishion/QCefView/gh-pages/images/Test.jpg)

---------

Document 
---------

Please refer to the soruce code.

Qt Side
----
- [QCefEvent](https://github.com/tishion/QCefView/blob/master/src/QCefView/inc/QCefEvent.h)

- [QCefQuery](https://github.com/tishion/QCefView/blob/master/src/QCefView/inc/QCefQuery.h) 
 
- [QCefSettings](https://github.com/tishion/QCefView/blob/master/src/QCefView/inc/QCefSetting.h)
 
- [QCefView](https://github.com/tishion/QCefView/blob/master/src/QCefView/inc/QCefView.h) 
 
 
Web Side:
---

---
- QCefClient Object

    Methods:
    
    > invokeMethod(name, args, ...)
    
    Sample: 
    ```javascript
    QCefClient.invokeMethod("TestMethod", 1, false, "arg3");
    ```
    
    > addEventListener(name, listener)
    
    Sample: 
    ```javascript
    QCefClient.addEventListener(
        "colorChange",                      // Event name
        function onColorChanged (event) {   // Event handler callback
            document.getElementById("main").style.backgroundColor = event["color"];
    });
    ```
    
    > removeEventListener(name, listener)
        
    Sample: 
    ```javascript
    QCefClient.removeEventListener("colorChange", onColorChanged);
    // onColorChanged is not an anonymous function
    ```
---

- QCef Query

    Functions:
    
    > QCefQuery
    
    > QCefQueryCancel
    
    Sample:
    ```javascript
    var queryId = window.QCefQuery({
        request: "Hello, this message is sent from javascript code.",
        onSuccess: function(response) {
            alert(response);
        },
        onFailure: function(error_code, error_message) {
            alert(error_message);
        }
    });
    
    //
    
    window.QCefQueryCancel(queryId);
    ```
---
  
- QCef Url Request

    Protocol:
    
    > qcef://xxxxxx
    
    Sampe:
    ```html
    <a href="qcef://test/a/b">qcef://test/a/b</a>
    ```
---
