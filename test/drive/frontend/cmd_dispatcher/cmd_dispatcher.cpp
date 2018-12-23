#include <vector>

#include "cmd.h"
#include "cmd_dispatcher.hpp"
#include "gtest/gtest.h"
#include "staccel_type.h"
#include "test_params.hpp"
#include "test_utils.hpp"

#define TEST_NUM_OF_COMMANDS 10
#define QUEUE_DEPTH 64
#define INVOKE_CMD_DISPATCHER_IMPL(context)                   \
  cmd_dispatcher_impl(context.unit_command_queue.get(),       \
                      context.host_write_data_queue.get(),    \
                      context.chip_read_req_queue[0].get(),   \
                      context.chip_read_req_context[0].get(), \
                      context.chip_write_req_queue[0].get(),  \
                      context.chip_read_req_queue[1].get(),   \
                      context.chip_read_req_context[1].get(), \
                      context.chip_write_req_queue[1].get(),  \
                      context.chip_read_req_queue[2].get(),   \
                      context.chip_read_req_context[2].get(), \
                      context.chip_write_req_queue[2].get(),  \
                      context.chip_read_req_queue[3].get(),   \
                      context.chip_read_req_context[3].get(), \
                      context.chip_write_req_queue[3].get())

struct cmd_dispatcher_context {
  std::unique_ptr<ST_Queue<Unit_Command>> unit_command_queue;
  std::unique_ptr<ST_Queue<Host_Write_Data>> host_write_data_queue;

  std::vector<std::unique_ptr<ST_Queue<Chip_Read_Req>>> chip_read_req_queue;
  std::vector<std::unique_ptr<ST_Queue<Chip_Write_Req>>> chip_write_req_queue;
  std::vector<std::unique_ptr<ST_Queue<Chip_Read_Req>>> chip_read_req_context;

  cmd_dispatcher_context() {
    chip_read_req_queue.resize(NUM_OF_CHIP_BANKS);
    chip_write_req_queue.resize(NUM_OF_CHIP_BANKS);
    chip_read_req_context.resize(NUM_OF_CHIP_BANKS);

    unit_command_queue.reset(
        new ST_Queue<Unit_Command>(NUM_OF_CHIP_BANKS * QUEUE_DEPTH));
    host_write_data_queue.reset(
        new ST_Queue<Host_Write_Data>(NUM_OF_CHIP_BANKS * QUEUE_DEPTH));

    for (int i = 0; i < NUM_OF_CHIP_BANKS; i++) {
      chip_read_req_queue[i].reset(new ST_Queue<Chip_Read_Req>(QUEUE_DEPTH));
      chip_read_req_context[i].reset(new ST_Queue<Chip_Read_Req>(QUEUE_DEPTH));
      chip_write_req_queue[i].reset(new ST_Queue<Chip_Write_Req>(QUEUE_DEPTH));
    }
  }
};

TEST(test_cmd_dispatcher, bank_0_dispatch) {
  std::vector<Unit_Command> input_unit_commands;
  std::vector<Chip_Read_Req> output_reqs;
  std::vector<Chip_Read_Req> output_contexts;

  cmd_dispatcher_context context;

  // generate bank 0 command
  for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
    Unit_Command command =
        RandomGen::rand_unit_command(0 /*bank_id*/, true /*is_read*/);
    input_unit_commands.push_back(command);
    context.unit_command_queue->write(command);
  }

  RUN_METHOD(TEST_NUM_OF_COMMANDS, INVOKE_CMD_DISPATCHER_IMPL(context));
  drain_queue(context.chip_read_req_queue[0].get(), &output_reqs);
  drain_queue(context.chip_read_req_context[0].get(), &output_contexts);
  ASSERT_EQ(input_unit_commands.size(), output_reqs.size());
  ASSERT_EQ(input_unit_commands.size(), output_contexts.size());

  for (int i = 0; i < input_unit_commands.size(); i++) {
    EXPECT_EQ((unsigned long long)input_unit_commands[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_reqs[i].addr);
  }
  for (int i = 0; i < input_unit_commands.size(); i++) {
    EXPECT_EQ((unsigned long long)input_unit_commands[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_contexts[i].addr);
  }
}

TEST(test_cmd_dispatcher, bank_1_dispatch) {
  std::vector<Unit_Command> input_unit_commands;
  std::vector<Chip_Read_Req> output_reqs;
  std::vector<Chip_Read_Req> output_contexts;

  cmd_dispatcher_context context;

  // generate bank 1 command
  for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
    Unit_Command command = RandomGen::rand_unit_command(1, true);
    input_unit_commands.push_back(command);
    context.unit_command_queue->write(command);
  }

  RUN_METHOD(TEST_NUM_OF_COMMANDS, INVOKE_CMD_DISPATCHER_IMPL(context));

  drain_queue(context.chip_read_req_queue[1].get(), &output_reqs);
  drain_queue(context.chip_read_req_context[1].get(), &output_contexts);

  ASSERT_EQ(input_unit_commands.size(), output_reqs.size());
  ASSERT_EQ(input_unit_commands.size(), output_contexts.size());

  for (int i = 0; i < input_unit_commands.size(); i++) {
    EXPECT_EQ((unsigned long long)input_unit_commands[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_reqs[i].addr);
  }
  for (int i = 0; i < input_unit_commands.size(); i++) {
    EXPECT_EQ((unsigned long long)input_unit_commands[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_reqs[i].addr);
  }
}

TEST(test_cmd_dispatcher, bank_2_dispatch) {
  std::vector<Unit_Command> input_unit_commands;
  std::vector<Chip_Read_Req> output_reqs;
  std::vector<Chip_Read_Req> output_contexts;
  cmd_dispatcher_context context;

  // generate bank 2 command
  for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
    Unit_Command command = RandomGen::rand_unit_command(2, true);
    input_unit_commands.push_back(command);
    context.unit_command_queue->write(command);
  }

  RUN_METHOD(TEST_NUM_OF_COMMANDS, INVOKE_CMD_DISPATCHER_IMPL(context));

  drain_queue(context.chip_read_req_queue[2].get(), &output_reqs);
  drain_queue(context.chip_read_req_context[2].get(), &output_contexts);

  ASSERT_EQ(input_unit_commands.size(), output_reqs.size());
  ASSERT_EQ(input_unit_commands.size(), output_contexts.size());

  for (int i = 0; i < input_unit_commands.size(); i++) {
    EXPECT_EQ((unsigned long long)input_unit_commands[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_reqs[i].addr);
  }
  for (int i = 0; i < input_unit_commands.size(); i++) {
    EXPECT_EQ((unsigned long long)input_unit_commands[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_reqs[i].addr);
  }
}

TEST(test_cmd_dispatcher, bank_3_dispatch) {
  std::vector<Unit_Command> input_unit_commands;
  std::vector<Chip_Read_Req> output_reqs;
  std::vector<Chip_Read_Req> output_contexts;
  cmd_dispatcher_context context;

  // generate bank 3 command
  for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
    Unit_Command command = RandomGen::rand_unit_command(3, true);
    input_unit_commands.push_back(command);
    context.unit_command_queue->write(command);
  }

  RUN_METHOD(TEST_NUM_OF_COMMANDS, INVOKE_CMD_DISPATCHER_IMPL(context));

  drain_queue(context.chip_read_req_queue[3].get(), &output_reqs);
  drain_queue(context.chip_read_req_context[3].get(), &output_contexts);

  ASSERT_EQ(input_unit_commands.size(), output_reqs.size());
  ASSERT_EQ(input_unit_commands.size(), output_contexts.size());

  for (int i = 0; i < input_unit_commands.size(); i++) {
    EXPECT_EQ((unsigned long long)input_unit_commands[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_reqs[i].addr);
  }
  for (int i = 0; i < input_unit_commands.size(); i++) {
    EXPECT_EQ((unsigned long long)input_unit_commands[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_reqs[i].addr);
  }
}

TEST(test_cmd_dispatcher, all_bank_dispatch_random) {
  std::vector<std::vector<Unit_Command>> input_unit_commands(NUM_OF_CHIP_BANKS);
  std::vector<std::vector<Chip_Read_Req>> output_reqs(NUM_OF_CHIP_BANKS);
  std::vector<std::vector<Chip_Read_Req>> output_contexts(NUM_OF_CHIP_BANKS);

  cmd_dispatcher_context context;

  for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
    Unit_Command unit_command = RandomGen::rand_read_unit_command();
    unsigned char bank_id =
        (unsigned char)unit_command.index & (NUM_OF_CHIP_BANKS - 1);

    input_unit_commands[bank_id].push_back(unit_command);

    context.unit_command_queue->write(unit_command);
  }

  RUN_METHOD(TEST_NUM_OF_COMMANDS, INVOKE_CMD_DISPATCHER_IMPL(context));

  for (int i = 0; i < NUM_OF_CHIP_BANKS; i++) {
    drain_queue(context.chip_read_req_queue[i].get(), &output_reqs[i]);
    drain_queue(context.chip_read_req_context[i].get(), &output_contexts[i]);
    ASSERT_EQ(input_unit_commands[i].size(), output_reqs[i].size());
    ASSERT_EQ(input_unit_commands[i].size(), output_contexts[i].size());
  }

  for (int bank_id = 0; bank_id < NUM_OF_CHIP_BANKS; bank_id++) {
    for (int i = 0; i < input_unit_commands[bank_id].size(); i++) {
      EXPECT_EQ((unsigned long long)input_unit_commands[bank_id][i].index *
                    UNIT_CHUCK_SIZE_IN_BYTE,
                output_reqs[bank_id][i].addr);
      EXPECT_EQ((unsigned long long)input_unit_commands[bank_id][i].index *
                    UNIT_CHUCK_SIZE_IN_BYTE,
                output_contexts[bank_id][i].addr);
    }
  }
}

TEST(test_cmd_dispatcher, all_bank_dispatch_interleave) {
  // generate & input `unit_command` in round robin manner

  std::vector<std::vector<Unit_Command>> input_unit_commands(NUM_OF_CHIP_BANKS);
  std::vector<std::vector<Chip_Read_Req>> output_reqs(NUM_OF_CHIP_BANKS);
  std::vector<std::vector<Chip_Read_Req>> output_contexts(NUM_OF_CHIP_BANKS);

  cmd_dispatcher_context context;

  for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
    for (int bank_id = 0; bank_id < NUM_OF_CHIP_BANKS; bank_id++) {
      Unit_Command unit_command =
          RandomGen::rand_unit_command(bank_id /*bank_id*/, true /*is_read*/);
      input_unit_commands[bank_id].push_back(unit_command);
      context.unit_command_queue->write(unit_command);
    }
  }

  RUN_METHOD(NUM_OF_CHIP_BANKS * TEST_NUM_OF_COMMANDS,
             INVOKE_CMD_DISPATCHER_IMPL(context));

  for (int i = 0; i < NUM_OF_CHIP_BANKS; i++) {
    drain_queue(context.chip_read_req_queue[i].get(), &output_reqs[i]);
    drain_queue(context.chip_read_req_context[i].get(), &output_contexts[i]);
    ASSERT_EQ(input_unit_commands[i].size(), output_reqs[i].size());
    ASSERT_EQ(input_unit_commands[i].size(), output_contexts[i].size());
  }

  for (int bank_id; bank_id < NUM_OF_CHIP_BANKS; bank_id++) {
    for (int i = 0; i < input_unit_commands[bank_id].size(); i++) {
      EXPECT_EQ((unsigned long long)input_unit_commands[bank_id][i].index *
                    UNIT_CHUCK_SIZE_IN_BYTE,
                output_reqs[bank_id][i].addr);
      EXPECT_EQ((unsigned long long)input_unit_commands[bank_id][i].index *
                    UNIT_CHUCK_SIZE_IN_BYTE,
                output_contexts[bank_id][i].addr);
    }
  }
}
