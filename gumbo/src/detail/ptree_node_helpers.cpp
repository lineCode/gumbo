#include "gumbo/detail/ptree_node_helpers.hpp"
#include <variant>
#include "gumbo/gumbo.hpp"

namespace {

template <typename... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};
template <typename... Ts>
overloaded(Ts...)->overloaded<Ts...>;

} // namespace

namespace beak::gumbo::detail {

auto node_tree_translator::get_value(const beak::gumbo::node& n) const -> boost::optional<std::string>
{
    std::stringstream ss;
    std::visit(
        overloaded{
            [&](const text& t) { ss << t._original_text; },
            [](const element&) {},
            [](const document&) {}},
        n._value);
    return ss.str();
}

auto node_tree_translator::put_value(const std::string&) const -> boost::optional<beak::gumbo::node>
{
    return boost::none;
}

} // namespace beak::gumbo::detail
