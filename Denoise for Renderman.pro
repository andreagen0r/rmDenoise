QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 'Denoise For Renderman'
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        mainwindow.cpp \
        pxrdenoise.cpp \
    preferencesUI.cpp \
    settings.cpp \
    utils.cpp

HEADERS  += mainwindow.h \
            pxrdenoise.h \
            preferencesUI.h \
    settings.h \
    utils.h

FORMS    += mainwindow.ui \
            preferencesUI.ui

RESOURCES += \
            resource.qrc

# set app icons
RC_ICONS = app.ico
macx:ICON = $${PWD}/app.icns
