cmake_minimum_required(VERSION 3.28)
project(selaura_client LANGUAGES CXX)

add_library(selaura_client SHARED
        dllmain.cpp
        selaura.cpp
        memory/scanner.cpp
        memory/scan_target.cpp
)

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
)