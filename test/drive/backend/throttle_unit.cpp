#include <cstdlib>
#include <memory>
#include <vector>

#include "gtest/gtest.h"
#include "staccel_type.h"
#include "test_params.hpp"
#include "test_utils.hpp"
#include "throttle_unit.hpp"

#define INVOKE_THROTTLE_UNIT_IMPL(context)                          \
  throttle_unit_impl(&context.valid_chip_read_req,                  \
    &context.valid_chip_read_resp, &context.valid_chip_write_req,   \
    &context.data_chip_read_req, &context.data_chip_read_resp,      \
    &context.data_chip_write_req, &context.state_chip_read_resp,    \
    &context.state_chip_write_req,                                  \
    context.chip_read_req_queue_ptr.get(),                         \
    context.chip_read_resp_queue_ptr.get(),                        \
    context.chip_write_req_queue_ptr.get(),                        \
    context.throttled_chip_read_req_queue_ptr.get(),               \
    context.throttled_chip_read_resp_queue_ptr.get(),              \
    context.throttled_chip_write_req_queue_ptr.get())

struct ThrottleUnitTestContext {
  bool valid_chip_read_req = false;
  bool valid_chip_read_resp = false;
  bool valid_chip_write_req = false;
  Chip_Read_Req data_chip_read_req;
  Chip_Read_Resp data_chip_read_resp;
  Chip_Write_Req data_chip_write_req;
  ap_uint<LOG2_THROTTLE_RATIO + 1> state_chip_read_resp = 0;
  ap_uint<LOG2_THROTTLE_RATIO + 1> state_chip_write_req = 0;
  std::unique_ptr<ST_Queue<Chip_Read_Req>> chip_read_req_queue_ptr;
  std::unique_ptr<ST_Queue<Chip_Read_Resp>> chip_read_resp_queue_ptr;
  std::unique_ptr<ST_Queue<Chip_Write_Req>> chip_write_req_queue_ptr;
  std::unique_ptr<ST_Queue<Chip_Read_Req>> throttled_chip_read_req_queue_ptr;
  std::unique_ptr<ST_Queue<Chip_Read_Resp>> throttled_chip_read_resp_queue_ptr;
  std::unique_ptr<ST_Queue<Chip_Write_Req>> throttled_chip_write_req_queue_ptr;

  ThrottleUnitTestContext() {
    chip_read_req_queue_ptr.reset(new ST_Queue<Chip_Read_Req>(128));
    chip_read_resp_queue_ptr.reset(new ST_Queue<Chip_Read_Resp>(128));
    chip_write_req_queue_ptr.reset(new ST_Queue<Chip_Write_Req>(128));
    throttled_chip_read_req_queue_ptr.reset(new ST_Queue<Chip_Read_Req>(128));
    throttled_chip_read_resp_queue_ptr.reset(new ST_Queue<Chip_Read_Resp>(128));
    throttled_chip_write_req_queue_ptr.reset(new ST_Queue<Chip_Write_Req>(128));
  }
};

TEST(throttle_unit_impl, correct_bypass_chip_read_req) {
  const int NUM_REQS = 128;

  ThrottleUnitTestContext context;
  Chip_Read_Req reqs[NUM_REQS];
  for (int i = 0; i < NUM_REQS; i++) {
    reqs[i].addr = 
      (((unsigned long long) rand()) << 32) | rand();
    context.chip_read_req_queue_ptr->write(reqs[i]);
  }
  RUN_METHOD(NUM_REQS, INVOKE_THROTTLE_UNIT_IMPL(context));
  std::vector<Chip_Read_Req> real_throttled_chip_read_reqs;
  drain_queue(context.throttled_chip_read_req_queue_ptr.get(), 
              &real_throttled_chip_read_reqs);
  ASSERT_EQ(real_throttled_chip_read_reqs.size(), NUM_REQS);
  for (int i = 0; i < NUM_REQS; i++) {
    EXPECT_EQ(real_throttled_chip_read_reqs[i].addr, reqs[i].addr);
  }
}

TEST(throttle_unit_impl, correct_throttle_chip_read_resp_and_chip_write_req) {
  const int NUM_ENTRIES = 128;

  ThrottleUnitTestContext context;
  static Chip_Read_Resp resps[NUM_ENTRIES];
  static Chip_Write_Req reqs[NUM_ENTRIES];

  for (int i = 0; i < NUM_ENTRIES; i++) {
    int int_size_in_bit = sizeof(int) * 8;
    for (int j = 0; j < PCIS_BUS_WIDTH; j += int_size_in_bit) {
      resps[i].data(j + int_size_in_bit - 1, j) = rand();
      reqs[i].data(j + int_size_in_bit - 1, j) = rand();
    }
    reqs[i].addr = 
      (((unsigned long long) rand()) << 32) | rand();
    context.chip_read_resp_queue_ptr->write(resps[i]);
    context.chip_write_req_queue_ptr->write(reqs[i]);
  }
  RUN_METHOD(NUM_ENTRIES, INVOKE_THROTTLE_UNIT_IMPL(context));
  std::vector<Chip_Read_Resp> real_throttled_chip_read_resps;
  std::vector<Chip_Write_Req> real_throttled_chip_write_reqs;
  drain_queue(context.throttled_chip_read_resp_queue_ptr.get(),
              &real_throttled_chip_read_resps);
  drain_queue(context.throttled_chip_write_req_queue_ptr.get(),
              &real_throttled_chip_write_reqs);
  ASSERT_EQ(real_throttled_chip_read_resps.size(), NUM_ENTRIES / THROTTLE_RATIO);
  ASSERT_EQ(real_throttled_chip_write_reqs.size(), NUM_ENTRIES / THROTTLE_RATIO);
  for (int i = 0; i < NUM_ENTRIES / THROTTLE_RATIO; i++) {
    EXPECT_EQ(real_throttled_chip_read_resps[i].data, resps[i].data);
    EXPECT_EQ(real_throttled_chip_write_reqs[i].addr, reqs[i].addr);
    EXPECT_EQ(real_throttled_chip_write_reqs[i].data, reqs[i].data);
  }
}
