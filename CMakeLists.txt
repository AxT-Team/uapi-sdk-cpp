cmake_minimum_required(VERSION 3.14)
project(uapi-sdk-cpp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_library(uapi INTERFACE)
target_include_directories(uapi INTERFACE include)
