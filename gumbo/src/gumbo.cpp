#include "beak/gumbo/gumbo.hpp"
#include <set>
#include <stack>
#include "beak/util/overloaded.hpp"
#include "original/gumbo.h"

namespace beak::gumbo {

auto get_key(const node& node) -> std::string
{
    return std::visit(
     util::overloaded{
      [](const text&) -> std::string { return "<xmltext>"; },
      [](const element& e) -> std::string { const auto sv = to_string_view(e._tag); return std::string{sv.data(), sv.size()}; },
      [](const document&) -> std::string { return ""; },
      [](const attribute&) -> std::string { return ""; }},
     node._value);
}

auto get_children(const GumboNode& node) -> boost::optional<const GumboVector&>
{
    switch (node.type) {
        case GUMBO_NODE_DOCUMENT: return node.v.document.children;
        case GUMBO_NODE_ELEMENT:
        case GUMBO_NODE_TEMPLATE: return node.v.element.children;
        case GUMBO_NODE_TEXT:
        case GUMBO_NODE_CDATA:
        case GUMBO_NODE_COMMENT:
        case GUMBO_NODE_WHITESPACE: return boost::none;
    }
    assert(false);
    throw std::runtime_error("unhandled node type");
}

auto get_document(const GumboDocument& d) -> document
{
    return document{
     [&]() -> boost::optional<document::doc_type> {
         if (!d.has_doctype) return boost::none;
         return document::doc_type{
          d.name, d.public_identifier, d.system_identifier};
     }(),
     static_cast<doctype_quirks_mode>(d.doc_type_quirks_mode)};
}

auto get_attributes(const GumboElement& e) -> std::pair<std::string, parse_output::tree>
{
    parse_output::tree tree;
    for (int i = 0; i < static_cast<int>(e.attributes.length); ++i) {
        const auto a = static_cast<GumboAttribute*>(e.attributes.data[i]);
        const auto name = std::string{a->name};
        node n{
         boost::none,
         parse_flags::flags{0},
         attribute{
          static_cast<attribute_namespace>(a->attr_namespace),
          name,
          std::string_view{a->original_name.data, a->original_name.length},
          std::string{a->value},
          std::string_view{a->original_value.data, a->original_value.length}}};
        tree.push_back(std::pair{name, parse_output::tree{std::move(n)}});
    }
    return {"<xmlattr>", tree};
}

auto get_element(const GumboElement& e, element_type t) -> element
{
    return element{
     t,
     static_cast<tag>(e.tag),
     static_cast<web_namespace>(e.tag_namespace),
     std::string_view{e.original_tag.data, e.original_tag.length},
     std::string_view{e.original_end_tag.data, e.original_end_tag.length},
    };
}

auto get_text(const GumboText& e, text_type t) -> text
{
    return text{
     t,
     e.text,
     std::string_view{e.original_text.data, e.original_text.length}};
}

auto get_node_type(const GumboNode& node) -> std::variant<document, text, element, attribute>
{
    switch (node.type) {
        case GUMBO_NODE_DOCUMENT: return get_document(node.v.document);
        case GUMBO_NODE_ELEMENT: return get_element(node.v.element, element_type::Element);
        case GUMBO_NODE_TEMPLATE: return get_element(node.v.element, element_type::Template);
        case GUMBO_NODE_TEXT: return get_text(node.v.text, text_type::Text);
        case GUMBO_NODE_CDATA: return get_text(node.v.text, text_type::CDATA);
        case GUMBO_NODE_WHITESPACE: return get_text(node.v.text, text_type::Whitespace);
        case GUMBO_NODE_COMMENT: return get_text(node.v.text, text_type::Comment);
    }
    assert(false);
    throw std::runtime_error("unhandled node type");
}

auto traverse(const GumboNode& root, const parse_options& opts) -> std::pair<std::string, parse_output::tree>
{
    using tree_type = parse_output::tree;
    tree_type tree{node{boost::none, static_cast<parse_flags::flags>(root.parse_flags), get_node_type(root)}};
    if (std::holds_alternative<element>(tree.data()._value)) {
        tree.push_back(get_attributes(root.v.element));
    }
    const auto children = get_children(root);
    if (!children) return {get_key(tree.data()), tree};
    for (int i = 0; i < static_cast<int>(children->length); ++i) {
        const auto child = static_cast<const GumboNode*>(children->data[i]);
        auto it = tree.push_back(traverse(*child, opts));
        it->second.data()._parent = tree.data();
    }

    return {get_key(tree.data()), tree};
}

auto element::contained_text() const -> std::string_view
{
    const auto begin = _original_tag.end();
    const auto length = static_cast<std::string_view::size_type>(
     std::distance(begin, _original_end_tag.begin()));
    return std::string_view{begin, length};
}

auto node::empty() const -> bool
{
    if (!std::holds_alternative<text>(_value)) return true;
    return std::get<text>(_value)._text.empty();
}

parse_output::parse_output(std::string_view html, parse_options o)
{
    const GumboOptions gumbo_options{
     kGumboDefaultOptions.allocator,
     kGumboDefaultOptions.deallocator,
     kGumboDefaultOptions.userdata,
     kGumboDefaultOptions.tab_stop,
     o._stop_on_first_error,
     o._max_errors.value_or(-1),
     static_cast<GumboTag>(o._fragment_context),
     static_cast<GumboNamespaceEnum>(o._web_namespace)};

    GumboOutput* output = gumbo_parse_with_options(
     &gumbo_options,
     html.data(),
     html.size());

    _document = traverse(*output->document, o).second;

    gumbo_destroy_output(
     &gumbo_options,
     output);
}

} // namespace beak::gumbo
