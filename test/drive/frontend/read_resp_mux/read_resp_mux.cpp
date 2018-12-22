#include <cstdlib>
#include <vector>

#include "chip.h"
#include "cmd.h"
#include "gtest/gtest.h"
#include "read_resp_mux.hpp"
#include "staccel_type.h"
#include "test_params.hpp"
#include "test_utils.hpp"

#ndefine TEST_NUM_OF_COMMANDS 10
#define QUEUE_DEPTH (32)
#define INVOKE_READ_RESP_MUX_IMPL(context)                         \
  read_resp_mux_impl(context.chip_read_req_context_0.get(),        \
                     context.chip_read_resp_queue_0.get(),         \
                     context.chip_read_req_context_1.get(),        \
                     context.chip_read_resp_queue_1.get(),         \
                     context.chip_read_req_context_2.get(),        \
                     context.chip_read_resp_queue_2.get(),         \
                     context.chip_read_req_context_3.get(),        \
                     context.chip_read_resp_queue_3.get(),         \
                     context.chip_read_resp_with_addr_queue.get(), \
                     &(context.write_lease))

struct Read_Resp_Mux_Context {
  std::unique_ptr<ST_Queue<Chip_Read_Req>> chip_read_req_context_0;
  std::unique_ptr<ST_Queue<Chip_Read_Resp>> chip_read_resp_queue_0;
  std::unique_ptr<ST_Queue<Chip_Read_Req>> chip_read_req_context_1;
  std::unique_ptr<ST_Queue<Chip_Read_Resp>> chip_read_resp_queue_1;
  std::unique_ptr<ST_Queue<Chip_Read_Req>> chip_read_req_context_2;
  std::unique_ptr<ST_Queue<Chip_Read_Resp>> chip_read_resp_queue_2;
  std::unique_ptr<ST_Queue<Chip_Read_Req>> chip_read_req_context_3;
  std::unique_ptr<ST_Queue<Chip_Read_Resp>> chip_read_resp_queue_3;
  std::unique_ptr<ST_Queue<Chip_Read_Resp_With_Addr>>
      chip_read_resp_with_addr_queue;
  unsigned char write_lease = 0;
  Read_Resp_Mux_Context() {
    chip_read_req_context_0.reset(new ST_Queue<Chip_Read_Req>(QUEUE_DEPTH));
    chip_read_resp_queue_0.reset(new ST_Queue<Chip_Read_Resp>(QUEUE_DEPTH));
    chip_read_req_context_1.reset(new ST_Queue<Chip_Read_Req>(QUEUE_DEPTH));
    chip_read_resp_queue_1.reset(new ST_Queue<Chip_Read_Resp>(QUEUE_DEPTH));

    chip_read_req_context_2.reset(new ST_Queue<Chip_Read_Req>(QUEUE_DEPTH));
    chip_read_resp_queue_2.reset(new ST_Queue<Chip_Read_Resp>(QUEUE_DEPTH));

    chip_read_req_context_3.reset(new ST_Queue<Chip_Read_Req>(QUEUE_DEPTH));
    chip_read_resp_queue_3.reset(new ST_Queue<Chip_Read_Resp>(QUEUE_DEPTH));

    chip_read_resp_with_addr_queue.reset(new ST_Queue<Chip_Read_Resp_With_Addr>(
        NUM_OF_CHIP_BANKS * QUEUE_DEPTH));
  }
};

TEST(read_resp_mux, bank_0_test) {
  Read_Resp_Mux_Context context;
  std::vector<std::vector<Chip_Read_Resp>> input_read_resps(NUM_OF_CHIP_BANKS);
  std::vector<std::vector<Chip_Read_Req>> input_read_reqs(NUM_OF_CHIP_BANKS);
  std::vector<Chip_Read_Resp_With_Addr> output_read_resp_with_addrs;

  for (int i = 0; i < TEST_NUM_OF_COMMANDS; i++) {
    Chip_Read_Resp chip_read_resp = RandomGen::rand_chip_read_resp();
    Chip_Read_Req chip_read_req = RandomGen::rand_chip_read_req(0);
    input_read_resps[0].push_back(chip_read_resp);
    input_read_reqs[0].push_back(chip_read_req);
  }

  read_resp_mux_impl(context.chip_read_req_context_0.get(),
                     context.chip_read_resp_queue_0.get(),
                     context.chip_read_req_context_1.get(),
                     context.chip_read_resp_queue_1.get(),
                     context.chip_read_req_context_2.get(),
                     context.chip_read_resp_queue_2.get(),
                     context.chip_read_req_context_3.get(),
                     context.chip_read_resp_queue_3.get(),
                     context.chip_read_resp_with_addr_queue.get(),
                     &(context.write_lease));

  //  RUN_METHOD(TEST_NUM_OF_COMMANDS, INVOKE_READ_RESP_MUX_IMPL(context));

  drain_queue(context.chip_read_resp_with_addr_queue.get(),
              &output_read_resp_with_addrs);
  ASSERT_EQ(input_read_resps[0].size(), output_read_resp_with_addrs.size());

  for (int i = 0; i < output_read_resp_with_addrs.size(); i++) {
    EXPECT_EQ(input_read_resps[0][i].data, output_read_resp_with_addrs[i].data);
    EXPECT_EQ(input_read_reqs[0][i].addr, output_read_resp_with_addrs[i].addr);
  }
}
