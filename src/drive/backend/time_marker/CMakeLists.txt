add_library(time_marker "")

target_sources(time_marker
    PRIVATE
        time_marker.cpp
    )

target_include_directories(time_marker
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )