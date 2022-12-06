QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    1_stage_preparing.cpp \
    2_stage_game.cpp \
    leader.cpp \
    main.cpp \
    mainwindow.cpp \
    patterns.cpp \
    sfmltictactoe.cpp \
    sfmlwidget.cpp

HEADERS += \
    leader.h \
    mainwindow.h \
    patterns.h \
    sfmltictactoe.h \
    sfmlwidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += nlohmann\include
INCLUDEPATH += C:\Users\User\WORKSPACE\SFML_for_Qt\SFML\include
DEPENDPATH += C:\Users\User\WORKSPACE\SFML_for_Qt\SFML\include

LIBS += -LC:\Users\User\WORKSPACE\SFML_for_Qt\LIBS\

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

RC_ICONS = $$PWD/tic-tac-toe-ICON.ico
