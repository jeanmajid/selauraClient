#pragma once
#include <bit>
#include <hooks/memory.hpp>

class ScreenContext;
class Tessellator;
namespace mce {
    class MaterialPtr;
};

namespace MeshHelpers {
    inline void renderMeshImmediately(ScreenContext& screenContext, Tessellator& tessellator, const mce::MaterialPtr& material, char* a4[0x58] = {}) {
        using fn_t = decltype(&MeshHelpers::renderMeshImmediately);
        static fn_t fn = std::bit_cast<fn_t>(selaura::find_signature<"E8 ? ? ? ? C6 46 ? ? F3 41 0F 10 5F">());
        return (*fn)(screenContext, tessellator, material, a4);
    }
};