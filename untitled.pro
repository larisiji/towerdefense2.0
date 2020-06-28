QT       += core gui
QT       += core
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG+=resources_big
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullet.cpp \
    bullet2.cpp \
    bullet3.cpp \
    choosescene.cpp \
    enemy.cpp \
    enemy2.cpp \
    enemy3.cpp \
    main.cpp \
    mainwindow.cpp \
    mypushbutton.cpp \
    scene1.cpp \
    scene2.cpp \
    tower.cpp \
    tower2.cpp \
    tower3.cpp \
    tower4.cpp \
    towerposition.cpp \
    waypoint.cpp

HEADERS += \
    bullet2.h \
    bullet3.h \
    choosescene.h \
    collision.h \
    enemy.h \
    enemy2.h \
    enemy3.h \
    mainwindow.h \
    mypushbutton.h \
    scene1.h \
    scene2.h \
    testing.h \
    tower.h \
    tower2.h \
    tower3.h \
    tower4.h \
    towerposition.h \
    waypoint.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc


