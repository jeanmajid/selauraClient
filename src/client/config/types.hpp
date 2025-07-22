#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <glaze/glaze.hpp>
#include "../feature/feature.hpp"

template <typename T>
struct glz::meta<selaura::feature<T>> {
    static constexpr auto value = glz::object(
        &selaura::feature<T>::get_name, "name",
        &selaura::feature<T>::get_description, "description",
        &selaura::feature<T>::is_enabled, "enabled",
        &selaura::feature<T>::get_hotkey, "hotkey",
        &selaura::feature<T>::settings, "settings"
    );
};

template <>
struct glz::meta<selaura::feature_setting<float>> {
    static constexpr auto value = glz::object(
        &selaura::feature_setting<float>::name, "name",
        &selaura::feature_setting<float>::value, "value",
        &selaura::feature_setting<float>::minimum_value, "min",
        &selaura::feature_setting<float>::maximum_value, "max",
        &selaura::feature_setting<float>::step, "step"
    );
};

template <>
struct glz::meta<selaura::feature_setting<bool>> {
    static constexpr auto value = glz::object(
        &selaura::feature_setting<bool>::name, "name",
        &selaura::feature_setting<bool>::value, "value"
    );
};

template <>
struct glz::meta<selaura::feature_setting<glm::vec4>> {
    static constexpr auto value = glz::object(
        &selaura::feature_setting<glm::vec4>::name, "name",
        &selaura::feature_setting<glm::vec4>::value, "value"
    );
};

template <>
struct glz::meta<glm::vec4> {
    static constexpr auto value = glz::array(
        &glm::vec4::x, &glm::vec4::y, &glm::vec4::z, &glm::vec4::w
    );
};
