cmake_minimum_required(VERSION 3.5)
project(maze-runner)

set(CMAKE_C_STANDARD 99)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(HEADER_FILES utils.h thread.h)
set(LIB_FILES utils.c thread.c)
file(GLOB all_SRC "*.h" "*.c")##For all files

set(SOURCE_FILES main.c ${all_SRC})
add_executable(maze-runner ${SOURCE_FILES})
target_link_libraries(maze-runner Threads::Threads)