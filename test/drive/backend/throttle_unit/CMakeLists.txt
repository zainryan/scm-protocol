add_executable(
    throttle_unit_tests
    throttle_unit.cpp
    )

target_link_libraries(
    throttle_unit_tests
    gtest_main
    )

add_test(
  NAME
    throttle_unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/throttle_unit_tests
  )

target_include_directories(
    throttle_unit_tests
    PUBLIC
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/test/inc/
    ${CMAKE_SOURCE_DIR}/third_party/hls/inc
    ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
)
