cmake_minimum_required( VERSION 2.6 )
set(CMAKE_C_COMPILER "/usr/bin/arm-linux-gnueabi-gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/arm-linux-gnueabi-g++")

project("Arm32Assembly")

set(CMAKE_C_FLAGS "-Wall -O0 -ggdb")
set(CMAKE_C_FLAGS_DEBUG "-Wall -O0 -ggdb")
set(CMAKE_C_FLAGS_RELEASE "-Wall -O0 -ggdb")
set(CMAKE_CXX_FLAGS "-Wall -O0 -ggdb")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -O0 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O0 -ggdb")

add_executable(addressing addressing.c)
add_executable(loadStrore loadStrore.c)
add_executable(loadStrore2 loadStrore2.c)
add_executable(batch batch.c)
add_executable(jump jump.c)
add_executable(dataProcess dataProcess.c)