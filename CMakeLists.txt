cmake_minimum_required(VERSION 3.8)

project(tankble
    LANGUAGES CXX 
    VERSION 1.0.0 
    DESCRIPTION "Clone of action game named Battle City/Tank 1990."
    HOMEPAGE_URL "https://github.com/przemek83/tankble")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(THIRD_PARTY_LIBS allegro)
foreach(file_i ${THIRD_PARTY_LIBS})
    configure_file(CMakeLists.txt.${file_i} ${file_i}/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G ${CMAKE_GENERATOR} .
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/${file_i})
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/${file_i} )

    include_directories(${CMAKE_BINARY_DIR}/${file_i}/install/include)
    link_directories(${CMAKE_BINARY_DIR}/${file_i}/install/lib)
endforeach(file_i)

file(GLOB_RECURSE DLLS "${CMAKE_BINARY_DIR}/*.dll" )
file(COPY ${DLLS} DESTINATION ${CMAKE_BINARY_DIR})

file(COPY image DESTINATION ${CMAKE_BINARY_DIR})
file(COPY missions DESTINATION ${CMAKE_BINARY_DIR})

set(${PROJECT_NAME}_SOURCES
        Tank.cpp
        Tank.h
        Menu.cpp
        Menu.h
        Map.cpp
        Map.h
        Game.cpp
        Game.h
        Config.cpp
        Config.h
        Screen.h
        Screen.cpp
        Resources.h
        Resources.cpp
        ResourceType.h
        Input.h
        Input.cpp
        InputAction.h
        TankType.h
        Bullet.cpp
        Bullet.h
        Drawable.cpp
        Drawable.h
        Point.h
        PointUtils.cpp
        PointUtils.h
        Direction.h
        TankStats.h
        Status.h
        Status.cpp
        MapUtils.h
        MapUtils.cpp
        map/Water.cpp
        map/Water.h
        map/Steel.cpp
        map/Steel.h
        map/PowerUp.cpp
        map/PowerUp.h
        map/ShieldUp.cpp
        map/ShieldUp.h
        map/SpeedUp.cpp
        map/SpeedUp.h
        map/LifeUp.cpp
        map/LifeUp.h
        map/TierUp.cpp
        map/TierUp.h
        map/Plant.cpp
        map/Plant.h
        map/Tile.cpp
        map/Tile.h
        map/Ice.cpp
        map/Ice.h
        map/Plain.cpp
        map/Plain.h
        map/Brick.cpp
        map/Brick.h
        map/Base.cpp
        map/Base.h
    )

add_library (${PROJECT_NAME}-lib STATIC ${${PROJECT_NAME}_SOURCES})

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} stdc++fs ${PROJECT_NAME}-lib
    optimized allegro debug allegro-debug
    optimized allegro_image debug allegro_image-debug
    optimized allegro_font debug allegro_font-debug
    optimized allegro_primitives debug allegro_primitives-debug
)

Include(Tests.cmake)
enable_testing()
add_subdirectory(test)
