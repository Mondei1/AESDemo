cmake_minimum_required(VERSION 3.12)

project(tiny-aes C)

add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/aes.c
        ${CMAKE_CURRENT_LIST_DIR}/pkcs7_padding.c
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/aes.h
        ${CMAKE_CURRENT_LIST_DIR}/aes.hpp
        ${CMAKE_CURRENT_LIST_DIR}/pkcs7_padding.h
)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
)
