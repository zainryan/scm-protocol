#include <cstdlib>
#include <vector>

#include "cmd.h"
#include "cmd_intrpr.hpp"
#include "gtest/gtest.h"
#include "staccel_type.h"
#include "test_params.hpp"
#include "test_utils.hpp"

#define TEST_NUM_OF_COMMANDS 10
#define COMMAND_NUM_LIMIT 10
#define QUEUE_DEPTH \
  120  // must less than TEST_NUM_OF_COMMANDS * COMMAND_NUM_LIMIT
#define INVOKE_CMD_INTRPR_IMPL(context)                                 \
  cmd_intrpr_impl(context.command_queue.get(),                          \
                  context.unit_command_queue.get(), &(context.command), \
                  &(context.unit_command), &(context.num_of_command_left))

struct CmdIntrprTestContext {
  std::unique_ptr<ST_Queue<Command>> command_queue;
  std::unique_ptr<ST_Queue<Unit_Command>> unit_command_queue;
  Command command;
  Unit_Command unit_command;
  unsigned int num_of_command_left;

  CmdIntrprTestContext() {
    command_queue.reset(new ST_Queue<Command>(QUEUE_DEPTH));
    unit_command_queue.reset(new ST_Queue<Unit_Command>(QUEUE_DEPTH));
    num_of_command_left = 0;
  }
};

TEST(test_cmd_intrpr, unit_command_pass_through) {
  std::vector<Command> input_commands;
  std::vector<Unit_Command> output_unit_commands;

  CmdIntrprTestContext context;

  for (int i = 0; i < NUM_OF_COMMAND; i++) {
    Command command = RandomGen::rand_command(1);
    input_commands.push_back(command);
    context.command_queue->write(command);
  }

  RUN_METHOD(NUM_OF_COMMAND, INVOKE_CMD_INTRPR_IMPL(context));
  drain_queue(context.unit_command_queue.get(), &output_unit_commands);
  ASSERT_EQ(input_commands.size(), output_unit_commands.size());

  for (int i = 0; i < input_commands.size(); i++) {
    EXPECT_EQ(input_commands[i], output_unit_commands[i]);
  }
}

TEST(test_cmd_intrpr, command_intrpr) {
  std::vector<Command> input_commands;
  std::vector<Unit_Command> output_unit_commands;

  CmdIntrprTestContext context;

  unsigned int expected_unit_command_num = 0;
  for (int i = 0; i < NUM_OF_COMMAND; i++) {
    unsigned int command_num = std::max(rand() % COMMAND_NUM_LIMIT, 1);
    Command command = RandomGen::rand_command(command_num);
    expected_unit_command_num += command_num;
    input_commands.push_back(command);
    context.command_queue->write(command);
  }

  RUN_METHOD(2 * expected_unit_command_num, INVOKE_CMD_INTRPR_IMPL(context));
  drain_queue(context.unit_command_queue.get(), &output_unit_commands);
  ASSERT_EQ(expected_unit_command_num, output_unit_commands.size());

  for (int i = 0, base = 0; i < input_commands.size(); i++) {
    for (int j = 0; j < input_commands[i].num; j++) {
      EXPECT_EQ(input_commands[i].index + j,
                output_unit_commands[base + j].index);
      EXPECT_EQ(input_commands[i].is_read,
                output_unit_commands[base + j].is_read);
    }
    base += input_commands[i].num;
  }
}
