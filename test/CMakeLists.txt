add_executable(
    unit_tests
    example_add.cpp
    example_subtract.cpp
    tonghe_cal_test.cpp
    )

target_link_libraries(
    unit_tests
    gtest_main
    example
    tonghe_cal
    )

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )
