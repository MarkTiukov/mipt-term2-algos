cmake_minimum_required(VERSION 3.16)
project(Contest4)

set(CMAKE_CXX_STANDARD 17)

add_executable(Contest4 main.cpp)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Task1.cpp)
    add_executable(Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Task1.cpp)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Task2.cpp)
    add_executable(Task2 ${CMAKE_CURRENT_SOURCE_DIR}/Task2.cpp)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Task3.cpp)
    add_executable(Task3 ${CMAKE_CURRENT_SOURCE_DIR}/Task3.cpp)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Task4.cpp)
    add_executable(Task4 ${CMAKE_CURRENT_SOURCE_DIR}/Task4.cpp)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Task5.cpp)
    add_executable(Task5 ${CMAKE_CURRENT_SOURCE_DIR}/Task5.cpp)
endif()