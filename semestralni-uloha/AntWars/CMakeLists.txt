cmake_minimum_required(VERSION 3.7)
project(AntWars)

set(CMAKE_CXX_STANDARD 11)

find_package( Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIRS} )

set(SOURCE_FILES
        main.cpp gameWrapper.h menu.cpp menu.h game.cpp game.h inOut.cpp inOut.h map.cpp map.h
        mapElement.h antHill.cpp antHill.h ant.cpp ant.h empty.h wall.h path.cpp path.h
        abstractPlayer.h humanPlayer.cpp humanPlayer.h botPlayer.cpp botPlayer.h command.cpp command.h common.h
        exceptions.h abstractPlayer.cpp gameWrapper.cpp)

add_executable(AntWars ${SOURCE_FILES})

target_link_libraries( AntWars ${CURSES_LIBRARIES} )