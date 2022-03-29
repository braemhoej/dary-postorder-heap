cmake_minimum_required(VERSION 3.21)
project(PostOrderHeap VERSION 1.0)
include(FetchContent)
set(CMAKE_CXX_STANDARD 20)

########################
##   Google Testing  ###
########################
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
FetchContent_MakeAvailable(googletest)

########################
##   Unit Testing    ###
########################

add_library(PostOrderHeap src/post_order_heap.h src/post_order_heap.cpp test/test_post_order_heap.cpp)
add_executable( testPostOrderHeap test/test_post_order_heap.cpp)
# Link test executable against gtest & gtest_main

target_link_libraries(testPostOrderHeap gtest gtest_main)
add_test( runUnitTests testPostOrderHeap)
