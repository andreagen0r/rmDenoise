QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Get version from git tags
GIT_VERSION = $$system(git --git-dir $$PWD/.git --work-tree $$PWD describe --always --tags)
VERSION = $${GIT_VERSION}

PRODUCT = "Renderman Denoise UI"
COMPANY = "Nankin CGI"
COPYRIGHT = "Copyright (c) by $${COMPANY}"
PRMAN_PROSERVER = "RenderManProServer-21.5"

DEFINES += APP_VERSION=\"\\\"$${GIT_VERSION}\\\"\" \
           APP_PRODUCT=\"\\\"$${PRODUCT}\\\"\" \
           APP_COMPANY=\"\\\"$${COMPANY}\\\"\" \
           APP_COPYRIGHT=\"\\\"$${COPYRIGHT}\\\"\" \
           APP_PRMAN_PROSERVER=\"\\\"$${PRMAN_PROSERVER}\\\"\"

message($${PRODUCT} | $${GIT_VERSION} | $${PRMAN_PROSERVER} | $${COMPANY} | $${COPYRIGHT})


win32 {
    VERSION ~= s/-\d+-g[a-f0-9]{6,}//
}

# VERIFICAR PORQUE ESTÁ DANDO ERRO XXXXXXXXXXXXXXXXXXXXX
#macx {
#    INFO_PLIST_PATH = $$shell_quote($${OUT_PWD}/$${TARGET}.app/Contents/Info.plist)
#    QMAKE_POST_LINK += /usr/libexec/PlistBuddy -c \"Set :CFBundleShortVersionString $${VERSION}\" $${INFO_PLIST_PATH}
#}



TARGET = $${PRODUCT}
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
