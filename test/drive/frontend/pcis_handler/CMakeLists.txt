add_executable(
    pcis_handler_unit_tests
    pcis_handler.cpp
    )

target_link_libraries(
    pcis_handler_unit_tests
    gtest_main
    pcis_handler
    )

add_test(
  NAME
    pcis_handler_unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/pcis_handler_unit_tests
  )

target_include_directories(
    pcis_handler_unit_tests
    PUBLIC
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/test/inc/
    ${CMAKE_SOURCE_DIR}/third_party/hls/inc
    ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
)
