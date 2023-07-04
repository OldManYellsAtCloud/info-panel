cmake_minimum_required(VERSION 3.5)

project(info-panel VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(sdbus-c++)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        dbusListener.cpp
        dbusListener.h
        brightness.h
        brightness.cpp
        config.h
        config.cpp
        logger.h
        logger.cpp
)

qt_standard_project_setup()

qt_add_executable(info-panel
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)


target_link_libraries(info-panel PRIVATE Qt6::Widgets)

install(TARGETS info-panel
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

qt_finalize_executable(info-panel)


target_link_libraries(info-panel PRIVATE SDBusCpp::sdbus-c++)
