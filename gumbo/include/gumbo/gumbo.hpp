#pragma once
#include <iosfwd>
#include <string>
#include <string_view>
#include <variant>
#include <vector>
#include <boost/optional.hpp>
#include <boost/property_tree/ptree.hpp>
#include "gumbo/enums.hpp"

namespace beak::gumbo {

struct source_position
{
    int _line;
    int _column;
    int _offset;
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
    DocTypeQuirksMode _doc_type_quicks_mode;
};

struct text
{
    NodeType _node_type;
    std::string _text;
    std::string_view _original_text;
    source_position _start_position;
};

struct element
{
    struct attribute
    {
        AttributeNamespace _attribute_namespace;
        std::string _name;
        std::string_view _original_name;
        std::string _value;
        std::string_view _original_value;
        source_position _name_start;
        source_position _name_end;
        source_position _value_start;
        source_position _value_end;
    };

    NodeType _node_type;
    Tag _tag;
    WebNamespace _tag_namespace;
    std::string_view _original_tag;
    source_position _start_position;
    std::string_view _original_end_tag;
    source_position _end_position;
    std::vector<attribute> _attributes;
};

struct node
{
    boost::optional<node&> _parent;
    ParseFlags::Flags _parse_flags;
    std::variant<document, text, element> _value;
    bool empty() const;
};

struct parse_options
{
    bool _stop_on_first_error{false};
    boost::optional<int> _max_errors;
    Tag _fragment_context{Tag::Last};
    WebNamespace _web_namespace{WebNamespace::HTML};
};

struct parse_output
{
    using tree_type = boost::property_tree::basic_ptree<std::string, node>;
    explicit parse_output(std::string_view html, parse_options = parse_options{});
    const tree_type& tree() const;

private:
    const tree_type _tree;
};
//std::ostream& operator<<(std::ostream& os, const parse_output::tree_type&);

} // namespace beak::gumbo
