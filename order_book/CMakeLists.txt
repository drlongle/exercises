cmake_minimum_required(VERSION 3.16)
project(order_book)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(order_book order_book.cpp)
add_executable(order_book_test order_book_test.cpp)
target_link_libraries(order_book_test order_book gtest_main)

include(GoogleTest)
gtest_discover_tests(order_book_test)
