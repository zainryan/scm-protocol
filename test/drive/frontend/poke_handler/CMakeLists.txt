add_executable(
    poke_handler_unit_tests
    poke_handler.cpp
    )

target_link_libraries(
    poke_handler_unit_tests
    gtest_main
    poke_handler
    )

add_test(
  NAME
    poke_handler_unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/poke_handler_unit_tests
  )

target_include_directories(
    poke_handler_unit_tests
    PUBLIC
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/test/inc/
    ${CMAKE_SOURCE_DIR}/third_party/hls/inc
    ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
)
