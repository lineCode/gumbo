#include "gumbo/gumbo.hpp"
#include <set>
#include <stack>
#include "original/gumbo.h"

namespace beak::gumbo {

std::string get_key(const GumboNode& node)
{
    switch (node.type) {
        case GUMBO_NODE_DOCUMENT: return "";
        case GUMBO_NODE_ELEMENT: {
            const auto& tag = node.v.element.original_tag;
            if (tag.length == 0) return "";
            return std::string{tag.data + 1, tag.length - 2};
        }
        case GUMBO_NODE_TEMPLATE:
        case GUMBO_NODE_TEXT:
        case GUMBO_NODE_CDATA:
        case GUMBO_NODE_COMMENT:
        case GUMBO_NODE_WHITESPACE: return "";
    }
    assert(false);
    throw std::runtime_error("unhandled node type");
}

boost::optional<const GumboVector&> get_children(const GumboNode& node)
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

std::variant<document, text, element> get_node_type(const GumboNode& node)
{
    switch (node.type) {
        case GUMBO_NODE_DOCUMENT: {
            const auto& d = node.v.document;
            return document{
                [&]() -> boost::optional<document::doc_type> {
                    if (!d.has_doctype) return boost::none;
                    return document::doc_type{
                        d.name, d.public_identifier, d.system_identifier};
                }(),
                static_cast<doctype_quirks_mode>(d.doc_type_quirks_mode)};
        }
        case GUMBO_NODE_ELEMENT:
        case GUMBO_NODE_TEMPLATE: {
            const auto& e = node.v.element;
            std::vector<element::attribute> attributes;
            attributes.reserve(e.attributes.length);
            for (int i = 0; i < static_cast<int>(e.attributes.length); ++i) {
                const auto a = static_cast<GumboAttribute*>(e.attributes.data[i]);
                attributes.push_back(element::attribute{
                    static_cast<attribute_namespace>(a->attr_namespace),
                    std::string{a->name},
                    std::string_view{a->original_name.data, a->original_name.length},
                    std::string{a->value},
                    std::string_view{a->original_value.data, a->original_value.length}});
            }
            return element{
                static_cast<node_type>(node.type),
                static_cast<tag>(e.tag),
                static_cast<web_namespace>(e.tag_namespace),
                std::string_view{e.original_tag.data, e.original_tag.length},
                std::string_view{e.original_end_tag.data, e.original_end_tag.length},
                std::move(attributes)};
        }
        case GUMBO_NODE_TEXT:
        case GUMBO_NODE_CDATA:
        case GUMBO_NODE_COMMENT:
        case GUMBO_NODE_WHITESPACE: {
            const auto& t = node.v.text;
            return text{
                static_cast<node_type>(node.type),
                t.text,
                std::string_view{t.original_text.data, t.original_text.length}};
        }
    }
    assert(false);
    throw std::runtime_error("unhandled node type");
}

parse_output::tree_type traverse(const GumboNode& root)
{
    using tree_type = parse_output::tree_type;
    tree_type tree{node{boost::none, parse_flags::flags{0}, get_node_type(root)}};
    const auto children = get_children(root);
    if (!children) return tree;
    for (int i = 0; i < static_cast<int>(children->length); ++i) {
        const auto child = static_cast<const GumboNode*>(children->data[i]);
        auto it = tree.push_back({get_key(*child), traverse(*child)});
        it->second.data()._parent = tree.data();
    }
    return tree;
} // namespace beak::gumbo

bool node::empty() const
{
    if (!std::holds_alternative<text>(_value)) return true;
    return std::get<text>(_value)._text.empty();
}

parse_output::parse_output(std::string_view html, parse_options o)
    : _tree{[&]() {
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

        const auto tree = traverse(*output->root);

        gumbo_destroy_output(
            &gumbo_options,
            output);

        return tree;
    }()}
{
}

const parse_output::tree_type& parse_output::tree() const
{
    return _tree;
}

template <typename... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};
template <typename... Ts>
overloaded(Ts...)->overloaded<Ts...>;

std::ostream& operator<<(std::ostream& os, const parse_output::tree_type& tree)
{
    const auto& n = tree.data();
    std::visit(
        overloaded{
            [&](const beak::gumbo::document&) {},
            [&](const beak::gumbo::element& e) {
                if (e._original_tag.empty()) {
                    os << "<empty " << static_cast<int>(e._tag) << ">";
                }
                os << e._original_tag;
                for (auto&& child : tree) {
                    os << child.second;
                }
                os << e._original_end_tag;
            },
            [&](const beak::gumbo::text& t) { os << t._original_text; }},
        n._value);
    return os;
}

} // namespace beak::gumbo
