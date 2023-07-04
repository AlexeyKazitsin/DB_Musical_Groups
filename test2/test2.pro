QT       += core gui
QT += core gui sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    albums.cpp \
    groups.cpp \
    labelinfo.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    navigation.cpp \
    places.cpp \
    songs.cpp \
    tours.cpp

HEADERS += \
    albums.h \
    groups.h \
    labelinfo.h \
    login.h \
    mainwindow.h \
    navigation.h \
    places.h \
    songs.h \
    tours.h

FORMS += \
    albums.ui \
    groups.ui \
    labelinfo.ui \
    login.ui \
    mainwindow.ui \
    navigation.ui \
    places.ui \
    songs.ui \
    tours.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
