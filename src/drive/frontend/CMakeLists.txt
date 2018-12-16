add_library(cmd_splitter "")

target_sources(cmd_splitter
    PRIVATE
        cmd_splitter.cpp
    )

target_include_directories(cmd_splitter
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )

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

add_library(poke_handler "")

target_sources(poke_handler
    PRIVATE
        poke_handler.cpp
    )

target_include_directories(poke_handler
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )