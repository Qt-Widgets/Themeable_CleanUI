#-------------------------------------------------
#
# XeTestUI.pro
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XeTestUI
TEMPLATE = app
CONFIG += app_bundle

SOURCES += $$files(src/xenia/app/*.cc, false)

HEADERS += $$files(src/xenia/app/*.h, false)

INCLUDEPATH += third_party/IconFontCppHeaders

win32 {
    # Only include / compile these files on Windows
    SOURCES += $$files(src/xenia/app/win/*.cc, true)

    HEADERS += $$files(src/xenia/app/win/*.h, true)

    LIBS += dwmapi.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib
}

mac {
    LIBS += -framework Foundation -framework Cocoa
    INCLUDEPATH += /System/Library/Frameworks/Foundation.framework/Versions/C/Headers
}

RESOURCES += \
    window.qrc

DISTFILES +=
