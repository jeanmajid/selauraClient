#pragma once
#include <hooks/memory.hpp>

namespace mce {
    enum class PrimitiveMode : int {
        None = 0,
        QuadList = 1,
        TriangleList = 2,
        TriangleStrip = 3,
        LineList = 4,
        LineStrip = 5,
    };

    enum class VertexField : int {
        UV_0 = 1
    };
};

class Tessellator {
public:
    bool mIsFormatFixed;
public:
    void begin(mce::PrimitiveMode mode, int maxVertices) {
        using fn_t = decltype(&Tessellator::begin);
        static fn_t fn = std::bit_cast<fn_t>(Selaura::FindSignature<"48 89 74 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 80 B9 ? ? ? ? ? 45 0F B6 D9">());
        return (this->*fn)(mode, maxVertices);
    }

    void vertex(float x, float y, float z) {
        using fn_t = decltype(&Tessellator::vertex);
        static fn_t fn = std::bit_cast<fn_t>(Selaura::FindSignature<"4C 8B DC 55 57 49 8D 6B ? 48 81 EC ? ? ? ? 45 0F 29 4B">());
        return (this->*fn)(x, y, z);
    }

    void vertexUV(float x, float y, float z, float u, float v) {
        u = std::clamp(u, 0.f, 1.f);
        v = std::clamp(v, 0.f, 1.f);

        if (!*(bool*)(this + 340))
            *(bool*)(this + 340) = true;
        *(float*)(this + 332) = u;
        *(float*)(this + 336) = v;
        if (!this->mIsFormatFixed)
            *(bool*)(this + 284) = true;

        this->vertex(x, y, z);
    }

    void color(float r, float g, float b, float a) {
        using fn_t = decltype(&Tessellator::color);
        static fn_t fn = std::bit_cast<fn_t>(Selaura::FindSignature<"80 B9 ? ? ? ? ? 4C 8B C1 75">());
        return (this->*fn)(r, g, b, a);
    }
};