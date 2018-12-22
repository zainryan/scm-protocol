#include <vector>

#include "cmd.h"
#include "cmd_dispatcher.hpp"
#include "gtest/gtest.h"
#include "staccel_type.h"
#include "test_params.hpp"
#include "test_utils.hpp"

#define TEST_NUM_OF_COMMANDS 10
#define QUEUE_DEPTH 64
#define INVOKE_CMD_DISPATCHER_IMPL(context)                  \
  cmd_dispatcher_impl(context.unit_command_queue.get(),      \
                      context.host_write_data_queue.get(),   \
                      context.chip_read_req_queue_0.get(),   \
                      context.chip_read_req_context_0.get(), \
                      context.chip_write_req_queue_0.get(),  \
                      context.chip_read_req_queue_1.get(),   \
                      context.chip_read_req_context_1.get(), \
                      context.chip_write_req_queue_1.get(),  \
                      context.chip_read_req_queue_2.get(),   \
                      context.chip_read_req_context_2.get(), \
                      context.chip_write_req_queue_2.get(),  \
                      context.chip_read_req_queue_3.get(),   \
                      context.chip_read_req_context_3.get(), \
                      context.chip_write_req_queue_3.get())

struct cmd_dispatcher_context {
  std::unique_ptr<ST_Queue<Unit_Command>> unit_command_queue;
  std::unique_ptr<ST_Queue<Host_Write_Data>> host_write_data_queue;

  std::unique_ptr<ST_Queue<Chip_Read_Req>> chip_read_req_queue_0;
  std::unique_ptr<ST_Queue<Chip_Write_Req>> chip_write_req_queue_0;
  std::unique_ptr<ST_Queue<Chip_Read_Req>> chip_read_req_context_0;

  std::unique_ptr<ST_Queue<Chip_Read_Req>> chip_read_req_queue_1;
  std::unique_ptr<ST_Queue<Chip_Write_Req>> chip_write_req_queue_1;
  std::unique_ptr<ST_Queue<Chip_Read_Req>> chip_read_req_context_1;

  std::unique_ptr<ST_Queue<Chip_Read_Req>> chip_read_req_queue_2;
  std::unique_ptr<ST_Queue<Chip_Write_Req>> chip_write_req_queue_2;
  std::unique_ptr<ST_Queue<Chip_Read_Req>> chip_read_req_context_2;

  std::unique_ptr<ST_Queue<Chip_Read_Req>> chip_read_req_queue_3;
  std::unique_ptr<ST_Queue<Chip_Write_Req>> chip_write_req_queue_3;
  std::unique_ptr<ST_Queue<Chip_Read_Req>> chip_read_req_context_3;

  cmd_dispatcher_context() {
    unit_command_queue.reset(new ST_Queue<Unit_Command>(4 * QUEUE_DEPTH));
    host_write_data_queue.reset(new ST_Queue<Host_Write_Data>(4 * QUEUE_DEPTH));

    chip_read_req_queue_0.reset(new ST_Queue<Chip_Read_Req>(QUEUE_DEPTH));
    chip_read_req_context_0.reset(new ST_Queue<Chip_Read_Req>(QUEUE_DEPTH));
    chip_write_req_queue_0.reset(new ST_Queue<Chip_Write_Req>(QUEUE_DEPTH));

    chip_read_req_queue_1.reset(new ST_Queue<Chip_Read_Req>(QUEUE_DEPTH));
    chip_read_req_context_1.reset(new ST_Queue<Chip_Read_Req>(QUEUE_DEPTH));
    chip_write_req_queue_1.reset(new ST_Queue<Chip_Write_Req>(QUEUE_DEPTH));

    chip_read_req_queue_2.reset(new ST_Queue<Chip_Read_Req>(QUEUE_DEPTH));
    chip_read_req_context_2.reset(new ST_Queue<Chip_Read_Req>(QUEUE_DEPTH));
    chip_write_req_queue_2.reset(new ST_Queue<Chip_Write_Req>(QUEUE_DEPTH));

    chip_read_req_queue_3.reset(new ST_Queue<Chip_Read_Req>(QUEUE_DEPTH));
    chip_read_req_context_3.reset(new ST_Queue<Chip_Read_Req>(QUEUE_DEPTH));
    chip_write_req_queue_3.reset(new ST_Queue<Chip_Write_Req>(QUEUE_DEPTH));
  }
};

TEST(test_cmd_dispatcher, bank_0_dispatch) {
  std::vector<Unit_Command> input_unit_commands;
  std::vector<Chip_Read_Req> output_reqs;
  std::vector<Chip_Read_Req> output_contexts;

  cmd_dispatcher_context context;

  // generate bank 0 command
  for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
    Unit_Command command = RandomGen::rand_unit_command(0, true);
    input_unit_commands.push_back(command);
    context.unit_command_queue->write(command);
  }

  RUN_METHOD(TEST_NUM_OF_COMMANDS, INVOKE_CMD_DISPATCHER_IMPL(context));
  drain_queue(context.chip_read_req_queue_0.get(), &output_reqs);
  drain_queue(context.chip_read_req_context_0.get(), &output_contexts);
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

  drain_queue(context.chip_read_req_queue_1.get(), &output_reqs);
  drain_queue(context.chip_read_req_context_1.get(), &output_contexts);

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

  drain_queue(context.chip_read_req_queue_2.get(), &output_reqs);
  drain_queue(context.chip_read_req_context_2.get(), &output_contexts);

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

  drain_queue(context.chip_read_req_queue_3.get(), &output_reqs);
  drain_queue(context.chip_read_req_context_3.get(), &output_contexts);

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
  std::vector<Unit_Command> input_unit_commands_0;
  std::vector<Unit_Command> input_unit_commands_1;
  std::vector<Unit_Command> input_unit_commands_2;
  std::vector<Unit_Command> input_unit_commands_3;

  std::vector<Chip_Read_Req> output_reqs_0;
  std::vector<Chip_Read_Req> output_reqs_1;
  std::vector<Chip_Read_Req> output_reqs_2;
  std::vector<Chip_Read_Req> output_reqs_3;

  std::vector<Chip_Read_Req> output_contexts_0;
  std::vector<Chip_Read_Req> output_contexts_1;
  std::vector<Chip_Read_Req> output_contexts_2;
  std::vector<Chip_Read_Req> output_contexts_3;

  cmd_dispatcher_context context;

  for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
    Unit_Command unit_command = RandomGen::rand_read_unit_command();
    switch (((unsigned long long)unit_command.index) &
            (NUM_OF_CHIP_BANKS - 1)) {
      case 0:
        input_unit_commands_0.push_back(unit_command);
        break;
      case 1:
        input_unit_commands_1.push_back(unit_command);
        break;
      case 2:
        input_unit_commands_2.push_back(unit_command);
        break;
      case 3:
        input_unit_commands_3.push_back(unit_command);
        break;
    }
    context.unit_command_queue->write(unit_command);
  }

  RUN_METHOD(TEST_NUM_OF_COMMANDS, INVOKE_CMD_DISPATCHER_IMPL(context));

  drain_queue(context.chip_read_req_queue_0.get(), &output_reqs_0);
  drain_queue(context.chip_read_req_queue_1.get(), &output_reqs_1);
  drain_queue(context.chip_read_req_queue_2.get(), &output_reqs_2);
  drain_queue(context.chip_read_req_queue_3.get(), &output_reqs_3);

  drain_queue(context.chip_read_req_context_0.get(), &output_contexts_0);
  drain_queue(context.chip_read_req_context_1.get(), &output_contexts_1);
  drain_queue(context.chip_read_req_context_2.get(), &output_contexts_2);
  drain_queue(context.chip_read_req_context_3.get(), &output_contexts_3);

  ASSERT_EQ(input_unit_commands_0.size(), output_reqs_0.size());
  ASSERT_EQ(input_unit_commands_1.size(), output_reqs_1.size());
  ASSERT_EQ(input_unit_commands_2.size(), output_reqs_2.size());
  ASSERT_EQ(input_unit_commands_3.size(), output_reqs_3.size());

  ASSERT_EQ(input_unit_commands_0.size(), output_contexts_0.size());
  ASSERT_EQ(input_unit_commands_1.size(), output_contexts_1.size());
  ASSERT_EQ(input_unit_commands_2.size(), output_contexts_2.size());
  ASSERT_EQ(input_unit_commands_3.size(), output_contexts_3.size());

  for (int i = 0; i < input_unit_commands_0.size(); i++) {
    EXPECT_EQ((unsigned long long)input_unit_commands_0[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_reqs_0[i].addr);
    EXPECT_EQ((unsigned long long)input_unit_commands_0[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_contexts_0[i].addr);
  }

  for (int i = 0; i < input_unit_commands_1.size(); i++) {
    EXPECT_EQ((unsigned long long)input_unit_commands_1[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_reqs_1[i].addr);
    EXPECT_EQ((unsigned long long)input_unit_commands_1[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_contexts_1[i].addr);
  }

  for (int i = 0; i < input_unit_commands_2.size(); i++) {
    EXPECT_EQ((unsigned long long)input_unit_commands_2[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_reqs_2[i].addr);
    EXPECT_EQ((unsigned long long)input_unit_commands_2[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_contexts_2[i].addr);
  }

  for (int i = 0; i < input_unit_commands_3.size(); i++) {
    EXPECT_EQ((unsigned long long)input_unit_commands_3[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_reqs_3[i].addr);
    EXPECT_EQ((unsigned long long)input_unit_commands_3[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_contexts_3[i].addr);
  }
}

TEST(test_cmd_dispatcher, all_bank_dispatch_interleave) {
  // generate & input `unit_command` in round robin manner

  std::vector<Unit_Command> input_unit_commands_0;
  std::vector<Unit_Command> input_unit_commands_1;
  std::vector<Unit_Command> input_unit_commands_2;
  std::vector<Unit_Command> input_unit_commands_3;

  std::vector<Chip_Read_Req> output_reqs_0;
  std::vector<Chip_Read_Req> output_reqs_1;
  std::vector<Chip_Read_Req> output_reqs_2;
  std::vector<Chip_Read_Req> output_reqs_3;

  std::vector<Chip_Read_Req> output_contexts_0;
  std::vector<Chip_Read_Req> output_contexts_1;
  std::vector<Chip_Read_Req> output_contexts_2;
  std::vector<Chip_Read_Req> output_contexts_3;

  cmd_dispatcher_context context;

  for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
    Unit_Command unit_command = RandomGen::rand_unit_command(0, true);
    input_unit_commands_0.push_back(unit_command);
    context.unit_command_queue->write(unit_command);

    unit_command = RandomGen::rand_unit_command(1, true);
    input_unit_commands_1.push_back(unit_command);
    context.unit_command_queue->write(unit_command);

    unit_command = RandomGen::rand_unit_command(2, true);
    input_unit_commands_2.push_back(unit_command);
    context.unit_command_queue->write(unit_command);

    unit_command = RandomGen::rand_unit_command(3, true);
    input_unit_commands_3.push_back(unit_command);
    context.unit_command_queue->write(unit_command);
  }

  RUN_METHOD(4 * TEST_NUM_OF_COMMANDS, INVOKE_CMD_DISPATCHER_IMPL(context));

  drain_queue(context.chip_read_req_queue_0.get(), &output_reqs_0);
  drain_queue(context.chip_read_req_queue_1.get(), &output_reqs_1);
  drain_queue(context.chip_read_req_queue_2.get(), &output_reqs_2);
  drain_queue(context.chip_read_req_queue_3.get(), &output_reqs_3);

  drain_queue(context.chip_read_req_context_0.get(), &output_contexts_0);
  drain_queue(context.chip_read_req_context_1.get(), &output_contexts_1);
  drain_queue(context.chip_read_req_context_2.get(), &output_contexts_2);
  drain_queue(context.chip_read_req_context_3.get(), &output_contexts_3);

  ASSERT_EQ(input_unit_commands_0.size(), output_reqs_0.size());
  ASSERT_EQ(input_unit_commands_1.size(), output_reqs_1.size());
  ASSERT_EQ(input_unit_commands_2.size(), output_reqs_2.size());
  ASSERT_EQ(input_unit_commands_3.size(), output_reqs_3.size());

  ASSERT_EQ(input_unit_commands_0.size(), output_contexts_0.size());
  ASSERT_EQ(input_unit_commands_1.size(), output_contexts_1.size());
  ASSERT_EQ(input_unit_commands_2.size(), output_contexts_2.size());
  ASSERT_EQ(input_unit_commands_3.size(), output_contexts_3.size());

  for (int i = 0; i < input_unit_commands_0.size(); i++) {
    EXPECT_EQ((unsigned long long)input_unit_commands_0[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_reqs_0[i].addr);
    EXPECT_EQ((unsigned long long)input_unit_commands_0[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_contexts_0[i].addr);
  }

  for (int i = 0; i < input_unit_commands_1.size(); i++) {
    EXPECT_EQ((unsigned long long)input_unit_commands_1[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_reqs_1[i].addr);
    EXPECT_EQ((unsigned long long)input_unit_commands_1[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_contexts_1[i].addr);
  }

  for (int i = 0; i < input_unit_commands_2.size(); i++) {
    EXPECT_EQ((unsigned long long)input_unit_commands_2[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_reqs_2[i].addr);
    EXPECT_EQ((unsigned long long)input_unit_commands_2[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_contexts_2[i].addr);
  }

  for (int i = 0; i < input_unit_commands_3.size(); i++) {
    EXPECT_EQ((unsigned long long)input_unit_commands_3[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_reqs_3[i].addr);
    EXPECT_EQ((unsigned long long)input_unit_commands_3[i].index *
                  UNIT_CHUCK_SIZE_IN_BYTE,
              output_contexts_3[i].addr);
  }
}
