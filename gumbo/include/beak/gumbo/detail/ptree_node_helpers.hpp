#pragma once
#include <string>
#include <boost/optional.hpp>
#include <boost/property_tree/ptree_fwd.hpp>

namespace beak::gumbo {

struct node;

namespace detail {

struct node_tree_translator {
    using internal_type = beak::gumbo::node;
    using external_type = std::string;
    auto get_value(const internal_type&) const -> boost::optional<external_type>;
    auto put_value(const external_type&) const -> boost::optional<internal_type>;
};

} // namespace detail
} // namespace beak::gumbo

namespace boost::property_tree {

template <>
struct translator_between<beak::gumbo::node, std::string> {
    using type = beak::gumbo::detail::node_tree_translator;
};

} // namespace boost::property_tree
