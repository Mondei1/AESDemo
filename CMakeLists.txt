cmake_minimum_required(VERSION 3.16)

project(aesdemo
    VERSION 1.0.0
    LANGUAGES CXX C)

# option(AESDEMO_ENABLE_TESTING "Build unit tests" ON)
option(AESDEMO_ENABLE_IN_SOURCE_BUILDS "Explicitly allow in-source builds." OFF)
option(AESDEMO_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ON)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR AND NOT AESDEMO_ENABLE_IN_SOURCE_BUILDS)
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.\n")
endif()

# Fetch dependencies
find_package(PkgConfig)
# pkg_check_modules(libsodium REQUIRED IMPORTED_TARGET libsodium)
pkg_check_modules(gtkmm REQUIRED IMPORTED_TARGET gtkmm-4.0)

include(FetchContent)

FetchContent_Declare(tinyaes
        GIT_REPOSITORY https://github.com/kokke/tiny-AES-c.git
        GIT_TAG 12e7744b4919e9d55de75b7ab566326a1c8e7a67)
FetchContent_GetProperties(tinyaes)
if(NOT tinyaes_POPULATED)
    FetchContent_Populate(tinyaes)
    add_library(tinyAES)
    add_library(tinyAES::tinyAES ALIAS tinyAES)
    file(
        COPY
        ${tinyaes_SOURCE_DIR}/aes.h
        ${tinyaes_SOURCE_DIR}/aes.hpp
        DESTINATION ${tinyaes_SOURCE_DIR}/include/tinyaes
    )
    target_sources(tinyAES PRIVATE
        ${tinyaes_SOURCE_DIR}/aes.c)
    target_include_directories(tinyAES PRIVATE
        "$<BUILD_INTERFACE:${tinyaes_SOURCE_DIR}>")
    target_include_directories(tinyAES PUBLIC
        "$<BUILD_INTERFACE:${tinyaes_SOURCE_DIR}/include>")

    target_compile_options(tinyAES PUBLIC -fsanitize=address)
    target_link_options(tinyAES PUBLIC -fsanitize=address)
endif()

FetchContent_Declare(tinypkcs
        GIT_REPOSITORY https://github.com/bonybrown/tiny-AES128-C.git
        GIT_TAG 426bf026f2b852bb204626d200f28dcf5829e1fe)
FetchContent_GetProperties(tinypkcs)
if(NOT tinypkcs_POPULATED)
    FetchContent_Populate(tinypkcs)
    add_library(tinyPKCS)
    add_library(tinyPKCS::tinyPKCS ALIAS tinyPKCS)
    file(
            COPY
            ${tinypkcs_SOURCE_DIR}/pkcs7_padding.h
            DESTINATION ${tinypkcs_SOURCE_DIR}/include/tinypkcs
    )
    target_sources(tinyPKCS PRIVATE
            ${tinypkcs_SOURCE_DIR}/pkcs7_padding.c)
    target_include_directories(tinyPKCS PRIVATE
            "$<BUILD_INTERFACE:${tinypkcs_SOURCE_DIR}>")
    target_include_directories(tinyPKCS PUBLIC
            "$<BUILD_INTERFACE:${tinypkcs_SOURCE_DIR}/include>")

    target_compile_options(tinyPKCS PUBLIC -fsanitize=address)
    target_link_options(tinyPKCS PUBLIC -fsanitize=address)
endif()


#if(AESDEMO_ENABLE_TESTING)
#    include(FetchContent)
#    FetchContent_Declare(googletest
#        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip)
#    FetchContent_MakeAvailable(googletest)
#    enable_testing()
#endif()

add_subdirectory(libaesdemo)
add_subdirectory(aesdemo)