# macos升级到15之后需要手动指定sdk，这里使用win的时候需要注解一下，剩下的不用动，后面用if来检测环境
# set(CMAKE_OSX_SYSROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk")
cmake_minimum_required(VERSION 3.15)
project(MyCProject C)

set(CMAKE_C_STANDARD 11)

add_executable(MyCProject algorithm/stack_and_queue/my_stack/min_stack.c algorithm/data_struct/arraylist/arraylist.c algorithm/data_struct/stack/stack.c )
#add_executable(MyCProject algorithm/data_struct/arraylist/arraylist.c algorithm)