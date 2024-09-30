cmake_minimum_required(VERSION 3.14)
project(SenderProject)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")

include(FetchContent)
FetchContent_Declare(
  googletest
  DOWNLOAD_EXTRACT_TIMESTAMP true
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add directories for header files
include_directories(${PROJECT_SOURCE_DIR}/include)

enable_testing()

file(GLOB SENDER "src/sender.cpp")
file(GLOB SENDER_TESTS "tests/sender_test.cpp")
add_executable(
    sender
  ${SENDER}
)

add_executable(
    sender_test
  ${SENDER}
)

target_link_libraries(
    sender_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(sender_test PROPERTIES TEST_DISCOVERY_TIMEOUT 200)

