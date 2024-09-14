set(PROJECT_TEST ${PROJECT_NAME}-test)

include_directories(${CMAKE_SOURCE_DIR})

set(${PROJECT_TEST}_SOURCES
    BulletTest.cpp
    MapTest.cpp
    TankTest.cpp
    MapUtilsTest.cpp
    ConfigTest.cpp
    MenuItemTest.cpp
)

add_executable(${PROJECT_TEST} ${${PROJECT_TEST}_SOURCES})
target_link_libraries(${PROJECT_TEST} PRIVATE Catch2::Catch2WithMain ${PROJECT_NAME}-lib)

if (WIN32)
    add_custom_command(TARGET ${PROJECT_TEST} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "$<TARGET_FILE_DIR:allegro>" "$<TARGET_FILE_DIR:${PROJECT_TEST}>")
endif()

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_TEST})
