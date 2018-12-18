add_library(param_replicator "")

target_sources(param_replicator
    PRIVATE
        param_replicator.cpp
    )

target_include_directories(param_replicator
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )
