#pragma once

namespace beak::gumbo {

enum class tag
{
    HTML,
    HEAD,
    TITLE,
    BASE,
    LINK,
    META,
    STYLE,
    SCRIPT,
    NOSCRIPT,
    TEMPLATE,
    BODY,
    ARTICLE,
    SECTION,
    NAV,
    ASIDE,
    H1,
    H2,
    H3,
    H4,
    H5,
    H6,
    HGROUP,
    HEADER,
    FOOTER,
    ADDRESS,
    P,
    HR,
    PRE,
    BLOCKQUOTE,
    OL,
    UL,
    LI,
    DL,
    DT,
    DD,
    FIGURE,
    FIGCAPTION,
    MAIN,
    DIV,
    A,
    EM,
    STRONG,
    SMALL,
    S,
    CITE,
    Q,
    DFN,
    ABBR,
    DATA,
    TIME,
    CODE,
    VAR,
    SAMP,
    KBD,
    SUB,
    SUP,
    I,
    B,
    U,
    MARK,
    RUBY,
    RT,
    RP,
    BDI,
    BDO,
    SPAN,
    BR,
    WBR,
    INS,
    DEL,
    IMAGE,
    IMG,
    IFRAME,
    EMBED,
    OBJECT,
    PARAM,
    VIDEO,
    AUDIO,
    SOURCE,
    TRACK,
    CANVAS,
    MAP,
    AREA,
    MATH,
    MI,
    MO,
    MN,
    MS,
    MTEXT,
    MGLYPH,
    MALIGNMARK,
    ANNOTATION_XML,
    SVG,
    FOREIGNOBJECT,
    DESC,
    TABLE,
    CAPTION,
    COLGROUP,
    COL,
    TBODY,
    THEAD,
    TFOOT,
    TR,
    TD,
    TH,
    FORM,
    FIELDSET,
    LEGEND,
    LABEL,
    INPUT,
    BUTTON,
    SELECT,
    DATALIST,
    OPTGROUP,
    OPTION,
    TEXTAREA,
    KEYGEN,
    OUTPUT,
    PROGRESS,
    METER,
    DETAILS,
    SUMMARY,
    MENU,
    MENUITEM,
    APPLET,
    ACRONYM,
    BGSOUND,
    DIR,
    FRAME,
    FRAMESET,
    NOFRAMES,
    ISINDEX,
    LISTING,
    XMP,
    NEXTID,
    NOEMBED,
    PLAINTEXT,
    RB,
    STRIKE,
    BASEFONT,
    BIG,
    BLINK,
    CENTER,
    FONT,
    MARQUEE,
    MULTICOL,
    NOBR,
    SPACER,
    TT,
    RTC,
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
