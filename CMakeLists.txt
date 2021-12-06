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
pkg_check_modules(gtkmm REQUIRED IMPORTED_TARGET gtkmm-4.0 libcryptopp)

include(FetchContent)


#if(AESDEMO_ENABLE_TESTING)
#    include(FetchContent)
#    FetchContent_Declare(googletest
#        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip)
#    FetchContent_MakeAvailable(googletest)
#    enable_testing()
#endif()

add_subdirectory(libaesdemo)
add_subdirectory(aesdemo)