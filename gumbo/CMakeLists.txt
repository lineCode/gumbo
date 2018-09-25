################################################
# Project Settings
################################################
project(beak-gumbo C CXX)
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)

################################################
# Dependencies
################################################
find_package(Boost COMPONENTS system REQUIRED)

################################################
# Files
################################################
set(S src/original)
set(ORIGINAL_LIB_FILES
    ${S}/gumbo.h
    ${S}/attribute.h ${S}/attribute.c
    ${S}/char_ref.h ${S}/char_ref.c
    ${S}/error.h ${S}/error.c
    ${S}/insertion_mode.h
    ${S}/parser.h ${S}/parser.c
    ${S}/string_buffer.h ${S}/string_buffer.c
    ${S}/string_piece.h ${S}/string_piece.c
    ${S}/tag.c
    ${S}/tag_gperf.h
    ${S}/tag_sizes.h
    ${S}/tag_strings.h
    ${S}/tokenizer.h ${S}/tokenizer.c
    ${S}/tokenizer_states.h
    ${S}/token_type.h
    ${S}/utf8.h ${S}/utf8.c
    ${S}/util.h ${S}/util.c
    ${S}/vector.h ${S}/vector.c
)

set(H include/gumbo)
set(S src)
set(LIB_FILES
    ${H}/enums.hpp
    ${H}/gumbo.hpp ${S}/gumbo.cpp
)

################################################
# Targets
################################################
add_library(libbeak-cgumbo
    ${ORIGINAL_LIB_FILES}
)
target_include_directories(libbeak-cgumbo
    PRIVATE src/original
)

add_library(libbeak-gumbo
    ${LIB_FILES}
)
target_include_directories(libbeak-gumbo
    PUBLIC include
    PRIVATE src
)
target_link_libraries(libbeak-gumbo
    libbeak-cgumbo
    Boost::system
)
set_property(TARGET libbeak-gumbo
    PROPERTY CXX_STANDARD 17)

add_executable(gumbo_test
    ${S}/main.cpp
)

target_link_libraries(gumbo_test
    libbeak-gumbo
)
