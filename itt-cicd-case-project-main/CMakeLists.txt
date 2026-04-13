cmake_minimum_required(VERSION 3.16)
project(QualityApiIndustrial)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

include_directories(include external)

add_library(quality_core src/quality_service.cpp)
target_include_directories(quality_core PUBLIC include external)

add_executable(quality_api src/main.cpp)
target_link_libraries(quality_api PRIVATE quality_core)
if (WIN32)
  target_compile_definitions(quality_api PRIVATE _WIN32_WINNT=0x0A00)
  target_link_libraries(quality_api PRIVATE ws2_32)
endif()

enable_testing()
add_executable(quality_service_tests tests/quality_service_test.cpp)
target_link_libraries(quality_service_tests PRIVATE quality_core GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(quality_service_tests)
