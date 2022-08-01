cmake_minimum_required(VERSION 3.22)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})

project(csapp C)

set(CMAKE_C_STANDARD 11)

include_directories(.)


# 动态添加当前c文件至可运行列表中
file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/chapter*/*/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/chapter*/*/*/*.c")
foreach(file ${files})
    get_filename_component(name ${file} NAME)
    add_executable(${name} ${file})
#    message(STATUS "file = ${file}")
endforeach()