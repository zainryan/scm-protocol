add_library(example "")

target_sources(
    example
    PRIVATE
        example.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/example.h
    )

target_include_directories(
    example
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )

# tonghe_cal related commands
add_library(tonghe_cal "")

target_sources(
    tonghe_cal
    PRIVATE
        tonghe_cal.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/tonghe_cal.h
    )

target_include_directories(
    tonghe_cal
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )
