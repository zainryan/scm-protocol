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
