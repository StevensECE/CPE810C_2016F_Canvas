What we use is libcurl "curl-7.51.0-win32-mingw". To add the external library libcurl, we should address the environment configuration.

Here is the codes should be added to pro. file.

INCLUDEPATH += $$PWD/../curl-7.51.0-win32-mingw/include
DEPENDPATH += $$PWD/../curl-7.51.0-win32-mingw/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../curl-7.51.0-win32-mingw/lib/ -lcurl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../curl-7.51.0-win32-mingw/lib/ -lcurl
LIBS += C:\Users\Gregory\Desktop\learn_curl\build-Learn_Curl-Desktop_Qt_5_7_0_MinGW_32bit-Debug\debug\libcurl.dll

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../curl-7.51.0-win32-mingw/lib/libcurl.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../curl-7.51.0-win32-mingw/lib/libcurldll.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../curl-7.51.0-win32-mingw/lib/curl.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../curl-7.51.0-win32-mingw/lib/curld.lib