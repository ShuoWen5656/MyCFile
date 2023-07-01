cmake_minimum_required(VERSION 3.15)
project(MyCProject C)

set(CMAKE_C_STANDARD 11)

add_executable(MyCProject data_struct/stack/stack.c)
#add_executable(MyCProject data_struct/stack/stack.c data_struct/arraylist/arraylist.c)