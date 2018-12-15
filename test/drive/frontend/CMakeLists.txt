add_executable(
    unit_tests
    cmd_splitter.cpp
    pcis_handler.cpp
    )

target_link_libraries(
    unit_tests
    gtest_main
    cmd_splitter
    pcis_handler
    )

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )

target_include_directories(
    unit_tests
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src/drive/frontend/
    ${CMAKE_SOURCE_DIR}/test/inc/
    ${CMAKE_SOURCE_DIR}/third_party
)
