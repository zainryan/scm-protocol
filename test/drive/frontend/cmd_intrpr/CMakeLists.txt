add_executable(
    cmd_intrpr_unit_tests
    cmd_intrpr.cpp
    )

target_link_libraries(
    cmd_intrpr_unit_tests
    gtest_main
    cmd_intrpr
    )

add_test(
  NAME
    cmd_intrpr_unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/cmd_intrpr_unit_tests
  )

target_include_directories(
    cmd_intrpr_unit_tests
    PUBLIC
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/test/inc/
    ${CMAKE_SOURCE_DIR}/third_party/hls/inc
    ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
)
