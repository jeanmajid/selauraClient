#pragma once
#include <libhat/scanner.hpp>

namespace Selaura {
    template <hat::fixed_string str>
    void* FindSignature() {
        auto signature = hat::compile_signature<str>();
        return reinterpret_cast<void*>(hat::find_pattern(signature, ".text").get());
    }

    template <typename TRet, typename... TArgs>
    extern TRet CallVirtual(void* thisptr, size_t index, TArgs... argList) {
        using TFunc = TRet(__fastcall*)(void*, TArgs...);
        TFunc* vtable = *reinterpret_cast<TFunc**>(thisptr);
        return vtable[index](thisptr, argList...);
    }

    namespace abi {
        template <typename T>
        constexpr void* mpf_to_fn(T member_fn) noexcept {
            static_assert(std::is_member_function_pointer_v<T>,
                          "mpf_to_fn expects a member function pointer");

#if defined(_MSC_VER)
            union {
                T mfptr;
                void* addr;
            } u{};
            u.mfptr = member_fn;
            return u.addr;
#else
            return reinterpret_cast<void*>(*reinterpret_cast<uintptr_t*>(&member_fn));
#endif
        }

    }
}