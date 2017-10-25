QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


# Get version from git tags
VERSION = $$system(git --git-dir $$PWD/.git --work-tree $$PWD describe --always --tags)

QMAKE_TARGET_PRODUCT = "Renderman Denoise UI"
QMAKE_TARGET_COMPANY = "Nankin CGI"
QMAKE_TARGET_COPYRIGHT = "Copyright (c) by $${QMAKE_TARGET_COMPANY}"

DEFINES += APP_VERSION=\"\\\"$${VERSION}\\\"\" \
           APP_PRODUCT=\"\\\"$${QMAKE_TARGET_PRODUCT}\\\"\" \
           APP_COMPANY=\"\\\"$${QMAKE_TARGET_COMPANY}\\\"\" \
           APP_COPYRIGHT=\"\\\"$${QMAKE_TARGET_COPYRIGHT}\\\"\"


#VERSION = $$GIT_VERSION
win32 {
    VERSION ~= s/-\d+-g[a-f0-9]{6,}//
}

# VERIFICAR PORQUE ESTÁ DANDO ERRO XXXXXXXXXXXXXXXXXXXXX
#macx {
#    INFO_PLIST_PATH = $$shell_quote($${OUT_PWD}/$${TARGET}.app/Contents/Info.plist)
#    QMAKE_POST_LINK += /usr/libexec/PlistBuddy -c \"Set :CFBundleShortVersionString $${VERSION}\" $${INFO_PLIST_PATH}
#}



TARGET = $${QMAKE_TARGET_PRODUCT}
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++14

SOURCES += main.cpp\
        mainwindow.cpp \
        pxrdenoise.cpp \
        preferencesUI.cpp \
        settings.cpp \
        utils.cpp

HEADERS += mainwindow.h \
            pxrdenoise.h \
            preferencesUI.h \
            settings.h \
            utils.h

FORMS += mainwindow.ui \
            preferencesUI.ui

RESOURCES += \
            resource.qrc

# set app icons
RC_ICONS = app.ico
macx:ICON = $${PWD}/app.icns

CONFIG(release, debug|release) {
DEFINES += QT_NO_DEBUG_OUTPUT
}

# optimization flag
QMAKE_CXXFLAGS_RELEASE += -O3
