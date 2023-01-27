SET(PROJECT_TEST ${PROJECT_NAME}-test )

set(${PROJECT_TEST}_SOURCES
    Test.cpp
    )

add_executable(${PROJECT_TEST} ${${PROJECT_TEST}_SOURCES})
target_link_libraries(${PROJECT_TEST} PRIVATE Catch2::Catch2WithMain)
add_test(NAME ${PROJECT_TEST} COMMAND ${PROJECT_TEST})

