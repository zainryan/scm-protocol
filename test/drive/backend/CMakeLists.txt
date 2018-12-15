add_executable(
    backend_unit_tests
    throttle_unit.cpp
    )

target_link_libraries(
    backend_unit_tests
    gtest_main
    )

add_test(
  NAME
    backend_unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/backend_unit_tests
  )

target_include_directories(
    backend_unit_tests
    PUBLIC
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/src/drive/backend/
    ${CMAKE_SOURCE_DIR}/test/inc/
    ${CMAKE_SOURCE_DIR}/third_party/hls/inc
    ${CMAKE_SOURCE_DIR}/third_party/staccel/inc
)