add_library(time_marker_0 "")

target_sources(time_marker_0
    PRIVATE
        time_marker_0.cpp
    )

target_include_directories(time_marker_0
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )

add_library(time_marker_1 "")

target_sources(time_marker_1
    PRIVATE
        time_marker_1.cpp
    )

target_include_directories(time_marker_1
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )

add_library(time_marker_2 "")

target_sources(time_marker_2
    PRIVATE
        time_marker_2.cpp
    )

target_include_directories(time_marker_2
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )

add_library(time_marker_3 "")

target_sources(time_marker_3
    PRIVATE
        time_marker_3.cpp
    )

target_include_directories(time_marker_3
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )