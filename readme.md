# Gumbo - A HTML5 parser.
This provides C++ bindings for [Gumbo Parser](https://github.com/google/gumbo-parser).  
It also ports the build system to CMake and removes all extensions, tests, examples and samples.  

## License
The original can be found here: https://github.com/google/gumbo-parser.  
The original source is licensed under the [Apache License 2.0](https://github.com/google/gumbo-parser/blob/master/COPYING).  
This modified version is licensed under the [MIT license](https://github.com/Barath-Kannan/gumbo/blob/master/license).  
All original code remains licensed under the Apache License 2.0.  
The original copyright notice [(COPYING)](https://github.com/Barath-Kannan/gumbo/blob/master/gumbo/src/original/COPYING) and acknowledgments [(THANKS)](https://github.com/Barath-Kannan/gumbo/blob/master/gumbo/src/original/THANKS) can be found in the [gumbo/src/original](https://github.com/Barath-Kannan/gumbo/tree/master/gumbo/src/original) directory.

## TODO
- Add allocator support
- Make text an optionally populated unique ptr in the node instead of a variant
- Fix xml/json conversion issues related to text and element being separate tree nodes
- Add stream operators for enums and structures
- Separate node types into element and text type enums and remove the document type enum
