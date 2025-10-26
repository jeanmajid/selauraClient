cmake_minimum_required(VERSION 3.28)
project(selaura_proxy LANGUAGES CXX)

add_library(selaura_proxy SHARED
        main_win_uwp.cpp
)

target_include_directories(selaura_proxy PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(selaura_proxy PRIVATE
        runtimeobject.lib
)