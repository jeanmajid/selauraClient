#include "enchant_glint.hpp"
#include "../../../client.hpp"

namespace selaura {
    void enchant_glint::on_enable() {
        auto& evm = selaura::get()->get<selaura::event_manager>();
        evm.subscribe(&enchant_glint::on_renderiteminhanddescription_event, this);
    }

    void enchant_glint::on_disable() {
        auto& evm = selaura::get()->get<selaura::event_manager>();
        evm.unsubscribe(&enchant_glint::on_renderiteminhanddescription_event, this);
    }

    glm::vec4 enchant_glint::get_chroma_color(float speed, float saturation, float value) {
        using clock = std::chrono::steady_clock;
        using seconds_f = std::chrono::duration<float>;

        float time = std::chrono::duration_cast<seconds_f>(clock::now().time_since_epoch()).count();
        float hue = std::fmod(time * speed * 60.0f, 360.0f);

        float c = value * saturation;
        float x = c * (1.0f - std::abs(std::fmod(hue / 60.0f, 2.0f) - 1.0f));
        float m = value - c;

        float r = 0, g = 0, b = 0;
        switch (static_cast<int>(hue / 60.0f)) {
            case 0:  r = c; g = x; b = 0; break;
            case 1:  r = x; g = c; b = 0; break;
            case 2:  r = 0; g = c; b = x; break;
            case 3:  r = 0; g = x; b = c; break;
            case 4:  r = x; g = 0; b = c; break;
            case 5:  r = c; g = 0; b = x; break;
        }

        return glm::vec4(r + m, g + m, b + m, 1.0f);
    }

    void enchant_glint::on_renderiteminhanddescription_event(selaura::RenderItemInHandDescription_event &event) {
        auto& color = std::get<0>(this->settings).value;
        auto& chroma = std::get<1>(this->settings).value;
        auto& chroma_speed = std::get<2>(this->settings).value;

        if (chroma) {
            auto chroma_col = get_chroma_color(chroma_speed);
            event.color = { chroma_col.r, chroma_col.g, chroma_col.b };
            event.alpha = chroma_col.a;
        } else {
            event.color = {color.r / 255, color.g / 255, color.b / 255};
            event.alpha = color.a;
        }
    }

};