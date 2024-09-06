cmake_minimum_required(VERSION 3.8)

project(tankble
    LANGUAGES CXX 
    VERSION 1.0.0 
    DESCRIPTION "Clone of action game named Battle City/Tank 1990."
    HOMEPAGE_URL "https://github.com/przemek83/tankble")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(CODE_COVERAGE "Collect coverage" OFF)

if(CODE_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 --coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage")
endif()

include(CMakeLists.txt.allegro)
set(ALLEGRO_SOURCE_DIR "${FETCHCONTENT_BASE_DIR}/allegro-src")
set(ALLEGRO_BINARY_DIR "${FETCHCONTENT_BASE_DIR}/allegro-build")

# file(GLOB_RECURSE DLLS "${CMAKE_BINARY_DIR}/*.dll" )
# file(COPY ${DLLS} DESTINATION ${CMAKE_BINARY_DIR})
# file(COPY ${DLLS} DESTINATION "${CMAKE_BINARY_DIR}/test")
file(COPY image DESTINATION ${CMAKE_BINARY_DIR})
file(COPY levels DESTINATION ${CMAKE_BINARY_DIR})

set(${PROJECT_NAME}_SOURCES
        src/Tank.cpp
        src/Tank.h
        src/Menu.cpp
        src/Menu.h
        src/Map.cpp
        src/Map.h
        src/Game.cpp
        src/Game.h
        src/Config.cpp
        src/Config.h
        src/Screen.h
        src/Screen.cpp
        src/Resources.h
        src/Resources.cpp
        src/ResourceType.h
        src/Input.h
        src/Input.cpp
        src/InputAction.h
        src/TankType.h
        src/Bullet.cpp
        src/Bullet.h
        src/Drawable.cpp
        src/Drawable.h
        src/Point.h
        src/PointUtils.cpp
        src/PointUtils.h
        src/Direction.h
        src/TankStats.h
        src/Status.h
        src/Status.cpp
        src/MapUtils.h
        src/MapUtils.cpp
        src/Level.h
        src/map/Water.cpp
        src/map/Water.h
        src/map/Steel.cpp
        src/map/Steel.h
        src/map/PowerUp.cpp
        src/map/PowerUp.h
        src/map/ShieldUp.cpp
        src/map/ShieldUp.h
        src/map/SpeedUp.cpp
        src/map/SpeedUp.h
        src/map/LifeUp.cpp
        src/map/LifeUp.h
        src/map/TierUp.cpp
        src/map/TierUp.h
        src/map/Plant.cpp
        src/map/Plant.h
        src/map/Tile.cpp
        src/map/Tile.h
        src/map/Ice.cpp
        src/map/Ice.h
        src/map/Plain.cpp
        src/map/Plain.h
        src/map/Brick.cpp
        src/map/Brick.h
        src/map/Base.cpp
        src/map/Base.h
    )

add_library (${PROJECT_NAME}-lib STATIC ${${PROJECT_NAME}_SOURCES})
target_link_libraries(${PROJECT_NAME}-lib allegro allegro_image allegro_font allegro_primitives)
target_include_directories(${PROJECT_NAME}-lib PUBLIC 
${ALLEGRO_SOURCE_DIR}/include 
${ALLEGRO_SOURCE_DIR}/addons/font 
${ALLEGRO_SOURCE_DIR}/addons/image
${ALLEGRO_SOURCE_DIR}/addons/primitives
${ALLEGRO_BINARY_DIR}/include
)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)

enable_testing()
Include(Tests.cmake)
add_subdirectory(test)
