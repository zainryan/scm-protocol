add_executable(
    peek_handler_unit_tests
    peek_handler.cpp
    )

target_link_libraries(
    peek_handler_unit_tests
    gtest_main
    peek_handler
    )

add_test(
  NAME
    peek_handler_unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/peek_handler_unit_tests
  )

target_include_directories(
    peek_handler_unit_tests
    PUBLIC
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/test/inc/
    ${CMAKE_SOURCE_DIR}/third_party/hls/inc
    ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
)
