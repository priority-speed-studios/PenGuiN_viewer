QMAKE_CXXFLAGS += -std=c++17
QT += core gui widgets

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ./header

SOURCES += \
        src/chessboard.cpp \
        src/about.cpp \
        src/main.cpp \
        src/mainwindow.cpp \
        src/qsfmlcanvas.cpp \
        src/sfmlcanvas.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS +=  -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

FORMS += \
        ui/about.ui \
        ui/mainwindow.ui

HEADERS += \
        header/chessboard.h \
        header/about.h \
        header/mainwindow.h \
        header/qsfmlcanvas.h \
        header/sfmlcanvas.h

DISTFILES += \
        LICENSE \
        README.md

RESOURCES += \
        res.qrc
