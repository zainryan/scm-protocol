add_executable(
    frontend_unit_tests
    cmd_splitter.cpp
    pcis_handler.cpp
    poke_handler.cpp
    )

target_link_libraries(
    frontend_unit_tests
    gtest_main
    cmd_splitter
    pcis_handler
    poke_handler
    )

add_test(
  NAME
    frontend_unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/frontend_unit_tests
  )

target_include_directories(
    frontend_unit_tests
    PUBLIC
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/test/inc/
    ${CMAKE_SOURCE_DIR}/third_party/hls/inc
    ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
)
