QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    base_card.cpp \
    cardwidget.cpp \
    changeinformation.cpp \
    chooseclient.cpp \
    chooseserver.cpp \
    deck.cpp \
    forgotpassword.cpp \
    king_card.cpp \
    login.cpp \
    loginafterregister.cpp \
    main.cpp \
    mainwindow.cpp \
    queen_card.cpp \
    register.cpp \
    server.cpp \
    serverorclient.cpp \
    thief_card.cpp \
    user.cpp

HEADERS += \
    base_card.h \
    cardwidget.h \
    changeinformation.h \
    chooseclient.h \
    chooseserver.h \
    deck.h \
    forgotpassword.h \
    king_card.h \
    login.h \
    loginafterregister.h \
    mainwindow.h \
    queen_card.h \
    register.h \
    server.h \
    serverorclient.h \
    thief_card.h \
    user.h

FORMS += \
    changeinformation.ui \
    chooseclient.ui \
    chooseserver.ui \
    forgotpassword.ui \
    login.ui \
    loginafterregister.ui \
    mainwindow.ui \
    register.ui \
    server.ui \
    serverorclient.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
