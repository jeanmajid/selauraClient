#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <atomic>
#include <concepts>
#include <memory>

namespace Selaura {
    enum EventPhase {
        Pre = 0,
        Post = 1
    };

    struct Event {
        Event() = default;
        virtual ~Event() = default;
    };

    struct CancelableEvent : Event {
        void Cancel() { mCancelled = true; }
        bool IsCancelled() const { return mCancelled; }
    private:
        bool mCancelled = false;
    };

    class EventManager {
    public:
        using listener_id = std::size_t;

        EventManager() = default;
        ~EventManager() = default;

        EventManager(const EventManager&) = delete;
        EventManager& operator=(const EventManager&) = delete;

        template <typename T>
        listener_id subscribe(std::function<void(T&)> fn) {
            auto& bus = get_bus<T>();
            listener_id id = ++bus.next_id;
            bus.listeners.emplace(id, std::move(fn));
            return id;
        }

        template <typename C, typename T>
        listener_id subscribe(C* instance, void (C::*method)(T&)) {
            return subscribe<T>([instance, method](T& e) {
                (instance->*method)(e);
            });
        }

        template <typename E>
        listener_id subscribe(void(*fn)(E&)) {
            return subscribe<E>([fn](E& e) {
                fn(e);
            });
        }

        template <typename T>
        bool unsubscribe(listener_id id) {
            auto it = buses.find(std::type_index(typeid(T)));
            if (it == buses.end()) return false;
            auto& bus = *static_cast<event_bus<T>*>(it->second.get());
            return bus.listeners.erase(id) > 0;
        }

        template <typename T>
        void post(T& e) {
            auto it = buses.find(std::type_index(typeid(T)));
            if (it == buses.end()) return;

            auto& bus = *static_cast<event_bus<T>*>(it->second.get());
            auto snapshot = bus.listeners;

            for (auto& [id, fn] : snapshot) {
                fn(e);
                if constexpr (std::derived_from<T, CancelableEvent>)
                    if (e.IsCancelled())
                        break;
            }
        }

        template <typename T>
        void unsubscribe_all() {
            auto it = buses.find(std::type_index(typeid(T)));
            if (it != buses.end()) {
                auto& bus = *static_cast<event_bus<T>*>(it->second.get());
                bus.listeners.clear();
            }
        }

        void clear() {
            buses.clear();
        }

    private:
        struct base_bus {
            virtual ~base_bus() = default;
        };

        template <typename T>
        struct event_bus : base_bus {
            using fn_t = std::function<void(T&)>;
            std::unordered_map<listener_id, fn_t> listeners;
            std::atomic<listener_id> next_id = 0;
        };

        template <typename T>
        event_bus<T>& get_bus() {
            auto key = std::type_index(typeid(T));
            auto it = buses.find(key);
            if (it == buses.end()) {
                auto bus = std::make_unique<event_bus<T>>();
                auto* ptr = bus.get();
                buses.emplace(key, std::move(bus));
                return *ptr;
            }
            return *static_cast<event_bus<T>*>(buses[key].get());
        }

        std::unordered_map<std::type_index, std::unique_ptr<base_bus>> buses;
    };

}