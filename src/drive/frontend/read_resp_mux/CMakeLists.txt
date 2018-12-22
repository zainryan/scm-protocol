add_library(read_resp_mux "")

target_sources(read_resp_mux
    PRIVATE
        read_resp_mux.cpp
)

target_include_directories(read_resp_mux
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
)

