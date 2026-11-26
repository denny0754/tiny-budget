find_package(GTest CONFIG REQUIRED)

add_executable(tb-tests
    "db/DatabaseSessionTest.cpp"
    "test_main.cpp"
)

set_target_properties(tb-tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(tb-tests
    PRIVATE
    tb-core-lib
    GTest::gtest
    GTest::gmock
)

include(GoogleTest)
gtest_discover_tests(tb-tests)