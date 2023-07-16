# macos升级到15之后需要手动指定sdk，这里使用win的时候需要注解一下，剩下的不用动，后面用if来检测环境
# set(CMAKE_OSX_SYSROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk")
cmake_minimum_required(VERSION 3.15)
project(MyCProject C)
set(CMAKE_C_STANDARD 11)
message(${PROJECT_SOURCE_DIR})



# 递归搜索匹配源码目录和其子目录下的.c文件
#FILE(GLOB DIR ${PROJECT_SOURCE_DIR}/*.c})
#FILE(GLOB_RECURSE DIR  ${PROJECT_SOURCE_DIR}/*.c)
FILE(GLOB_RECURSE DIR  ${PROJECT_SOURCE_DIR}/algorithm/*.c)
include_directories("algorithm/include/")
add_executable(MyCProject ${DIR})
#add_executable(MyCProject algorithm/data_struct/arraylist/arraylist.c algorithm)


#        #设定所有源码列表 方式一
#        #  假如你有好多个源码文件放在在CAMKE_SOURCE_DIR这个目录下，其实这个目标就是工程目录，即CMakeLists.txt所在目录
#        #aux_source_directory(${CAMKE_SOURCE_DIR} DIR)  #将${CAMKE_SOURCE_DIR}目录下，也就是最顶级目录下所有的.cpp文件放入DIR变量中，后面add_executable就可很简化啦
#        #aux_source_directory(../src  DIR) 诶，我还有一些不小心放在其他地点的源码文件，我也要放在DIR变量中
#        #设定所有源码列表 方式二
#        FILE（GLOB DIR ${PROJECT_SOURCE_DIR}/*.cpp}） #匹配源码目录所有.cpp文件
#        FILE（GLOB_RECURSE DIR  ${PROJECT_SOURCE_DIR}/*.cpp） # 递归搜索匹配源码目录和其子目录下的.cpp文件
#        #add_executable(hello_world ${DIR})  设置源码列表后，获得可执行文件这一步就很方便了，不用巴拉巴拉写一长串源码文件； 这里只是说明下，不是这句真写在这个地方
#
#        #设定头文件路径
#        include_directories(../include/)
#        #inclde_directories("路径1"  “路径2”)
#
#
#        #设定链接库的路径（一般使用第三方非系统目录下的库）  比如opencv??
#        link_directories(../build/)
#        link_directories("路径1"  “路径2)
#
#        #添加子目录，作用相当于进去子目录里面，展开子目录的CMakeLists.txt
#        #同时执行，子目录中的CMakeLists.txt一般是编译成一个库，作为一个模块
#        #在父目录中可以直接引用子目录生成的库
#        #add_subdirectory(math)
#
#        #生成动静态库
#        #add_library(动静态链接库名称  SHARED/STATIC(可选，默认STATIC)    源码列表)
#        add_libarary(model STATIC ${DIR}) # 生成libmodel.a
#        add_libarary(model SHARED ${DIR}) #生成libmodel.so
#
#        #生成可执行文件
#        add_executable(modle ${SOURCE_FILES})
#        target_link_libaries(${PROJECT_NAME} pthred glog) #就是g++ 编译选项中-l后的内容，不要有多余空格
#
#        ADD_CUSTOM_COMMAND(#执行shell命令
#        TARGET  modle
#        POST_BUILD # 在目标文件model build之后，执行下面的拷贝命令，还可以选择PRE_BUILD命令将会在其他依赖项执行前执行  PRE_LINK命令将会在其他依赖项执行完后执行   POST_BUILD命令将会在目标构建完执行
#        COMMAND cp  ./model ../
#        )


# 三方库链接方式
#cmake_minimum_required(VERSION 3.7)
##项目名字
#project(deadcode)
##设置编译版本
#set (CMAKE_CXX_STANDARD 14)
## 1.自己项目的头文件和cpp
#set(SOURCE_FILES
#        src/trace/cpps/main.cpp
#        src/trace/headers/directory_iterator.h src/trace/cpps/directory_iterator.cpp
#        src/trace/headers/file_reader.h src/trace/cpps/file_reader.cpp
#        src/trace/headers/reader.h src/trace/cpps/reader.cpp
#        src/trace/headers/record_file_reader.h src/trace/headers/record_file_reader.cpp
#        src/trace/headers/memref.h src/trace/headers/memtrace_stream.h src/trace/headers/utils.h
#        src/trace/headers/trace_entry.h src/trace/cpps/trace_entry.cpp
#        src/trace/headers/analyzer.h src/trace/cpps/analyzer.cpp
#        src/trace/headers/analyzer_runner.h src/trace/cpps/analyzer_runner.cpp
#        src/trace/headers/analysis_tool.h
#        src/trace/headers/dead_code_analysis.h src/trace/cpps/dead_code_analysis.cpp)
#​
## 2.下载的外部库
### 外部库的头文件
#set(ZLIB_INCLUDE C:/Users/29185/Desktop/2023/GEARS/dead_code/src/xed/include)
### 外部库的lib文件（静态编译）
#set(ZLIB_LIBRARIES C:/Users/29185/Desktop/2023/GEARS/dead_code/src/xed/lib)
#​
## 3.加载线程库
#find_package (Threads)
#​
## 设置项目输出
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
## 链接外部库
#include_directories(${ZLIB_INCLUDE})
#link_directories(${ZLIB_LIBRARIES})
#​
## 设置编译文件
#add_executable(deadcode ${SOURCE_FILES})
##将第三方库链接在一起
#target_link_libraries (${PROJECT_NAME} libxed.a Threads::Threads)