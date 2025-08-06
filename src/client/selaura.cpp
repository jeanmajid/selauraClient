#include "selaura.hpp"

#include "libhat/scanner.hpp"
#include "memory/patterns/win/patterns.hpp"

namespace selaura {
    std::shared_ptr<client> client_instance = nullptr;

    client::~client() {
    }

    void client::init() {
        if (auto self = shared_from_this(); self) {
            client_instance = self;
        }

        auto start = std::chrono::high_resolution_clock::now();

        this->get<scanner>().start_scanning_thread();
        this->get<scanner>().kill_scanning_thread();

        std::println("r: {}", selaura::signature_runtime_value<&hi>::value);

        auto end = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::println("Injected [{}ms]", ms);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        this->m_running = false;
    }

    std::shared_ptr<client>& get() {
        return client_instance;
    }
};