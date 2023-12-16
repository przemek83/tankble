SET(PROJECT_TEST ${PROJECT_NAME}-test )

include_directories(${CMAKE_SOURCE_DIR})

set(${PROJECT_TEST}_SOURCES
    BulletTest.cpp
    MapTest.cpp
    TankTest.cpp
    MapUtilsTest.cpp
    ConfigTest.cpp
    )

add_executable(${PROJECT_TEST} ${${PROJECT_TEST}_SOURCES})
target_link_libraries(${PROJECT_TEST} PRIVATE Catch2::Catch2WithMain
    ${PROJECT_NAME}-lib optimized allegro debug allegro-debug
    optimized allegro_image debug allegro_image-debug
    optimized allegro_font debug allegro_font-debug
    optimized allegro_primitives debug allegro_primitives-debug
)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME}-test)
