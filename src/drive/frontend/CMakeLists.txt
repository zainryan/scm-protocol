add_library(cmd_splitter "")

target_sources(cmd_splitter
    PRIVATE
        cmd_splitter.cpp
    )

target_include_directories(cmd_splitter
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )
