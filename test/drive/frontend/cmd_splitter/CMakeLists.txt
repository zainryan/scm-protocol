add_executable(
    cmd_splitter_unit_tests
    cmd_splitter.cpp
    )

target_link_libraries(
    cmd_splitter_unit_tests
    gtest_main
    cmd_splitter
    )

add_test(
  NAME
    cmd_splitter_unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/cmd_splitter_unit_tests
  )

target_include_directories(
    cmd_splitter_unit_tests
    PUBLIC
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/test/inc/
    ${CMAKE_SOURCE_DIR}/third_party/hls/inc
    ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
)
