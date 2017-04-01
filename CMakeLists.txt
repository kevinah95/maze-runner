cmake_minimum_required(VERSION 3.5)
project(maze-runner)

set(CMAKE_C_STANDARD 99)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SOURCE_FILES main.c)

add_executable(maze-runner ${SOURCE_FILES})
target_link_libraries(maze-runner Threads::Threads)