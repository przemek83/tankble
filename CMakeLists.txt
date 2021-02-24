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
        vehicle.cpp
        vehicle.h
        player.cpp
        player.h
        menu.cpp
        menu.h
        map.cpp
        map.h
        game.cpp
        game.h
        config.h
        map/water.cpp
        map/water.h
        map/steel.cpp
        map/steel.h
        map/powerup.cpp
        map/powerup.h
        map/plants.cpp
        map/plants.h
        map/map_element.cpp
        map/map_element.h
        map/ice.cpp
        map/ice.h
        map/dirt.cpp
        map/dirt.h
        map/bullet.cpp
        map/bullet.h
        map/bricks.cpp
        map/bricks.h
        map/plain.cpp
        map/plain.h
    )

add_executable(${CMAKE_PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

target_link_libraries(${PROJECT_NAME} allegro-debug-5.2 allegro_image-debug-5.2 allegro_font-debug-5.2)

enable_testing()
add_subdirectory(test)
