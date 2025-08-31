cmake_minimum_required(VERSION 3.28)
project(mcsdk LANGUAGES CXX)

add_library(mcsdk mcsdk.cpp)

target_include_directories(mcsdk PRIVATE
        fmt
        EnTT
        gsl
        glm
        glaze
)

target_link_libraries(mcsdk PRIVATE
        EnTT::EnTT
        Microsoft.GSL::GSL
        glm
        glaze::glaze
)