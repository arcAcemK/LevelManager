CMAKE_MINIMUM_REQUIRED(VERSION 3.16.3)

project(LevelManager LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(PROJECT_CPP
        src/BoxContainer.cpp
        src/ConfigurePlayer.cpp
        src/DialogAdmin.cpp
        src/UserInterface.cpp
        src/LMGlobal.cpp
        main.cpp
        )


set(PROJECT_HEADERS
        include/BoxContainer.h
        include/ConfigurePlayer.h
        include/DialogAdmin.h
        include/UserInterface.h
        include/LMGlobal.h
        )

set(PROJECT_UI
        include/ui_/UserInterface.ui
        include/ui_/BoxContainer.ui
        include/ui_/ConfigurePlayer.ui
        include/ui_/DialogAdmin.ui
        )

set(PROJECT_RESOURCES
        assets/resources.qrc)

set(TS_FILES
        assets/lang/LevelManager_fr_FR.ts
        assets/lang/LevelManager_ar.ts
        assets/lang/LevelManager_es.ts
        )

set(PROJECT_SOURCES
        ${PROJECT_CPP}
        ${PROJECT_HEADERS}
        ${PROJECT_UI}
        ${PROJECT_RESOURCES}
        ${TS_FILES}
        )

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(LevelManager ${PROJECT_SOURCES})

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else ()
    add_executable(LevelManager ${PROJECT_SOURCES})
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif ()

target_link_libraries(LevelManager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
