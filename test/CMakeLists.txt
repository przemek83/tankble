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
target_link_libraries(${PROJECT_TEST} PRIVATE Catch2::Catch2WithMain ${PROJECT_NAME}-lib)

IF (WIN32)
    file(GLOB_RECURSE DLLS "${CMAKE_BINARY_DIR}/*.dll" )
    message("--------- LIBS: ${DLLS}")
    file(COPY ${DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${DLLS} DESTINATION "${CMAKE_BINARY_DIR}/test/${CMAKE_BUILD_TYPE}")
    message("--------- COMMAND")
    execute_process(COMMAND dir "${CMAKE_BINARY_DIR}/test/${CMAKE_BUILD_TYPE}")

    add_custom_command(TARGET ${PROJECT_TEST} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${FETCHCONTENT_BASE_DIR}/allegro-build/lib/" "$<TARGET_FILE_DIR:${PROJECT_TEST}>/${CMAKE_BUILD_TYPE}")
    add_custom_command(TARGET ${PROJECT_TEST} POST_BUILD
                   COMMAND dir "${FETCHCONTENT_BASE_DIR}/allegro-build/lib/")
    add_custom_command(TARGET ${PROJECT_TEST} POST_BUILD
                   COMMAND dir "${CMAKE_BINARY_DIR}/test/${CMAKE_BUILD_TYPE}")
ENDIF()

include(CTest)
include(Catch)
set(CMAKE_CATCH_DISCOVER_TESTS_DISCOVERY_MODE PRE_TEST)
catch_discover_tests(${PROJECT_TEST})
