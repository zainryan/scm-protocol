add_executable(
    param_replicator_unit_tests
    param_replicator.cpp
    )

target_link_libraries(
    param_replicator_unit_tests
    gtest_main
    param_replicator
    )

add_test(
  NAME
    param_replicator_unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/param_replicator_unit_tests
  )

target_include_directories(
    param_replicator_unit_tests
    PUBLIC
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/test/inc/
    ${CMAKE_SOURCE_DIR}/third_party/hls/inc
    ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
)
