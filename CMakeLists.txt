cmake_minimum_required(VERSION 3.10.0)
project(parallelkalman VERSION 0.1.0 LANGUAGES C CXX)
# set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

# add the src directory to the include path
include_directories(src)


file(GLOB MAIN 
    "src/matops.cpp"
    "src/linearMotion.cpp"
    "src/main.cpp"
    "src/*.h"
)

add_executable(parallelkalman ${MAIN})
add_executable(test_matops src/matops.cpp src/test_matops.cpp)


# Include the header files directory
target_include_directories(test_matops PUBLIC ${CMAKE_SOURCE_DIR}/src)
add_test(NAME parallelkalman COMMAND parallelkalman)
add_test(NAME matops COMMAND test_matops)


include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
