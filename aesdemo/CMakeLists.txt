set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../build")

# GResources
find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)
set(GRESOURCE_C   aesdemo.gresource.c)
set(GRESOURCE_XML img/aesdemo.gresource.xml)

add_custom_command(
        OUTPUT ${GRESOURCE_C}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ${GLIB_COMPILE_RESOURCES}
        ARGS
            --target=${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
            --generate
            ${GRESOURCE_XML}
        VERBATIM
        MAIN_DEPENDENCY ${GRESOURCE_XML}
        DEPENDS
            img/icon.png
)
add_custom_target(
        dummy-resource
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
)

add_executable(AESDemo ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C})
set_source_files_properties(
        ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
        PROPERTIES GENERATED TRUE
)

# Step 5:
add_dependencies(AESDemo dummy-resource)

target_include_directories(AESDemo PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
target_link_libraries(AESDemo PRIVATE aesdemo::libaesdemo)

target_sources(AESDemo PRIVATE
    # Sources here
    aesdemo/main.cpp)