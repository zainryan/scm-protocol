add_executable(
    time_marker_unit_tests
    time_marker.cpp
    )

target_link_libraries(
    time_marker_unit_tests
    gtest_main
    )

add_test(
  NAME
    time_marker_unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/time_marker_unit_tests
  )

target_include_directories(
    time_marker_unit_tests
    PUBLIC
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/test/inc/
    ${CMAKE_SOURCE_DIR}/third_party/hls/inc
    ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
)
