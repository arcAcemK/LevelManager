TARGET = LevelManager

QT += core gui widgets

win32
{
    QMAKE_LFLAGS += -static-libgcc
}

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    src/BoxContainer.cpp \
    src/ConfigurePlayer.cpp \
    src/DialogAdmin.cpp \
    src/UserInterface.cpp

HEADERS += \
    include/BoxContainer.h \
    include/ConfigurePlayer.h \
    include/DialogAdmin.h \
    include/UserInterface.h \

FORMS += \
    include/ui_/BoxContainer.ui \
    include/ui_/ConfigurePlayer.ui \
    include/ui_/DialogAdmin.ui \
    include/ui_/UserInterface.ui \

TRANSLATIONS += \
    assets/lang/LevelManager_fr_FR.ts\
    assets/lang/LevelManager_ar.ts\
    assets/lang/LevelManager_es.ts
    
RESOURCES += \
    assets/resources.qrc
