#include <vector>

#include "cmd.h"
#include "cmd_dispatcher.hpp"
#include "gtest/gtest.h"
#include "staccel_type.h"
#include "test_params.hpp"
#include "test_utils.hpp"

#define TEST_NUM_OF_COMMANDS 10
#define QUEUE_DEPTH 64
#define INVOKE_CMD_DISPATCHER_IMPL(context)			\
  cmd_dispatcher_impl(context.command_queue.get(),		\
		      context.host_write_data_queue.get(),	\
		      context.chip_read_req_queue_0.get(),	\
		      context.chip_read_req_context_0.get(),	\
		      context.chip_write_req_queue_0.get(),	\
		      context.chip_read_req_queue_1.get(),	\
		      context.chip_read_req_context_1.get(),	\
		      context.chip_write_req_queue_1.get(),	\
		      context.chip_read_req_queue_2.get(),	\
		      context.chip_read_req_context_2.get(),	\
		      context.chip_write_req_queue_2.get(),	\
		      context.chip_read_req_queue_3.get(),	\
		      context.chip_read_req_context_3.get(),	\
		      context.chip_write_req_queue_3.get()	\
		      )



struct cmd_dispatcher_context {

  std::unique_ptr<ST_Queue<Command>> command_queue;
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
    command_queue.reset(new ST_Queue<Command>(QUEUE_DEPTH));
    host_write_data_queue.reset(new ST_Queue<Host_Write_Data>(QUEUE_DEPTH));
   
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

// TEST(test_cmd_dispatcher, bank_0_dispatch) {

//   std::vector<Command> expected;
//   std::vector<Chip_Read_Req> real;
//   cmd_dispatcher_context context;

//   // generate bank 0 command
//   for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
//     Command command = RandomGen::rand_command(0, true);
//     expected.push_back(command);
//     context.command_queue->write(command);
//   }

//   RUN_METHOD(TEST_NUM_OF_COMMANDS, INVOKE_CMD_DISPATCHER_IMPL(context));

//   drain_queue(context.chip_read_req_queue_0.get(), &real);

//   ASSERT_EQ(expected.size(), real.size());

//   for (int i = 0; i < expected.size(); i++) {
//     EXPECT_EQ((unsigned long long) expected[i].index, real[i].addr);
//   }
// }

// TEST(test_cmd_dispatcher, bank_1_dispatch) {

//   std::vector<Command> expected;
//   std::vector<Chip_Read_Req> real;
//   cmd_dispatcher_context context;

//   // generate bank 1 command
//   for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
//     Command command = RandomGen::rand_command(1, true);
//     expected.push_back(command);
//     context.command_queue->write(command);
//   }

//   RUN_METHOD(TEST_NUM_OF_COMMANDS, INVOKE_CMD_DISPATCHER_IMPL(context));

//   drain_queue(context.chip_read_req_queue_1.get(), &real);

//   ASSERT_EQ(expected.size(), real.size());

//   for (int i = 0; i < expected.size(); i++) {
//     EXPECT_EQ((unsigned long long) expected[i].index, real[i].addr);
//   }
// }

// TEST(test_cmd_dispatcher, bank_2_dispatch) {

//   std::vector<Command> expected;
//   std::vector<Chip_Read_Req> real;
//   cmd_dispatcher_context context;

//   // generate bank 2 command
//   for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
//     Command command = RandomGen::rand_command(2, true);
//     expected.push_back(command);
//     context.command_queue->write(command);
//   }

//   RUN_METHOD(TEST_NUM_OF_COMMANDS, INVOKE_CMD_DISPATCHER_IMPL(context));

//   drain_queue(context.chip_read_req_queue_2.get(), &real);

//   ASSERT_EQ(expected.size(), real.size());

//   for (int i = 0; i < expected.size(); i++) {
//     EXPECT_EQ((unsigned long long) expected[i].index, real[i].addr);
//   }
// }

// TEST(test_cmd_dispatcher, bank_3_dispatch) {

//   std::vector<Command> expected;
//   std::vector<Chip_Read_Req> real;
//   cmd_dispatcher_context context;

//   // generate bank 3 command
//   for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
//     Command command = RandomGen::rand_command(3, true);
//     expected.push_back(command);
//     context.command_queue->write(command);
//   }

//   RUN_METHOD(TEST_NUM_OF_COMMANDS, INVOKE_CMD_DISPATCHER_IMPL(context));

//   drain_queue(context.chip_read_req_queue_3.get(), &real);

//   ASSERT_EQ(expected.size(), real.size());

//   for (int i = 0; i < expected.size(); i++) {
//     EXPECT_EQ((unsigned long long) expected[i].index, real[i].addr);
//   }
// }

// TEST(test_cmd_dispatcher, all_bank_dispatch_random) {

//   std::vector<Command> expected_bank_0;
//   std::vector<Command> expected_bank_1;
//   std::vector<Command> expected_bank_2;
//   std::vector<Command> expected_bank_3;

//   std::vector<Chip_Read_Req> real_bank_0;
//   std::vector<Chip_Read_Req> real_bank_1;
//   std::vector<Chip_Read_Req> real_bank_2;
//   std::vector<Chip_Read_Req> real_bank_3;

//   cmd_dispatcher_context context;

//   for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
//     Command command = RandomGen::rand_command();
//     switch (((unsigned long long) command.index) & 3) {
//     case 0: expected_bank_0.push_back(command); break;
//     case 1: expected_bank_1.push_back(command); break;
//     case 2: expected_bank_2.push_back(command); break;
//     case 3: expected_bank_3.push_back(command); break;
//     }
//     context.command_queue->write(command);
//   }

//   RUN_METHOD(TEST_NUM_OF_COMMANDS, INVOKE_CMD_DISPATCHER_IMPL(context));

//   drain_queue(context.chip_read_req_queue_0.get(), &real_bank_0);
//   drain_queue(context.chip_read_req_queue_1.get(), &real_bank_1);
//   drain_queue(context.chip_read_req_queue_2.get(), &real_bank_2);
//   drain_queue(context.chip_read_req_queue_3.get(), &real_bank_3);

//   ASSERT_EQ(expected_bank_0.size(), real_bank_0.size());
//   ASSERT_EQ(expected_bank_1.size(), real_bank_1.size());
//   ASSERT_EQ(expected_bank_2.size(), real_bank_2.size());
//   ASSERT_EQ(expected_bank_3.size(), real_bank_3.size());

//   for (int i = 0; i < expected_bank_0.size(); i++) {
//     EXPECT_EQ((unsigned long long) expected_bank_0[i].index, real_bank_0[i].addr);
//   }

//   for (int i = 0; i < expected_bank_1.size(); i++) {
//     EXPECT_EQ((unsigned long long) expected_bank_1[i].index, real_bank_1[i].addr);
//   }

//   for (int i = 0; i < expected_bank_2.size(); i++) {
//     EXPECT_EQ((unsigned long long) expected_bank_2[i].index, real_bank_2[i].addr);
//   }

//   for (int i = 0; i < expected_bank_3.size(); i++) {
//     EXPECT_EQ((unsigned long long) expected_bank_3[i].index, real_bank_3[i].addr);
//   }
// }

// TEST(test_cmd_dispatcher, all_bank_dispatch_interleave) {
//   // generate & input `command` in round robin manner

//   std::vector<Command> expected_bank_0;
//   std::vector<Command> expected_bank_1;
//   std::vector<Command> expected_bank_2;
//   std::vector<Command> expected_bank_3;

//   std::vector<Chip_Read_Req> real_bank_0;
//   std::vector<Chip_Read_Req> real_bank_1;
//   std::vector<Chip_Read_Req> real_bank_2;
//   std::vector<Chip_Read_Req> real_bank_3;

//   cmd_dispatcher_context context;

//   for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
//     Command command = RandomGen::rand_command(0, true);
//     expected_bank_0.push_back(command);
//     context.command_queue->write(command);

//     command = RandomGen::rand_command(1, true);
//     expected_bank_1.push_back(command);
//     context.command_queue->write(command);

//     command = RandomGen::rand_command(2, true);
//     expected_bank_2.push_back(command);
//     context.command_queue->write(command);

//     command = RandomGen::rand_command(3, true);
//     expected_bank_3.push_back(command);
//     context.command_queue->write(command);
//   }

//   RUN_METHOD(4 * TEST_NUM_OF_COMMANDS, INVOKE_CMD_DISPATCHER_IMPL(context));

//   drain_queue(context.chip_read_req_queue_0.get(), &real_bank_0);
//   drain_queue(context.chip_read_req_queue_1.get(), &real_bank_1);
//   drain_queue(context.chip_read_req_queue_2.get(), &real_bank_2);
//   drain_queue(context.chip_read_req_queue_3.get(), &real_bank_3);

//   ASSERT_EQ(expected_bank_0.size(), real_bank_0.size());
//   ASSERT_EQ(expected_bank_1.size(), real_bank_1.size());
//   ASSERT_EQ(expected_bank_2.size(), real_bank_2.size());
//   ASSERT_EQ(expected_bank_3.size(), real_bank_3.size());

//   for (int i = 0; i < expected_bank_0.size(); i++) {
//     EXPECT_EQ((unsigned long long) expected_bank_0[i].index, real_bank_0[i].addr);
//   }

//   for (int i = 0; i < expected_bank_1.size(); i++) {
//     EXPECT_EQ((unsigned long long) expected_bank_1[i].index, real_bank_1[i].addr);
//   }

//   for (int i = 0; i < expected_bank_2.size(); i++) {
//     EXPECT_EQ((unsigned long long) expected_bank_2[i].index, real_bank_2[i].addr);
//   }

//   for (int i = 0; i < expected_bank_3.size(); i++) {
//     EXPECT_EQ((unsigned long long) expected_bank_3[i].index, real_bank_3[i].addr);
//   }
//}

TEST(test_cmd_dispatcher, hol_blocking_bank_0) {

  std::vector<Command> expected_bank_0;
  std::vector<Command> expected_bank_1;
  std::vector<Command> expected_bank_2;
  std::vector<Command> expected_bank_3;

  std::vector<Chip_Read_Req> real_bank_0;
  std::vector<Chip_Read_Req> real_bank_1;
  std::vector<Chip_Read_Req> real_bank_2;
  std::vector<Chip_Read_Req> real_bank_3;

  cmd_dispatcher_context context;
  for (int i = 0; i < QUEUE_DEPTH; i++) {
    Command command = RandomGen::rand_command(0, true);
    expected_bank_0.push_back(command);
    context.command_queue->write(command);
  }

  for (int i = 0; i < 4 * TEST_NUM_OF_COMMANDS; i++) {
    Command command = RandomGen::rand_command();
    switch (((unsigned long long) command.index) & 3) {
    case 0: expected_bank_0.push_back(command); break;
    case 1: expected_bank_1.push_back(command); break;
    case 2: expected_bank_2.push_back(command); break;
    case 3: expected_bank_3.push_back(command); break;
    }
    context.command_queue->write(command);
  }

  RUN_METHOD(QUEUE_DEPTH + 10 * TEST_NUM_OF_COMMANDS, INVOKE_CMD_DISPATCHER_IMPL(context));

  drain_queue(context.chip_read_req_queue_0.get(), &real_bank_0);
  drain_queue(context.chip_read_req_queue_1.get(), &real_bank_1);
  drain_queue(context.chip_read_req_queue_2.get(), &real_bank_2);
  drain_queue(context.chip_read_req_queue_3.get(), &real_bank_3);

  std::cout << "expected bank 0 queue size is: " << expected_bank_0.size() << std::endl;
  std::cout << "real bank 1: " << real_bank_1.size() << "expected is: " << expected_bank_1.size() << std::endl;
  std::cout << "real bank 2: " << real_bank_2.size() << "expected is: " << expected_bank_2.size() << std::endl;
  std::cout << "real bank 3: " << real_bank_3.size() << "expected is: " << expected_bank_3.size() << std::endl;
  ASSERT_EQ(QUEUE_DEPTH, real_bank_0.size()); 
  ASSERT_EQ(0, real_bank_1.size());
  ASSERT_EQ(0, real_bank_2.size());
  ASSERT_EQ(0, real_bank_3.size());

  for (int i = 0; i < QUEUE_DEPTH; i++) {
    EXPECT_EQ((unsigned long long) expected_bank_0[i].index, real_bank_0[i].addr);
  }
}

TEST (queue_depth, queue_depth) {

  ST_Queue<int> queue(10);
  std::vector<int> expected;
  for (int i = 0; i < 20; i++) {
    int num = rand();
    std::cout << num << std::endl;
    expected.push_back(num);
    queue.write(num);
  }
  std::cout << "========" << std::endl;
  int item;
  int numOfItem = 0;
  int i = 0;
  while (queue.read_nb(item)) {
    int exp = expected[i++];
    std::cout << exp << " : " << item << std::endl;
    numOfItem++;
  }
  std::cout << "finally: " << numOfItem << std::endl;

}
