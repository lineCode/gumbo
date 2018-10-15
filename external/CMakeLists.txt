include(FetchContent)

if (NOT beak_clone_dir)
    set(beak_clone_dir ${CMAKE_CURRENT_SOURCE_DIR})
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
