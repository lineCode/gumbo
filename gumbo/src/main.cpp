#include <iostream>
#include <set>
#include <sstream>
#include <stack>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "gumbo/gumbo.hpp"

int main(int argc, const char* argv[])
{
    assert(argc > 1);

    std::string contents;
    {
        std::ifstream f(argv[1], std::ios::in | std::ios::binary);
        if (!f) {
            std::cout << "Failed to read " << argv[1] << "\n";
            return -1;
        }
        f.seekg(0, std::ios::end);
        contents.resize(f.tellg());
        f.seekg(0, std::ios::beg);
        f.read(&contents[0], contents.size());
        f.close();
    }
    beak::gumbo::parse_output p{contents};
    //beak::gumbo::parse_output p{"<html><head></head><body><h1><b>Hello, World!</b></h1></body></html>"};
    std::ostringstream ss;
    boost::property_tree::xml_writer_settings<std::string> s(' ', 4);
    boost::property_tree::xml_parser::write_xml(ss, p._tree, s);
    //boost::property_tree::json_parser::write_json(ss, p._tree);
    std::cout << ss.str() << "\n";
}
