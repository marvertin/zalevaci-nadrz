cmake_minimum_required(VERSION 3.22)

set(CMAKE_WARN_DEPRECATED FALSE)
set(CMAKE_POLICY_DEFAULT_CMP0111 OLD)
if(POLICY CMP0111)
    cmake_policy(SET CMP0111 OLD)
endif()

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(voda-septik)
