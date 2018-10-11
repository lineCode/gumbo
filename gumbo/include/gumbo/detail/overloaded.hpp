#pragma once

namespace beak::gumbo::detail {

template <typename... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};
template <typename... Ts>
overloaded(Ts...)->overloaded<Ts...>;

} // namespace beak::gumbo::detail
