find_package(GTest)

add_executable(DataHistoryTest BaseTest.cpp DataHistoryTest.cpp DataTraceTest.cpp DataUtilsTest.cpp)

target_include_directories(DataHistoryTest PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(DataHistoryTest PUBLIC DataHistory GTest::gtest GTest::gtest_main)

gtest_discover_tests(DataHistoryTest)
