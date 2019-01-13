add_library(cmd_intrpr "")

target_sources(cmd_intrpr
    PRIVATE
        cmd_intrpr.cpp
)

target_include_directories(cmd_intrpr
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
)
