add_library(pcis_handler "")

target_sources(pcis_handler
    PRIVATE
        pcis_handler.cpp
    )

target_include_directories(pcis_handler
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )
