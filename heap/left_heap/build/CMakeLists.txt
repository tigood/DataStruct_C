cmake_minimum_required(VERSION 3.0)

project(left_heap_text)

include_directories(${PROJECT_BINARY_DIR}/../include)

aux_source_directory(${PROJECT_BINARY_DIR}/../src SRC)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

add_executable(left_heap_run ${SRC})