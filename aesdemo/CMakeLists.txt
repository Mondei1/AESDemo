set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../build")

add_executable(AESDemo)

target_include_directories(AESDemo PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
target_link_libraries(AESDemo PRIVATE aesdemo::libaesdemo)

target_sources(AESDemo PRIVATE
    # Sources here
    aesdemo/main.cpp)