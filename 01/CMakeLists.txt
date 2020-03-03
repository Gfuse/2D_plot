project( p_demo_01 )
cmake_minimum_required( VERSION 3.4 )

set( CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} $ENV{QT5_DIR} )
set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC ON )

find_package(Qt5Widgets 5.13 REQUIRED) #add qt5

qt5_wrap_ui(UI_HEADERS ui/mainwindow.ui)
include_directories(include
                    qwt/src) 
add_executable( ${PROJECT_NAME}
                src/main.cpp
                src/mainwindow.cpp
                include/mainwindow.h
                include/signal.h
                ${UI_HEADERS})

FIND_LIBRARY(QWT_LIBRARY NAMES qwt qwt5 qwt-qt4 qwt5-qt4 PATHS
             qwt/lib)

target_link_libraries( ${PROJECT_NAME}
                       Qt5::Widgets
                       ${QWT_LIBRARY})

