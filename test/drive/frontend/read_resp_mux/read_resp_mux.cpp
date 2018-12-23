#include <cstdlib>
#include <vector>

#include "chip.h"
#include "cmd.h"
#include "gtest/gtest.h"
#include "read_resp_mux.hpp"
#include "staccel_type.h"
#include "test_params.hpp"
#include "test_utils.hpp"

#define TEST_NUM_OF_COMMANDS 10
#define QUEUE_DEPTH (32)
#define INVOKE_READ_RESP_MUX_IMPL(context)                         \
  read_resp_mux_impl(context.chip_read_req_context[0].get(),       \
                     context.chip_read_resp_queue[0].get(),        \
                     context.chip_read_req_context[1].get(),       \
                     context.chip_read_resp_queue[1].get(),        \
                     context.chip_read_req_context[2].get(),       \
                     context.chip_read_resp_queue[2].get(),        \
                     context.chip_read_req_context[3].get(),       \
                     context.chip_read_resp_queue[3].get(),        \
                     context.chip_read_resp_with_addr_queue.get(), \
                     &(context.write_lease))

struct Read_Resp_Mux_Context {
  std::vector<std::unique_ptr<ST_Queue<Chip_Read_Req>>> chip_read_req_context;
  std::vector<std::unique_ptr<ST_Queue<Chip_Read_Resp>>> chip_read_resp_queue;
  std::unique_ptr<ST_Queue<Chip_Read_Resp_With_Addr>>
      chip_read_resp_with_addr_queue;
  unsigned char write_lease = 0;
  Read_Resp_Mux_Context() {
    chip_read_req_context.resize(4);
    chip_read_resp_queue.resize(4);
    for (int i = 0; i < NUM_OF_CHIP_BANKS; i++) {
      chip_read_req_context[i].reset(new ST_Queue<Chip_Read_Req>(QUEUE_DEPTH));
      chip_read_resp_queue[i].reset(new ST_Queue<Chip_Read_Resp>(QUEUE_DEPTH));
    }
    chip_read_resp_with_addr_queue.reset(new ST_Queue<Chip_Read_Resp_With_Addr>(
        NUM_OF_CHIP_BANKS * QUEUE_DEPTH));
  }
};

TEST(test_read_resp_mux, bank_0_resemble) {
  Read_Resp_Mux_Context context;
  std::vector<std::vector<Chip_Read_Resp>> input_read_resps(NUM_OF_CHIP_BANKS);
  std::vector<std::vector<Chip_Read_Req>> input_read_reqs(NUM_OF_CHIP_BANKS);
  std::vector<Chip_Read_Resp_With_Addr> output_read_resp_with_addrs;

  for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
    Chip_Read_Resp chip_read_resp = RandomGen::rand_chip_read_resp();
    Chip_Read_Req chip_read_req = RandomGen::rand_chip_read_req(0 /*bank_id*/);
    input_read_resps[0].push_back(chip_read_resp);
    input_read_reqs[0].push_back(chip_read_req);
    context.chip_read_resp_queue[0]->write(chip_read_resp);
    context.chip_read_req_context[0]->write(chip_read_req);
  }

  RUN_METHOD(4 * TEST_NUM_OF_COMMANDS, INVOKE_READ_RESP_MUX_IMPL(context));

  drain_queue(context.chip_read_resp_with_addr_queue.get(),
              &output_read_resp_with_addrs);
  ASSERT_EQ(input_read_resps[0].size(), output_read_resp_with_addrs.size());

  for (int i = 0; i < output_read_resp_with_addrs.size(); i++) {
    EXPECT_EQ(input_read_resps[0][i].data, output_read_resp_with_addrs[i].data);
    EXPECT_EQ(input_read_reqs[0][i].addr, output_read_resp_with_addrs[i].addr);
  }
}

TEST(test_read_resp_mux, bank_1_resemble) {
  Read_Resp_Mux_Context context;
  std::vector<std::vector<Chip_Read_Resp>> input_read_resps(NUM_OF_CHIP_BANKS);
  std::vector<std::vector<Chip_Read_Req>> input_read_reqs(NUM_OF_CHIP_BANKS);
  std::vector<Chip_Read_Resp_With_Addr> output_read_resp_with_addrs;

  for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
    Chip_Read_Resp chip_read_resp = RandomGen::rand_chip_read_resp();
    Chip_Read_Req chip_read_req = RandomGen::rand_chip_read_req(1 /*bank_id*/);
    input_read_resps[1].push_back(chip_read_resp);
    input_read_reqs[1].push_back(chip_read_req);
    context.chip_read_resp_queue[1]->write(chip_read_resp);
    context.chip_read_req_context[1]->write(chip_read_req);
  }

  RUN_METHOD(10 * TEST_NUM_OF_COMMANDS, INVOKE_READ_RESP_MUX_IMPL(context));

  drain_queue(context.chip_read_resp_with_addr_queue.get(),
              &output_read_resp_with_addrs);
  ASSERT_EQ(input_read_resps[1].size(), output_read_resp_with_addrs.size());

  for (int i = 0; i < output_read_resp_with_addrs.size(); i++) {
    EXPECT_EQ(input_read_resps[1][i].data, output_read_resp_with_addrs[i].data);
    EXPECT_EQ(input_read_reqs[1][i].addr, output_read_resp_with_addrs[i].addr);
  }
}

TEST(test_read_resp_mux, bank_2_resemble) {
  Read_Resp_Mux_Context context;
  std::vector<std::vector<Chip_Read_Resp>> input_read_resps(NUM_OF_CHIP_BANKS);
  std::vector<std::vector<Chip_Read_Req>> input_read_reqs(NUM_OF_CHIP_BANKS);
  std::vector<Chip_Read_Resp_With_Addr> output_read_resp_with_addrs;

  for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
    Chip_Read_Resp chip_read_resp = RandomGen::rand_chip_read_resp();
    Chip_Read_Req chip_read_req = RandomGen::rand_chip_read_req(2 /*bank_id*/);
    input_read_resps[2].push_back(chip_read_resp);
    input_read_reqs[2].push_back(chip_read_req);
    context.chip_read_resp_queue[2]->write(chip_read_resp);
    context.chip_read_req_context[2]->write(chip_read_req);
  }

  RUN_METHOD(4 * TEST_NUM_OF_COMMANDS, INVOKE_READ_RESP_MUX_IMPL(context));

  drain_queue(context.chip_read_resp_with_addr_queue.get(),
              &output_read_resp_with_addrs);
  ASSERT_EQ(input_read_resps[2].size(), output_read_resp_with_addrs.size());

  for (int i = 0; i < output_read_resp_with_addrs.size(); i++) {
    EXPECT_EQ(input_read_resps[2][i].data, output_read_resp_with_addrs[i].data);
    EXPECT_EQ(input_read_reqs[2][i].addr, output_read_resp_with_addrs[i].addr);
  }
}

TEST(test_read_resp_mux, bank_3_resemble) {
  Read_Resp_Mux_Context context;
  std::vector<std::vector<Chip_Read_Resp>> input_read_resps(NUM_OF_CHIP_BANKS);
  std::vector<std::vector<Chip_Read_Req>> input_read_reqs(NUM_OF_CHIP_BANKS);
  std::vector<Chip_Read_Resp_With_Addr> output_read_resp_with_addrs;

  for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
    Chip_Read_Resp chip_read_resp = RandomGen::rand_chip_read_resp();
    Chip_Read_Req chip_read_req = RandomGen::rand_chip_read_req(3);
    input_read_resps[3].push_back(chip_read_resp);
    input_read_reqs[3].push_back(chip_read_req);
    context.chip_read_resp_queue[3]->write(chip_read_resp);
    context.chip_read_req_context[3]->write(chip_read_req);
  }

  RUN_METHOD(4 * TEST_NUM_OF_COMMANDS, INVOKE_READ_RESP_MUX_IMPL(context));

  drain_queue(context.chip_read_resp_with_addr_queue.get(),
              &output_read_resp_with_addrs);
  ASSERT_EQ(input_read_resps[3].size(), output_read_resp_with_addrs.size());

  for (int i = 0; i < output_read_resp_with_addrs.size(); i++) {
    EXPECT_EQ(input_read_resps[3][i].data, output_read_resp_with_addrs[i].data);
    EXPECT_EQ(input_read_reqs[3][i].addr, output_read_resp_with_addrs[i].addr);
  }
}

TEST(test_read_resp_mux, all_bank_resemble) {
  Read_Resp_Mux_Context context;
  std::vector<std::vector<Chip_Read_Resp>> input_read_resps(NUM_OF_CHIP_BANKS);
  std::vector<std::vector<Chip_Read_Req>> input_read_reqs(NUM_OF_CHIP_BANKS);
  std::vector<Chip_Read_Resp_With_Addr> output_read_resp_with_addrs;

  for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
    Chip_Read_Resp chip_read_resp = RandomGen::rand_chip_read_resp();
    Chip_Read_Req chip_read_req = RandomGen::rand_chip_read_req();
    unsigned char bank_id =
        (unsigned char)chip_read_req.addr & (NUM_OF_CHIP_BANKS - 1);
    input_read_reqs[bank_id].push_back(chip_read_req);
    input_read_resps[bank_id].push_back(chip_read_resp);
    context.chip_read_resp_queue[bank_id]->write(chip_read_resp);
    context.chip_read_req_context[bank_id]->write(chip_read_req);
  }

  RUN_METHOD(NUM_OF_CHIP_BANKS * TEST_NUM_OF_COMMANDS,
             INVOKE_READ_RESP_MUX_IMPL(context));

  drain_queue(context.chip_read_resp_with_addr_queue.get(),
              &output_read_resp_with_addrs);

  ASSERT_EQ(input_read_resps[0].size() + input_read_resps[1].size() +
                input_read_resps[2].size() + input_read_resps[3].size(),
            output_read_resp_with_addrs.size());

  unsigned int bank_data_ptr[NUM_OF_CHIP_BANKS] = {0};
  for (int i = 0; i < output_read_resp_with_addrs.size(); i++) {
    unsigned char bank_id = (unsigned char)output_read_resp_with_addrs[i].addr &
                            (NUM_OF_CHIP_BANKS - 1);

    EXPECT_EQ(input_read_resps[bank_id][bank_data_ptr[bank_id]].data,
              output_read_resp_with_addrs[i].data);
    EXPECT_EQ(input_read_reqs[bank_id][bank_data_ptr[bank_id]++].addr,
              output_read_resp_with_addrs[i].addr);
  }
}
