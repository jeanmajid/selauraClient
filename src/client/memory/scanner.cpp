#include "scanner.hpp"

namespace selaura {
    void scanner::start_scanning_thread() {
        this->m_scanning_thread = std::thread([this]() {
            this->game_handle = selaura::get_handle(
#ifdef SELAURA_WINDOWS
            "Minecraft.Windows.exe"
#else
            "libminecraftpe.so"
#endif
            );
            this->resolve_all_async(signatures);
        });
    }

    void scanner::kill_scanning_thread() {
        if (this->m_scanning_thread.joinable()) {
            this->m_scanning_thread.join();
        }
        m_scanning_thread = std::thread();
    }

    void scanner::init() {
        this->start_scanning_thread();
        this->kill_scanning_thread();
    }
};