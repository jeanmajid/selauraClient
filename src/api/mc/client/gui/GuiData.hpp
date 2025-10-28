#pragma once
#include <api/imports.hpp>
#include <hooks/memory.hpp>
#include <string>

class GuiData {
public:
    void displayLocalMessage(const std::string& message) {
        using fn_t = decltype(&GuiData::displayLocalMessage);
        static fn_t fn = std::bit_cast<fn_t>(selaura::find_signature<"E8 ? ? ? ? 90 48 85 DB 74 ? 48 8B CB E8 ? ? ? ? 90 E9 ? ? ? ? 0F 57 C0 0F 11 45 ? 66 0F 6F 0D">());
        return (this->*fn)(message);
    }
};
