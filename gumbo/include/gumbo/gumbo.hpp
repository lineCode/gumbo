#pragma once
#include <string>
#include <string_view>
#include <variant>
#include <vector>
#include <boost/optional.hpp>
#include <boost/property_tree/ptree.hpp>
#include "gumbo/detail/ptree_node_helpers.hpp"
#include "gumbo/enums.hpp"

namespace beak::gumbo {

struct text
{
    node_type _node_type;
    std::string _text;
    std::string_view _original_text;
};

struct element
{
    struct attribute
    {
        attribute_namespace _attribute_namespace;
        std::string _name;
        std::string_view _original_name;
        std::string _value;
        std::string_view _original_value;
    };

    node_type _node_type;
    tag _tag;
    web_namespace _tag_namespace;
    std::string_view _original_tag;
    std::string_view _original_end_tag;
    std::vector<attribute> _attributes;
};

struct node
{
    boost::optional<node&> _parent;
    parse_flags::flags _parse_flags;
    std::variant<text, element> _value;
    bool empty() const;
};

struct document
{
    struct doc_type
    {
        std::string _name;
        std::string _public_identifier;
        std::string _system_identifier;
    };

    boost::optional<doc_type> _doc_type;
    doctype_quirks_mode _doc_type_quicks_mode;
};

struct parse_options
{
    bool _stop_on_first_error{false};
    boost::optional<int> _max_errors;
    tag _fragment_context{tag::Last};
    web_namespace _web_namespace{web_namespace::HTML};
};

struct parse_output
{
    using tree_type = boost::property_tree::basic_ptree<std::string, node>;
    explicit parse_output(std::string_view html, parse_options = parse_options{});
    document _document;
    tree_type _tree;
};

} // namespace beak::gumbo