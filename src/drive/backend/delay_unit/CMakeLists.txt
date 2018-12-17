add_library(delay_unit "")

target_sources(delay_unit
    PRIVATE
        delay_unit.cpp
    )

target_include_directories(delay_unit
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )