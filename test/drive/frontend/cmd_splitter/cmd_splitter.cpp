#include <cstdlib>
#include <vector>

#include "cmd.h"
#include "cmd_splitter.hpp"
#include "gtest/gtest.h"
#include "staccel_type.h"
#include "test_params.hpp"
#include "test_utils.hpp"

TEST(test_cmd_splitter, correct_split) {
  std::vector<Command> expected;
  std::vector<Command> real;

  SuperCommand super_command;
  Command command;

  for (int i = 0; i < NUM_OF_COMMAND; i++) {
    command = RandomGen::rand_command();
    expected.push_back(command);

    long long command_content = 0;
    command_content |= command.index;
    command_content <<= COMMAND_NUM_SIZE_IN_BIT;
    command_content |= command.num;
    command_content <<= COMMAND_ISREAD_SIZE_IN_BIT;
    command_content |= command.is_read;

    super_command.data <<= COMMAND_SIZE_IN_BIT;
    super_command.data |= ((ap_uint<COMMAND_SIZE_IN_BIT>)command_content);
  }

  ST_Queue<SuperCommand> super_command_queue(8);
  ST_Queue<Command> command_queue(32);

  // put super-command to super command queue
  ASSERT_EQ(super_command_queue.write_nb(super_command), true);

  RUN_METHOD(1, cmd_splitter_impl(&super_command_queue, &command_queue));

  // read command from the command queue
  drain_queue(&command_queue, &real);

  ASSERT_EQ(real.size(), expected.size());

  for (int i = 0; i < real.size(); i++) {
    EXPECT_EQ(expected[NUM_OF_COMMAND - i - 1], real[i]);
  }
}
