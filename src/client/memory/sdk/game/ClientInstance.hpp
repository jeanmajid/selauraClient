#pragma once
#include <cstddef>

#include "../gui/gui/GuiData.hpp"

struct ClientInstance {
    std::byte pad[0x5B8];
    GuiData* guiData;
};
