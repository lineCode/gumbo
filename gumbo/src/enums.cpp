#include "gumbo/enums.hpp"
#include <array>
#include <experimental/array>
#include <ostream>
#include <boost/algorithm/string/predicate.hpp>

namespace {

template <typename T, typename Enum>
struct enum_conversion
{
    using case_sensitive = beak::gumbo::case_sensitive;

    static constexpr std::string_view to_string_view(Enum e)
    {
        using index_type = typename decltype(T::map)::size_type;
        return std::get<std::string_view>(T::map[static_cast<index_type>(e)]);
    }

    static constexpr boost::optional<Enum> to_enum(
        std::string_view view,
        case_sensitive sensitive)
    {
        const auto it = std::find_if(
            T::map.begin(),
            T::map.end(),
            [&](const auto& v) {
                const auto& sv = std::get<std::string_view>(v);
                if (sensitive == case_sensitive::True)
                    return sv == view;
                else
                    return boost::iequals(sv, view);
            });
        if (it == T::map.end()) return boost::none;
        return std::get<Enum>(*it);
    }

protected:
    using p = std::pair<Enum, std::string_view>;
    template <typename... Args>
    static constexpr auto make_lookup(Args&&... args)
    {
        return std::experimental::make_array<p>(std::forward<Args>(args)...);
    }
};

} // namespace

namespace beak::gumbo {

struct tag_conversion : enum_conversion<tag_conversion, tag>
{
    static constexpr auto map = make_lookup(
        p{tag::Html, "html"},
        p{tag::Head, "head"},
        p{tag::Title, "title"},
        p{tag::Base, "base"},
        p{tag::Link, "link"},
        p{tag::Meta, "meta"},
        p{tag::Style, "style"},
        p{tag::Script, "script"},
        p{tag::Noscript, "noscript"},
        p{tag::Template, "template"},
        p{tag::Body, "body"},
        p{tag::Article, "article"},
        p{tag::Section, "section"},
        p{tag::Nav, "nav"},
        p{tag::Aside, "aside"},
        p{tag::H1, "h1"},
        p{tag::H2, "h2"},
        p{tag::H3, "h3"},
        p{tag::H4, "h4"},
        p{tag::H5, "h5"},
        p{tag::H6, "h6"},
        p{tag::Hgroup, "hgroup"},
        p{tag::Header, "header"},
        p{tag::Footer, "footer"},
        p{tag::Address, "address"},
        p{tag::P, "p"},
        p{tag::Hr, "hr"},
        p{tag::Pre, "pre"},
        p{tag::Blockquote, "blockquote"},
        p{tag::Ol, "ol"},
        p{tag::Ul, "ul"},
        p{tag::Li, "li"},
        p{tag::Dl, "dl"},
        p{tag::Dt, "dt"},
        p{tag::Dd, "dd"},
        p{tag::Figure, "figure"},
        p{tag::Figcaption, "figcaption"},
        p{tag::Main, "main"},
        p{tag::Div, "div"},
        p{tag::A, "a"},
        p{tag::Em, "em"},
        p{tag::Strong, "strong"},
        p{tag::Small, "small"},
        p{tag::S, "s"},
        p{tag::Cite, "cite"},
        p{tag::Q, "q"},
        p{tag::Dfn, "dfn"},
        p{tag::Abbr, "abbr"},
        p{tag::Data, "data"},
        p{tag::Time, "time"},
        p{tag::Code, "code"},
        p{tag::Var, "var"},
        p{tag::Samp, "samp"},
        p{tag::Kbd, "kbd"},
        p{tag::Sub, "sub"},
        p{tag::Sup, "sup"},
        p{tag::I, "i"},
        p{tag::B, "b"},
        p{tag::U, "u"},
        p{tag::Mark, "mark"},
        p{tag::Ruby, "ruby"},
        p{tag::Rt, "rt"},
        p{tag::Rp, "rp"},
        p{tag::Bdi, "bdi"},
        p{tag::Bdo, "bdo"},
        p{tag::Span, "span"},
        p{tag::Br, "br"},
        p{tag::Wbr, "wbr"},
        p{tag::Ins, "ins"},
        p{tag::Del, "del"},
        p{tag::Image, "image"},
        p{tag::Img, "img"},
        p{tag::Iframe, "iframe"},
        p{tag::Embed, "embed"},
        p{tag::Object, "object"},
        p{tag::Param, "param"},
        p{tag::Video, "video"},
        p{tag::Audio, "audio"},
        p{tag::Source, "source"},
        p{tag::Track, "track"},
        p{tag::Canvas, "canvas"},
        p{tag::Map, "map"},
        p{tag::Area, "area"},
        p{tag::Math, "math"},
        p{tag::Mi, "mi"},
        p{tag::Mo, "mo"},
        p{tag::Mn, "mn"},
        p{tag::Ms, "ms"},
        p{tag::Mtext, "mtext"},
        p{tag::Mglyph, "mglyph"},
        p{tag::Malignmark, "malignmark"},
        p{tag::Annotation_xml, "annotation_xml"},
        p{tag::Svg, "svg"},
        p{tag::Foreignobject, "foreignobject"},
        p{tag::Desc, "desc"},
        p{tag::Table, "table"},
        p{tag::Caption, "caption"},
        p{tag::Colgroup, "colgroup"},
        p{tag::Col, "col"},
        p{tag::Tbody, "tbody"},
        p{tag::Thead, "thead"},
        p{tag::Tfoot, "tfoot"},
        p{tag::Tr, "tr"},
        p{tag::Td, "td"},
        p{tag::Th, "th"},
        p{tag::Form, "form"},
        p{tag::Fieldset, "fieldset"},
        p{tag::Legend, "legend"},
        p{tag::Label, "label"},
        p{tag::Input, "input"},
        p{tag::Button, "button"},
        p{tag::Select, "select"},
        p{tag::Datalist, "datalist"},
        p{tag::Optgroup, "optgroup"},
        p{tag::Option, "option"},
        p{tag::Textarea, "textarea"},
        p{tag::Keygen, "keygen"},
        p{tag::Output, "output"},
        p{tag::Progress, "progress"},
        p{tag::Meter, "meter"},
        p{tag::Details, "details"},
        p{tag::Summary, "summary"},
        p{tag::Menu, "menu"},
        p{tag::Menuitem, "menuitem"},
        p{tag::Applet, "applet"},
        p{tag::Acronym, "acronym"},
        p{tag::Bgsound, "bgsound"},
        p{tag::Dir, "dir"},
        p{tag::Frame, "frame"},
        p{tag::Frameset, "frameset"},
        p{tag::Noframes, "noframes"},
        p{tag::Isindex, "isindex"},
        p{tag::Listing, "listing"},
        p{tag::Xmp, "xmp"},
        p{tag::Nextid, "nextid"},
        p{tag::Noembed, "noembed"},
        p{tag::Plaintext, "plaintext"},
        p{tag::Rb, "rb"},
        p{tag::Strike, "strike"},
        p{tag::Basefont, "basefont"},
        p{tag::Big, "big"},
        p{tag::Blink, "blink"},
        p{tag::Center, "center"},
        p{tag::Font, "font"},
        p{tag::Marquee, "marquee"},
        p{tag::Multicol, "multicol"},
        p{tag::Nobr, "nobr"},
        p{tag::Spacer, "spacer"},
        p{tag::Tt, "tt"},
        p{tag::Rtc, "rtc"},
        p{tag::Unknown, "unknown"},
        p{tag::Last, "last"});
};

struct attribute_namespace_conversion : enum_conversion<attribute_namespace_conversion, attribute_namespace>
{
    static constexpr auto map = make_lookup(
        p{attribute_namespace::None, "none"},
        p{attribute_namespace::XLink, "XLink"},
        p{attribute_namespace::XML, "XML"},
        p{attribute_namespace::XMLNS, "XMLNS"});
};

struct node_type_conversion : enum_conversion<node_type_conversion, node_type>
{
    static constexpr auto map = make_lookup(
        p{node_type::Element, "element"},
        p{node_type::Text, "text"},
        p{node_type::CDATA, "CDATA"},
        p{node_type::Comment, "comment"},
        p{node_type::Whitespace, "whitespace"},
        p{node_type::Template, "template"});
};

struct element_type_conversion : enum_conversion<element_type_conversion, element_type>
{
    static constexpr auto map = make_lookup(
        p{element_type::Element, "element"},
        p{element_type::Template, "template"});
};

struct text_type_conversion : enum_conversion<text_type_conversion, text_type>
{
    static constexpr auto map = make_lookup(
        p{text_type::Text, "text"},
        p{text_type::CDATA, "CDATA"},
        p{text_type::Comment, "comment"},
        p{text_type::Whitespace, "whitespace"});
};

struct doctype_quirks_mode_conversion : enum_conversion<doctype_quirks_mode_conversion, doctype_quirks_mode>
{
    static constexpr auto map = make_lookup(
        p{doctype_quirks_mode::NoQuirks, "no_quirks"},
        p{doctype_quirks_mode::Quirks, "quirks"},
        p{doctype_quirks_mode::LimitedQuicks, "limited_quirks"});
};

struct web_namespace_conversion : enum_conversion<web_namespace_conversion, web_namespace>
{
    static constexpr auto map = make_lookup(
        p{web_namespace::HTML, "HTML"},
        p{web_namespace::SVG, "SVG"},
        p{web_namespace::MATHML, "MATHML"});
};

auto to_string_view(tag t) -> std::string_view
{
    return tag_conversion::to_string_view(t);
}

auto to_string_view(attribute_namespace an) -> std::string_view
{
    return attribute_namespace_conversion::to_string_view(an);
}

auto to_string_view(node_type type) -> std::string_view
{
    return node_type_conversion::to_string_view(type);
}

auto to_string_view(element_type type) -> std::string_view
{
    return element_type_conversion::to_string_view(type);
}

auto to_string_view(text_type type) -> std::string_view
{
    return text_type_conversion::to_string_view(type);
}

auto to_string_view(doctype_quirks_mode mode) -> std::string_view
{
    return doctype_quirks_mode_conversion::to_string_view(mode);
}

auto to_string_view(web_namespace ns) -> std::string_view
{
    return web_namespace_conversion::to_string_view(ns);
}

auto operator<<(std::ostream& os, tag t) -> std::ostream&
{
    os << to_string_view(t);
    return os;
}

auto operator<<(std::ostream& os, attribute_namespace an) -> std::ostream&
{
    os << to_string_view(an);
    return os;
}

auto operator<<(std::ostream& os, node_type type) -> std::ostream&
{
    os << to_string_view(type);
    return os;
}

auto operator<<(std::ostream& os, element_type type) -> std::ostream&
{
    os << to_string_view(type);
    return os;
}

auto operator<<(std::ostream& os, text_type type) -> std::ostream&
{
    os << to_string_view(type);
    return os;
}

auto operator<<(std::ostream& os, doctype_quirks_mode mode) -> std::ostream&
{
    os << to_string_view(mode);
    return os;
}

auto operator<<(std::ostream& os, web_namespace ns) -> std::ostream&
{
    os << to_string_view(ns);
    return os;
}

auto to_tag(std::string_view view, case_sensitive sensitive) -> boost::optional<tag>
{
    return tag_conversion::to_enum(view, sensitive);
}

auto to_attribute_namespace(std::string_view view, case_sensitive sensitive) -> boost::optional<attribute_namespace>
{
    return attribute_namespace_conversion::to_enum(view, sensitive);
}

auto to_node_type(std::string_view view, case_sensitive sensitive) -> boost::optional<node_type>
{
    return node_type_conversion::to_enum(view, sensitive);
}

auto to_element_type(std::string_view view, case_sensitive sensitive) -> boost::optional<element_type>
{
    return element_type_conversion::to_enum(view, sensitive);
}

auto to_text_type(std::string_view view, case_sensitive sensitive) -> boost::optional<text_type>
{
    return text_type_conversion::to_enum(view, sensitive);
}

auto to_doctype_quirks_mode(std::string_view view, case_sensitive sensitive) -> boost::optional<doctype_quirks_mode>
{
    return doctype_quirks_mode_conversion::to_enum(view, sensitive);
}

auto to_web_namespace(std::string_view view, case_sensitive sensitive) -> boost::optional<web_namespace>
{
    return web_namespace_conversion::to_enum(view, sensitive);
}

} // namespace beak::gumbo
