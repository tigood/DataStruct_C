cmake_minimum_required(VERSION 3.0)

project(binary_search_tree_ptr)

include_directories(${PROJECT_BINARY_DIR}/../include)

aux_source_directory(${PROJECT_BINARY_DIR}/../src SRC)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

add_executable(search_tree_ptr_run ${SRC})