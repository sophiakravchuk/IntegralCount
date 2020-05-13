cmake_minimum_required(VERSION 3.10)
project(integral)

set(CMAKE_CXX_STANDARD 14)
if( NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE Release CACHE STRING
            "Choose the type of build, options are: None Debug Release RelWithDebInfo
MinSizeRel."
            FORCE )
endif()
find_package(Threads REQUIRED)
add_executable(integral main.cpp)

target_link_libraries(integral Threads::Threads)