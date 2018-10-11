include(FetchContent)

if (EXISTS ${CMAKE_SOURCE_DIR}/external) 
    set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external)
elseif (EXISTS ${CMAKE_SOURCE_DIR}/extern)
    set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/extern)
elseif (EXISTS ${CMAKE_SOURCE_DIR}/3rdParty)
    set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/3rdParty)
else()
    set(EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR})
endif()

FetchContent_Declare(
    beak-util
    SOURCE_DIR ${EXTERNAL_DIR}/beak-util
    GIT_REPOSITORY git@github.com:Barath-Kannan/util.git 
    GIT_TAG master 
)

FetchContent_GetProperties(beak-util)
if (NOT beak-util_POPULATED)
    FetchContent_Populate(beak-util)
    add_subdirectory(${beak-util_SOURCE_DIR} ${beak-util_BINARY_DIR})
endif()
