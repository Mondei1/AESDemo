cmake_minimum_required(VERSION 3.16)

project(aesdemo
    VERSION 1.0.0
    LANGUAGES CXX)

# option(AESDEMO_ENABLE_TESTING "Build unit tests" ON)
option(AESDEMO_ENABLE_IN_SOURCE_BUILDS "Explicitly allow in-source builds." OFF)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR AND NOT AESDEMO_ENABLE_IN_SOURCE_BUILDS)
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.\n")
endif()

include(FetchContent)
FetchContent_Declare(DEP_TINYAES
        GIT_REPOSITORY https://github.com/kokke/tiny-AES-c.git
        GIT_TAG 12e7744b4919e9d55de75b7ab566326a1c8e7a67)

FetchContent_GetProperties(DEP_TINYAES)
if(NOT DEP_TINYAES_POPULATED)
    FetchContent_Populate(DEP_TINYAES)

    add_library(tinyAES)
    add_library(tinyAES::tinyAES ALIAS tinyAES)
    target_sources(tinyAES PRIVATE
            ${DEP_TINYAES_SOURCE_DIR}/aes.c)
    target_include_directories(tinyAES PUBLIC
            "$<BUILD_INTERFACE:${DEP_TINYAES_SOURCE_DIR}>")
endif()

# Fetch dependencies
find_package(PkgConfig)
# pkg_check_modules(libsodium REQUIRED IMPORTED_TARGET libsodium)
pkg_check_modules(gtkmm REQUIRED IMPORTED_TARGET gtkmm-4.0)

#if(AESDEMO_ENABLE_TESTING)
#    include(FetchContent)
#    FetchContent_Declare(googletest
#        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip)
#    FetchContent_MakeAvailable(googletest)
#    enable_testing()
#endif()

add_subdirectory(libaesdemo)
add_subdirectory(aesdemo)