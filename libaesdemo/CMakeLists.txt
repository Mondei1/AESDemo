add_library(libaesdemo libaesdemo/Crypto.cpp libaesdemo/Crypto.hpp libaesdemo/Utils.cpp libaesdemo/Utils.hpp libaesdemo/Base64.cpp libaesdemo/Base64.hpp)
add_library(aesdemo::libaesdemo ALIAS libaesdemo)

add_subdirectory(tinyAES)

target_include_directories(libaesdemo PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
target_link_libraries(libaesdemo PUBLIC PkgConfig::gtkmm tiny-aes)
target_compile_features(libaesdemo PUBLIC cxx_std_17)

target_sources(libaesdemo PRIVATE
    # Sources here
    libaesdemo/MainWindow.cpp
    libaesdemo/Crypto.cpp
)

#if(AESDEMO_ENABLE_TESTING)
#    add_executable(libaesdemo_test)
#    target_link_libraries(libaesdemo_test PRIVATE aesdemo::libaesdemo gtest_main)
#
#    target_sources(libaesdemo_test PRIVATE
#        libaesdemo/hello.test.cpp)

#    include(GoogleTest)
#    gtest_discover_tests(libaesdemo_test)
#endif()