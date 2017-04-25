cmake_minimum_required(VERSION 3.5)
project(maze-runner)

set(CMAKE_C_STANDARD 99)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

##file(GLOB SRCS "*.h" "*.c")##For all files

set(extra_flags -Werror -Wall -Wextra -Wno-deprecated -Wimplicit-function-declaration)
set(CMAKE_CXX_FLGAS "${CMAKE_CXX_FLAGS} ${extra_flags}")
set(SOURCES     main.c
                utils.c
                thread.c
                operation.c)
set (HEADERS    utils.h
                thread.h
                operation.h
                vector.h)
##include_directories(BEFORE ${HEADERS})
add_executable(maze-runner ${SOURCES} ${HEADERS})
target_link_libraries(maze-runner Threads::Threads)