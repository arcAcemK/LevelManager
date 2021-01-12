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
    src/LMProfile.cpp \
    src/LMConfigProfile.cpp \
    src/LMWizzard.cpp \
    src/LMMainUi.cpp

HEADERS += \
    include/LMProfile.h \
    include/LMConfigProfile.h \
    include/LMWizzard.h \
    include/LMMainUi.h \

FORMS += \
    include/ui_/LMProfile.ui \
    include/ui_/LMConfigProfile.ui \
    include/ui_/LMWizzard.ui \
    include/ui_/LMMainUi.ui \

TRANSLATIONS += \
    assets/lang/LevelManager_fr_FR.ts\
    assets/lang/LevelManager_ar.ts\
    assets/lang/LevelManager_es.ts
    
RESOURCES += \
    assets/resources.qrc
