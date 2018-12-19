add_library(read_resp_collector "")

target_sources(read_resp_collector
    PRIVATE
        read_resp_collector.cpp
    )

target_include_directories(read_resp_collector
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )
