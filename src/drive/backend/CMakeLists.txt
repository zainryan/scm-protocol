add_library(throttle_unit_0 "")

target_sources(throttle_unit_0
    PRIVATE
        throttle_unit_0.cpp
    )

target_include_directories(throttle_unit_0
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )

add_library(throttle_unit_1 "")

target_sources(throttle_unit_1
    PRIVATE
        throttle_unit_1.cpp
    )

target_include_directories(throttle_unit_1
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )

add_library(throttle_unit_2 "")

target_sources(throttle_unit_2
    PRIVATE
        throttle_unit_2.cpp
    )

target_include_directories(throttle_unit_2
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )

add_library(throttle_unit_3 "")

target_sources(throttle_unit_3
    PRIVATE
        throttle_unit_3.cpp
    )

target_include_directories(throttle_unit_3
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )