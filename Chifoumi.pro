QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chifoumi.cpp \
    chifoumidialog.cpp \
    chifoumivue.cpp \
    database.cpp \
    logindialog.cpp \
    main.cpp

HEADERS += \
    chifoumi.h \
    chifoumidialog.h \
    chifoumivue.h \
    database.h \
    logindialog.h

FORMS += \
    chifoumidialog.ui \
    logindialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    RessourceChifoumi.qrc
