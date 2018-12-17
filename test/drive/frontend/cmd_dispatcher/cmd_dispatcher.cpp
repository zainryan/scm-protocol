#include <vector>

#include "cmd.h"
#include "cmd_dispatcher.hpp"
#include "gtest/gtest.h"
#include "staccel_type.h"
#include "test_params.hpp"
#include "test_utils.hpp"

#define TEST_NUM_OF_COMMAND 10
#define QUEUE_DEPTH 64

TEST(test_cmd_dispatcher, bank_0_dispatch) {

  ST_Queue<Command> command_queue(QUEUE_DEPTH);
  ST_Queue<Host_Write_Data> host_write_data_queue(QUEUE_DEPTH);

  ST_Queue<Chip_Read_Req> chip_read_req_queue_0(QUEUE_DEPTH);
  ST_Queue<Chip_Write_Req> chip_write_req_queue_0(QUEUE_DEPTH);
  ST_Queue<Chip_Read_Req> read_req_context_0(QUEUE_DEPTH);

  ST_Queue<Chip_Read_Req> chip_read_req_queue_1(QUEUE_DEPTH);
  ST_Queue<Chip_Write_Req> chip_write_req_queue_1(QUEUE_DEPTH);
  ST_Queue<Chip_Read_Req> read_req_context_1(QUEUE_DEPTH);

  ST_Queue<Chip_Read_Req> chip_read_req_queue_2(QUEUE_DEPTH);
  ST_Queue<Chip_Write_Req> chip_write_req_queue_2(QUEUE_DEPTH);
  ST_Queue<Chip_Read_Req> read_req_context_2(QUEUE_DEPTH);

  ST_Queue<Chip_Read_Req> chip_read_req_queue_3(QUEUE_DEPTH);
  ST_Queue<Chip_Write_Req> chip_write_req_queue_3(QUEUE_DEPTH);
  ST_Queue<Chip_Read_Req> read_req_context_3(QUEUE_DEPTH);

  std::vector<Command> expected;
  std::vector<Chip_Read_Req> real;

  // generate bank 0 command
  for (int i = 0; i < TEST_NUM_OF_COMMAND; i++) {
    Command command = RandomGen::rand_command(0, true);
    expected.push_back(command);
    command_queue.write(command);
  }

  RUN_METHOD(TEST_NUM_OF_COMMAND, cmd_dispatcher_impl( \
        &command_queue,             \
        &host_write_data_queue,     \

        &chip_read_req_queue_0,     \
        &read_req_context_0,        \
        &chip_write_req_queue_0,    \

        &chip_read_req_queue_1,     \
        &read_req_context_1,        \
        &chip_write_req_queue_1,    \

        &chip_read_req_queue_2,     \
        &read_req_context_2,        \
        &chip_write_req_queue_2,    \

        &chip_read_req_queue_3,     \
        &read_req_context_3,        \
        &chip_write_req_queue_3
        )   
      );

  drain_queue(&chip_read_req_queue_0, &real);

  ASSERT_EQ(expected.size(), real.size());
}

//TEST(test_cmd_dispatcher, hol_blocking) {

//}
