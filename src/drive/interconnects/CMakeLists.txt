add_library(place_holder "")

target_sources(place_holder
    PRIVATE
        place_holder.cpp
    )

target_include_directories(place_holder
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )

add_library(interconnects "")

target_sources(interconnects
    PRIVATE
        interconnects.cpp
    )

target_include_directories(interconnects
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/third_party/hls/inc
        ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
    )