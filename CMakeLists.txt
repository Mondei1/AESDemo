cmake_minimum_required(VERSION 3.16)

project(aesdemo
    VERSION 1.0.0
    LANGUAGES CXX)

# option(AESDEMO_ENABLE_TESTING "Build unit tests" ON)

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