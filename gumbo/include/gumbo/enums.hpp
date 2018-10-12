#pragma once
#include <iosfwd>
#include <string_view>
#include <boost/optional.hpp>

namespace beak::gumbo {

struct icase_t {
} constexpr icase;

enum class tag;
enum class attribute_namespace;
enum class node_type;
enum class element_type;
enum class text_type;
enum class doctype_quirks_mode;
enum class web_namespace;

auto to_string_view(tag) -> std::string_view;
auto to_string_view(attribute_namespace) -> std::string_view;
auto to_string_view(node_type) -> std::string_view;
auto to_string_view(element_type) -> std::string_view;
auto to_string_view(text_type) -> std::string_view;
auto to_string_view(doctype_quirks_mode) -> std::string_view;
auto to_string_view(web_namespace) -> std::string_view;

auto operator<<(std::ostream&, tag) -> std::ostream&;
auto operator<<(std::ostream&, attribute_namespace) -> std::ostream&;
auto operator<<(std::ostream&, node_type) -> std::ostream&;
auto operator<<(std::ostream&, element_type) -> std::ostream&;
auto operator<<(std::ostream&, text_type) -> std::ostream&;
auto operator<<(std::ostream&, doctype_quirks_mode) -> std::ostream&;
auto operator<<(std::ostream&, web_namespace) -> std::ostream&;

auto to_tag(std::string_view) -> boost::optional<tag>;
auto to_tag(std::string_view, icase_t) -> boost::optional<tag>;
auto to_attribute_namespace(std::string_view) -> boost::optional<attribute_namespace>;
auto to_attribute_namespace(std::string_view, icase_t) -> boost::optional<attribute_namespace>;
auto to_node_type(std::string_view) -> boost::optional<node_type>;
auto to_node_type(std::string_view, icase_t) -> boost::optional<node_type>;
auto to_element_type(std::string_view) -> boost::optional<element_type>;
auto to_element_type(std::string_view, icase_t) -> boost::optional<element_type>;
auto to_text_type(std::string_view) -> boost::optional<text_type>;
auto to_text_type(std::string_view, icase_t) -> boost::optional<text_type>;
auto to_doctype_quirks_mode(std::string_view) -> boost::optional<doctype_quirks_mode>;
auto to_doctype_quirks_mode(std::string_view, icase_t) -> boost::optional<doctype_quirks_mode>;
auto to_web_namespace(std::string_view) -> boost::optional<web_namespace>;
auto to_web_namespace(std::string_view, icase_t) -> boost::optional<web_namespace>;

enum class tag
{
    Html,
    Head,
    Title,
    Base,
    Link,
    Meta,
    Style,
    Script,
    Noscript,
    Template,
    Body,
    Article,
    Section,
    Nav,
    Aside,
    H1,
    H2,
    H3,
    H4,
    H5,
    H6,
    Hgroup,
    Header,
    Footer,
    Address,
    P,
    Hr,
    Pre,
    Blockquote,
    Ol,
    Ul,
    Li,
    Dl,
    Dt,
    Dd,
    Figure,
    Figcaption,
    Main,
    Div,
    A,
    Em,
    Strong,
    Small,
    S,
    Cite,
    Q,
    Dfn,
    Abbr,
    Data,
    Time,
    Code,
    Var,
    Samp,
    Kbd,
    Sub,
    Sup,
    I,
    B,
    U,
    Mark,
    Ruby,
    Rt,
    Rp,
    Bdi,
    Bdo,
    Span,
    Br,
    Wbr,
    Ins,
    Del,
    Image,
    Img,
    Iframe,
    Embed,
    Object,
    Param,
    Video,
    Audio,
    Source,
    Track,
    Canvas,
    Map,
    Area,
    Math,
    Mi,
    Mo,
    Mn,
    Ms,
    Mtext,
    Mglyph,
    Malignmark,
    Annotation_xml,
    Svg,
    Foreignobject,
    Desc,
    Table,
    Caption,
    Colgroup,
    Col,
    Tbody,
    Thead,
    Tfoot,
    Tr,
    Td,
    Th,
    Form,
    Fieldset,
    Legend,
    Label,
    Input,
    Button,
    Select,
    Datalist,
    Optgroup,
    Option,
    Textarea,
    Keygen,
    Output,
    Progress,
    Meter,
    Details,
    Summary,
    Menu,
    Menuitem,
    Applet,
    Acronym,
    Bgsound,
    Dir,
    Frame,
    Frameset,
    Noframes,
    Isindex,
    Listing,
    Xmp,
    Nextid,
    Noembed,
    Plaintext,
    Rb,
    Strike,
    Basefont,
    Big,
    Blink,
    Center,
    Font,
    Marquee,
    Multicol,
    Nobr,
    Spacer,
    Tt,
    Rtc,
    Unknown,
    Last
};

enum class attribute_namespace
{
    None,
    XLink,
    XML,
    XMLNS,
};

enum class node_type
{
    Element,
    Text,
    CDATA,
    Comment,
    Whitespace,
    Template,
};

enum class element_type
{
    Element,
    Template
};

enum class text_type
{
    Text,
    CDATA,
    Comment,
    Whitespace
};

enum class doctype_quirks_mode
{
    NoQuirks,
    Quirks,
    LimitedQuicks,
};

enum class web_namespace
{
    HTML,
    SVG,
    MATHML
};

namespace parse_flags {

enum flags : unsigned int
{
    InsertionNormal = 0,
    InsertionByParser = 1 << 0,
    InsertionImplicitEndTag = 1 << 1,
    InsertionImplied = 1 << 3,
    InsertionConvertedFromEndTag = 1 << 4,
    InsertionFromIsIndex = 1 << 5,
    InsertionFromImage = 1 << 6,
    InsertionReconstructedFormattingElement = 1 << 7,
    InsertionAdoptionAgencyCloned = 1 << 8,
    InsertionAdoptionAgencyMoved = 1 << 9,
    InsertionFosterParented = 1 << 10
};
} // namespace parse_flags

} // namespace beak::gumbo
