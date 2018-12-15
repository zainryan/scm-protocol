#include <cstdlib>

#include "gtest/gtest.h"
#include "pcis_handler.hpp"
#include "test_params.hpp"
#include "test_utils.hpp"

TEST(pcis_handler_impl, correct) {
  ST_Queue<PCIS_Write_Req> pcis_write_req_queue(16);
  ST_Queue<SuperCommand> super_command_queue(16);

  PCIS_Write_Req pcis_write_req;
  pcis_write_req.addr = rand();
  int int_size_in_bit = sizeof(int) * 8;
  for (int i = 0; i < PCIS_BUS_WIDTH; i += int_size_in_bit) {
    pcis_write_req.data(i + int_size_in_bit - 1, i) = rand();
  }
  pcis_write_req_queue.write(pcis_write_req);

  RUN_METHOD(1, pcis_handler_impl(&pcis_write_req_queue, &super_command_queue));

  std::vector<SuperCommand> real_super_commands;
  drain_queue(&super_command_queue, &real_super_commands);

  ASSERT_EQ(real_super_commands.size(), 1);
  EXPECT_EQ(real_super_commands[0].data, pcis_write_req.data);
}
