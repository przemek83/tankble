SET(PROJECT_TEST ${PROJECT_NAME}-test )

include_directories(${CMAKE_SOURCE_DIR})

set(${PROJECT_TEST}_SOURCES
    BulletTest.cpp
    MapTest.cpp
    TankTest.cpp
    )

add_executable(${PROJECT_TEST} ${${PROJECT_TEST}_SOURCES})
target_link_libraries(${PROJECT_TEST} PRIVATE Catch2::Catch2WithMain
    ${PROJECT_NAME}-lib optimized allegro-5.2 debug allegro-debug-5.2
    optimized allegro_image-5.2 debug allegro_image-debug-5.2
    optimized allegro_font-5.2 debug allegro_font-debug-5.2
    optimized allegro_primitives-5.2 debug allegro_primitives-debug-5.2
)

add_test(NAME ${PROJECT_TEST} COMMAND ${PROJECT_TEST})

