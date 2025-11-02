#pragma once

namespace mce {
    enum class PrimitiveMode : int {
        None = 0,
        QuadList = 1,
        TriangleList = 2,
        TriangleStrip = 3,
        LineList = 4,
        LineStrip = 5,
    };
};

class Tessellator {
public:
    void begin(mce::PrimitiveMode mode, int maxVertices) {
        using fn_t = decltype(&Tessellator::begin);
        static fn_t fn = std::bit_cast<fn_t>(selaura::find_signature<"48 89 74 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 80 B9 ? ? ? ? ? 45 0F B6 D9">());
        return (this->*fn)(mode, maxVertices);
    }

    void vertex(float x, float y, float z) {
        using fn_t = decltype(&Tessellator::vertex);
        static fn_t fn = std::bit_cast<fn_t>(selaura::find_signature<"4C 8B DC 55 57 49 8D 6B ? 48 81 EC ? ? ? ? 45 0F 29 4B">());
        return (this->*fn)(x, y, z);
    }

    void color(float r, float g, float b, float a) {
        using fn_t = decltype(&Tessellator::color);
        static fn_t fn = std::bit_cast<fn_t>(selaura::find_signature<"80 B9 ? ? ? ? ? 4C 8B C1 75">());
        return (this->*fn)(r, g, b, a);
    }
};