#include "gtest/gtest.h"
#include "cmd.h"
#include "stdlib.h"
#include "staccel_type.h"
#include <thread>
#include <vector>
#include "cmd_splitter.hpp"

#define COMMAND_SIZE_IN_BIT 64
#define MAX_READ_TIMES  100000000L
#define NUM_OF_COMMAND 8

inline void command_eq(Command &expected, Command &real) {
  ASSERT_EQ(expected.index, real.index);
  ASSERT_EQ(expected.num, real.num);
  ASSERT_EQ(expected.is_read, real.is_read);
}


TEST(test_cmd_splitter, correct_split) {

  std::vector<Command> expected;
  std::vector<Command> real;

  SuperCommand super_command;
  Command command;

  for (int i = 0; i < NUM_OF_COMMAND; i ++) {
    int upper_half_command_index = rand();
    int lower_half_command_index = rand();
    int command_num = rand();
    bool command_is_read = (bool) (rand() % 2);
    command.index = 
      ap_uint<50> (((long long) upper_half_command_index) << 32 | lower_half_command_index);
    command.num = (ap_uint<13>) command_num; 
    command.is_read = command_is_read; 
    expected.push_back(command);

    long long command_content = 0;
    command_content |= command.index;
    command_content <<= 13;
    command_content |= command.num;
    command_content <<= 1;
    command_content |= command.is_read;

    super_command.data <<= 64; 
    super_command.data |= ((ap_uint<64>) command_content);
  }

  ST_Queue<SuperCommand> super_command_queue(8);
  ST_Queue<Command> command_queue(32); 
  
  // put super-command to super command queue
  ASSERT_EQ(super_command_queue.write_nb(super_command), true); 

  cmd_splitter_impl(super_command_queue, command_queue);

  // read command from the command queue
  int read_times = 0;
  while (real.size() != expected.size() && read_times < MAX_READ_TIMES) {
    Command command;
    if (command_queue.read_nb(command)) {
      real.push_back(command); 
    }
    read_times ++;
  }

  ASSERT_EQ(real.size(), expected.size());

  for (int i = 0; i < real.size(); i++) {
    command_eq(expected[7 - i], real[i]);
  }

}
