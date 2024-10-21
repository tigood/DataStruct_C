cmake_minimum_required(VERSION 3.0)

project(generate_avl_tree_text)

include_directories(${PROJECT_BINARY_DIR}/../../../avl_tree_adt/include)

# 只包含 test.c 作为可执行文件的源文件
set(SRC ${PROJECT_BINARY_DIR}/../src/test.c)

# 指定包含二叉搜索树实现的源文件
set(AVL_SRC ${PROJECT_BINARY_DIR}/../../../avl_tree_adt/src/avl_tree.c)

list(APPEND SRC ${AVL_SRC})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

add_executable(generate_test ${SRC})
