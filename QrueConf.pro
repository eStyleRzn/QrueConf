TEMPLATE = app
TARGET = QrueConf

CONFIG -= debug_and_release
CONFIG += rtti exceptions
CONFIG += c++11

QT += core gui widgets axcontainer

QMAKE_CXXFLAGS += -D__STDC_CONSTANT_MACROS

# Set up output folder
DESTDIR = $$absolute_path($$PWD/Build)

# Windows logic
# Attention!!! The folders below will affect the logic of installer builder, since they define binaries output folder
win32{
    CONFIG(debug, debug|release){
      DESTDIR = $$DESTDIR/WinDebug

      MY_PLATFORM_PLUGINS += $$[QT_INSTALL_PLUGINS]/platforms/qwindowsd.dll

      MY_LIB_FILES += $$[QT_INSTALL_BINS]/Qt5Cored.dll
      MY_LIB_FILES += $$[QT_INSTALL_BINS]/Qt5Guid.dll
      MY_LIB_FILES += $$[QT_INSTALL_BINS]/Qt5Widgetsd.dll
   } else {
      DESTDIR = $$DESTDIR/WinRelease
   }
}

OBJECTS_DIR = $${DESTDIR}/gen/obj
MOC_DIR     = $${DESTDIR}/gen/moc
RCC_DIR     = $${DESTDIR}/gen/res
UI_DIR      = $${DESTDIR}/gen/uic

TYPELIBS = $$system(dumpcpp -n TrueConf -o $$PWD/Res/CallX/TrueConf_CallX $$PWD/Res/CallX/TrueConf_CallX.ocx)

INCLUDEPATH += $$PWD/Res/CallX

## Define what files are 'extra_libs' and where to put them
ExtraLibs.files = $$MY_LIB_FILES
ExtraLibs.path = $${DESTDIR}

ExtraPlatforms.files += $$MY_PLATFORM_PLUGINS
ExtraPlatforms.path += $${DESTDIR}/platforms

## Tell qmake to add the moving of them to the 'install' target
INSTALLS += ExtraLibs \
    ExtraPlatforms \

SOURCES += $$PWD/Src/main.cpp \
    $$PWD/Src/MainWindow.cpp \
    $$PWD/Res/CallX/TrueConf_CallX.cpp \
    $$PWD/Src/WtSettings.cpp \
    $$PWD/Src/WtStartConf.cpp \
    $$PWD/Src/VideoConfProvider.cpp \
    $$PWD/Src/ServerNotifyProcessor.cpp \
    $$PWD/Src/AddressBook.cpp \
    $$PWD/Src/DlgContacts.cpp \
    $$PWD/Src/DlgIncomingCall.cpp \
    $$PWD/Src/DlgCreateConf.cpp \
    $$PWD/Src/DlgShareScreen.cpp

HEADERS += $$PWD/Src/MainWindow.h \
    $$PWD/Res/CallX/TrueConf_CallX.h \
    $$PWD/Src/WtSettings.h \
    $$PWD/Src/WtStartConf.h \
    $$PWD/Src/VideoConfProvider.h \
    $$PWD/Src/ServerNotifyProcessor.h \
    $$PWD/Src/AddressBook.h \
    $$PWD/Src/DlgContacts.h \
    $$PWD/Src/DlgIncomingCall.h \
    $$PWD/Src/DlgCreateConf.h \
    $$PWD/Src/DlgShareScreen.h

FORMS += $$PWD/Src/MainWindow.ui \
    $$PWD/Src/WtSettings.ui \
    $$PWD/Src/WtStartConf.ui \
    $$PWD/Src/VideoConfProvider.ui \
    $$PWD/Src/DlgContacts.ui \
    $$PWD/Src/DlgIncomingCall.ui \
    $$PWD/Src/DlgCreateConf.ui \
    $$PWD/Src/DlgShareScreen.ui

# This must be always the last string in the file, since it prints the final values
include($$PWD/CommonMessages.pri)
