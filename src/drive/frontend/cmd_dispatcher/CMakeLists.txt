add_library(cmd_dispatcher "")

target_sources(cmd_dispatcher
    PRIVATE
        cmd_dispatcher.cpp
)

target_include_directories(cmd_dispatcher
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
)
