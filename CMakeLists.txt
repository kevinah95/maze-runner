cmake_minimum_required(VERSION 3.5)
project(maze-runner)

set(CMAKE_C_STANDARD 99)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(HEADER_FILES utils.h thread.h)
set(LIB_FILES utils.c thread.c)
file(GLOB all_SRC "*.h" "*.c")##For all files

set(extra_flags -Werror -Wall -Wextra -Wno-deprecated)
set(CMAKE_CXX_FLGAS "${CMAKE_CXX_FLAGS} ${extra_flags}")
set(SOURCE_FILES main.c utils.c vector.c thread.c utils.h utilities.h vector.h thread.h ) ##${all_SRC}
add_executable(maze-runner ${SOURCE_FILES})
target_link_libraries(maze-runner Threads::Threads)