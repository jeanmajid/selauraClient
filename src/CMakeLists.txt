cmake_minimum_required(VERSION 3.28)
project(selaura_client LANGUAGES CXX)

add_library(selaura_client SHARED
        main.cpp
        runtime.cpp
        hooks/hooks.cpp
)

target_compile_definitions(selaura_client PRIVATE SELAURA_CLIENT_EXPORTS)

target_include_directories(selaura_client PRIVATE
        fmt
        EnTT
        spdlog
        libhat
        gsl
        glm
        safetyhook
        glaze
        magic_enum

        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(selaura_client PRIVATE
        EnTT::EnTT
        spdlog
        libhat
        Microsoft.GSL::GSL
        glm
        safetyhook::safetyhook
        glaze::glaze
        magic_enum::magic_enum
        runtimeobject.lib
        version.lib
)