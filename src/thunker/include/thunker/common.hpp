#pragma once

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <format>
#include <type_traits>

namespace thunker {
    inline void assert_fail_msg(const char* expr_str, const char* msg, const char* file, int line) {
        std::fprintf(stderr,
            "THUNKER_ASSERT FAILED: %s\nMessage: %s\nAt %s:%d\n",
            expr_str, msg ? msg : "(no message)", file, line);
        std::fflush(stderr);
        assert(false); // triggers debugger breakpoint or abort
    }
}

#define THUNKER_ASSERT(cond, fmt_str, ...)                                      \
    do {                                                                        \
        if constexpr (std::is_constant_evaluated()) {                           \
            static_assert(cond, "Compile-time assertion failed: " #cond);       \
        } else {                                                                \
            if (!(cond)) {                                                      \
                auto _msg = std::format(fmt_str, __VA_ARGS__);                 \
                thunker::assert_fail_msg(#cond, _msg.c_str(), __FILE__, __LINE__); \
            }                                                                   \
        }                                                                       \
    } while (0)


#if defined(_WIN64)
    #define THUNKER_WINDOWS 1
#elif defined(__ANDROID__)
    #define THUNKER_ANDROID 1
#elif defined(__linux__) && !defined(__ANDROID__)
    #define THUNKER_LINUX 1
#else
    #error "thunker only supports Windows x64, Linux x64, Android x64, and Android arm64"
#endif

#if (defined(_M_X64) || defined(__x86_64__))
    #define THUNKER_ARCH_X64 1
#elif defined(__aarch64__)
    #define THUNKER_ARCH_ARM64 1
#else
    #error "thunker only supports x64 and arm64 architectures"
#endif

#if defined(THUNKER_WINDOWS)

    #if defined(THUNKER_STATIC)
        #define THUNKER_DLLEXPORT
        #define THUNKER_DLLIMPORT
    #else
        #if defined(THUNKER_BUILD_DLL)
            #define THUNKER_DLLEXPORT __declspec(dllexport)
            #define THUNKER_DLLIMPORT
        #else
            #define THUNKER_DLLEXPORT
            #define THUNKER_DLLIMPORT __declspec(dllimport)
        #endif
    #endif

#else
    #define THUNKER_DLLEXPORT
    #define THUNKER_DLLIMPORT
#endif

#if defined(THUNKER_STATIC)
    #define THUNKER_API
#elif defined(THUNKER_BUILD_DLL)
    #define THUNKER_API THUNKER_DLLEXPORT
#else
    #define THUNKER_API THUNKER_DLLIMPORT
#endif
