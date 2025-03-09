cmake_minimum_required(VERSION 3.10.0)
project(parallelkalman VERSION 0.1.0 LANGUAGES C CXX)

# add the src directory to the include path
file(GLOB MAIN 
    "src/main.cpp"
    "src/*.h"
)

add_executable(parallelkalman ${MAIN})

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
