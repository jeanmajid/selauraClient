cmake_minimum_required(VERSION 3.28)
project(thunker LANGUAGES CXX)

file(GLOB_RECURSE THUNKER_SOURCES src/*.cpp)
add_library(thunker STATIC ${THUNKER_SOURCES})

target_compile_definitions(thunker PRIVATE THUNKER_BUILD_DLL)

target_include_directories(thunker PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)