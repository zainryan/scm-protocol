add_library(delay_unit_0 "")

target_sources(delay_unit_0
    PRIVATE
        delay_unit_0.cpp
    )

target_include_directories(delay_unit_0
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )

add_library(delay_unit_1 "")

target_sources(delay_unit_1
    PRIVATE
        delay_unit_1.cpp
    )

target_include_directories(delay_unit_1
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )

add_library(delay_unit_2 "")

target_sources(delay_unit_2
    PRIVATE
        delay_unit_2.cpp
    )

target_include_directories(delay_unit_2
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )

add_library(delay_unit_3 "")

target_sources(delay_unit_3
    PRIVATE
        delay_unit_3.cpp
    )

target_include_directories(delay_unit_3
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )