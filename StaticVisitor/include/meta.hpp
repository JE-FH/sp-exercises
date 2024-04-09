#ifndef STATIC_VISITOR_META_HPP
#define STATIC_VISITOR_META_HPP

/**
 * TODO: implement meta-predicates
 * (template classes/variables taking type and returning bool)
 * is_bool_v
 * is_number_v
 * is_character_v
 * is_string_v
 * is_container_v
 * accepts_v
 *
 * Tips:
 * - read documentation about std::is_same, std::is_integral, std::is_floating_point, std::is_arithmetic.
 * - make your meta-predicates robust against const/volatile/reference combinations (see meta_test.cpp):
 *   see std::remove_reference, std::remove_const, std::remove_cvref, std::decay
 */

#include <type_traits>
#include <string>
#include <tuple>
#include <utility>

template <typename T>
constexpr auto is_bool_v = std::is_same_v<std::remove_cvref_t<T>, bool>;

template <typename T>
constexpr auto is_number_v =
    !std::is_same_v<std::remove_cvref_t<T>, bool> &&
    (std::is_integral_v<std::remove_cvref_t<T>> || std::is_floating_point_v<std::remove_cvref_t<T>>);

template <typename T>
constexpr auto is_character_v = std::is_same_v<std::remove_cvref_t<T>, char>;

template <typename T>
constexpr auto is_string_v = std::is_same_v<std::remove_cvref_t<T>, std::string> ||
                             is_character_v<std::remove_extent_t<T>> || is_character_v<std::remove_pointer_t<T>>;

template <typename T>
constexpr auto is_tuple_v = requires {
    {
        std::tuple_size<T>()
    } -> std::convertible_to<std::size_t>;
};

template <typename T>
constexpr auto is_container_v = requires(T&& c) {
    {
        std::cbegin(c)
    };
    {
        std::cend(c)
    };
} && !is_string_v<T>;

template <typename T>
constexpr auto is_writeable_container_v = requires(T&& c) {
    {
        c.emplace_back()
    };
} && !is_string_v<T>;

template <typename Data, typename Visitor>
constexpr auto accepts_v = requires(Data d, Visitor v) {
    {
        d.accept(v)
    };
};

template <typename T>
concept BoolC = is_bool_v<T>;

template <typename T>
concept NumberC = is_number_v<T>;

template <typename T>
concept StringC = is_string_v<T>;

template <typename T>
concept ContainerC = is_container_v<T>;

template <typename T>
concept WriteableContainer = is_writeable_container_v<T>;

template <typename T, typename W>
concept DataC = accepts_v<T, W>;

template <typename T>
concept TupleC = is_tuple_v<T>;

template <typename T>
class TD;

#endif  // STATIC_VISITOR_META_HPP
