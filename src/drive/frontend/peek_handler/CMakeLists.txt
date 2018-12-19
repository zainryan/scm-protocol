add_library(peek_handler "")

target_sources(peek_handler
    PRIVATE
        peek_handler.cpp
    )

target_include_directories(peek_handler
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )
