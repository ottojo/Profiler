/**
 * @file OptionalSerialization.hpp
 * @author Jonas
 * @date 10.04.2020
 * @brief Adds serialization and deserialization for std::optional<T> if T is serializable
 */

#ifndef OPTIONALSERIALIZATION_HPP
#define OPTIONALSERIALIZATION_HPP

#include <nlohmann/json.hpp>
#include <optional>

namespace nlohmann {
    template<typename T>
    struct adl_serializer<std::optional<T>> {
        static void to_json(json &j, const std::optional<T> &opt) {
            if (opt.has_value()) {
                j = opt.value();
            } else {
                j = nullptr;
            }
        }

        static void from_json(const json &j, std::optional<T> &opt) {
            if (j.is_null()) {
                opt = std::nullopt;
            } else {
                opt = j.get<T>();
            }
        }
    };
} // namespace nlohmann

#endif // OPTIONALSERIALIZATION_HPP
