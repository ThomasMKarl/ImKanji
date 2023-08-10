find_package(Catch2 3 REQUIRED)
add_executable(imkanji_tests main_test.cpp)
target_link_libraries(imkanji_tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(imkanji_tests)
