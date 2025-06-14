#include "ImageDescription.hpp"
#include <spdlog/spdlog.h>

uint32_t cg::ImageDescription::getStrideFromFormat(const mce::TextureFormat format)
{
    switch (format) {
        case mce::TextureFormat::R32G32B32A32_FLOAT:
            return 16;

        case mce::TextureFormat::R8G8B8A8_UNORM:
            return 4;

        case mce::TextureFormat::A8_UNORM:
            return 1;

        default:
            spdlog::error("Case {} has not been implemented in getStrideFromFormat", (int)format);
    }
}
