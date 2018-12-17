add_executable(
    delay_unit_unit_tests
    delay_unit.cpp
    )

target_link_libraries(
    delay_unit_unit_tests
    gtest_main
    )

add_test(
  NAME
    delay_unit_unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/delay_unit_unit_tests
  )

target_include_directories(
    delay_unit_unit_tests
    PUBLIC
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/test/inc/
    ${CMAKE_SOURCE_DIR}/third_party/hls/inc
    ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
)
