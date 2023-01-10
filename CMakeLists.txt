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
    link_directories(${CMAKE_BINARY_DIR}/${file_i}/install/bin)
endforeach(file_i)

# Gtest / Gmock
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src 
    ${CMAKE_BINARY_DIR}/googletest-build)

file(GLOB_RECURSE DLLS "${CMAKE_BINARY_DIR}/*.dll" )
file(COPY ${DLLS} DESTINATION ${CMAKE_BINARY_DIR})

file(COPY image DESTINATION ${CMAKE_BINARY_DIR})
file(COPY missions DESTINATION ${CMAKE_BINARY_DIR})

set(${PROJECT_NAME}_SOURCES
        main.cpp
        Tank.cpp
        Tank.h
        Menu.cpp
        Menu.h
        Map.cpp
        Map.h
        Game.cpp
        Game.h
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
        map/Water.cpp
        map/Water.h
        map/Steel.cpp
        map/Steel.h
        map/Powerup.cpp
        map/Powerup.h
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
        map/Bullet.cpp
        map/Bullet.h
        map/Brick.cpp
        map/Brick.h
        map/Base.cpp
        map/Base.h
    )

add_executable(${CMAKE_PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

target_link_libraries(${PROJECT_NAME} stdc++fs)
target_link_libraries(${PROJECT_NAME} optimized allegro-5.2 debug allegro-debug-5.2)
target_link_libraries(${PROJECT_NAME} optimized allegro_image-5.2 debug allegro_image-debug-5.2)
target_link_libraries(${PROJECT_NAME} optimized allegro_font-5.2 debug allegro_font-debug-5.2)

enable_testing()
add_subdirectory(test)
