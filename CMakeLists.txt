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
        src/LMProfile.cpp
        src/LMConfigProfile.cpp
        src/LMWizard.cpp
        src/LMMainUi.cpp
        src/LMGlobal.cpp
        main.cpp
        )


set(PROJECT_HEADERS
        include/LMProfile.h
        include/LMConfigProfile.h
        include/LMWizard.h
        include/LMMainUi.h
        include/LMGlobal.h
        )

set(PROJECT_UI
        include/ui_/LMMainUi.ui
        include/ui_/LMProfile.ui
        include/ui_/LMConfigProfile.ui
        include/ui_/LMWizard.ui
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
