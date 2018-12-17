#include <cstdlib>
#include <memory>
#include <vector>

#include "gtest/gtest.h"
#include "staccel_type.h"
#include "test_params.hpp"
#include "test_utils.hpp"
#include "throttle_unit.hpp"

#define INVOKE_THROTTLE_UNIT_IMPL(context)                             \
  throttle_unit_impl(context.throttle_ratio_queue_ptr.get(),           \
                     context.chip_read_req_queue_ptr.get(),            \
                     context.chip_read_resp_queue_ptr.get(),           \
                     context.chip_write_req_queue_ptr.get(),           \
                     context.throttled_chip_read_req_queue_ptr.get(),  \
                     context.throttled_chip_read_resp_queue_ptr.get(), \
                     context.throttled_chip_write_req_queue_ptr.get())

struct ThrottleUnitTestContext {
  std::unique_ptr<ST_Queue<unsigned int>> throttle_ratio_queue_ptr;
  std::unique_ptr<ST_Queue<Chip_Read_Req>> chip_read_req_queue_ptr;
  std::unique_ptr<ST_Queue<Chip_Read_Resp>> chip_read_resp_queue_ptr;
  std::unique_ptr<ST_Queue<Chip_Write_Req>> chip_write_req_queue_ptr;
  std::unique_ptr<ST_Queue<Chip_Read_Req>> throttled_chip_read_req_queue_ptr;
  std::unique_ptr<ST_Queue<Chip_Read_Resp>> throttled_chip_read_resp_queue_ptr;
  std::unique_ptr<ST_Queue<Chip_Write_Req>> throttled_chip_write_req_queue_ptr;

  ThrottleUnitTestContext() {
    throttle_ratio_queue_ptr.reset(new ST_Queue<unsigned int>(128));
    chip_read_req_queue_ptr.reset(new ST_Queue<Chip_Read_Req>(128));
    chip_read_resp_queue_ptr.reset(new ST_Queue<Chip_Read_Resp>(128));
    chip_write_req_queue_ptr.reset(new ST_Queue<Chip_Write_Req>(128));
    throttled_chip_read_req_queue_ptr.reset(new ST_Queue<Chip_Read_Req>(128));
    throttled_chip_read_resp_queue_ptr.reset(new ST_Queue<Chip_Read_Resp>(128));
    throttled_chip_write_req_queue_ptr.reset(new ST_Queue<Chip_Write_Req>(128));
  }
};

void test_correct_throttle_chip_read_resp_and_chip_write_req(
    bool has_throttle_ratio, unsigned int throttle_ratio) {
  const int NUM_ENTRIES = 128;

  if (!has_throttle_ratio) {
    throttle_ratio = DEFAULT_THROTTLE_RATIO;
  }

  ThrottleUnitTestContext context;
  static Chip_Read_Resp resps[NUM_ENTRIES];
  static Chip_Write_Req reqs[NUM_ENTRIES];

  for (int i = 0; i < NUM_ENTRIES; i++) {
    int int_size_in_bit = sizeof(int) * 8;
    resps[i] = RandomGen::rand_chip_read_resp();
    reqs[i] = RandomGen::rand_chip_write_req();
    context.chip_read_resp_queue_ptr->write(resps[i]);
    context.chip_write_req_queue_ptr->write(reqs[i]);
  }
  context.throttle_ratio_queue_ptr->write(throttle_ratio);
  RUN_METHOD(NUM_ENTRIES, INVOKE_THROTTLE_UNIT_IMPL(context));
  std::vector<Chip_Read_Resp> real_throttled_chip_read_resps;
  std::vector<Chip_Write_Req> real_throttled_chip_write_reqs;
  drain_queue(context.throttled_chip_read_resp_queue_ptr.get(),
              &real_throttled_chip_read_resps);
  drain_queue(context.throttled_chip_write_req_queue_ptr.get(),
              &real_throttled_chip_write_reqs);
  ASSERT_EQ(real_throttled_chip_read_resps.size(),
            NUM_ENTRIES / throttle_ratio);
  ASSERT_EQ(real_throttled_chip_write_reqs.size(),
            NUM_ENTRIES / throttle_ratio);
  for (int i = 0; i < NUM_ENTRIES / throttle_ratio; i++) {
    EXPECT_EQ(real_throttled_chip_read_resps[i], resps[i]);
    EXPECT_EQ(real_throttled_chip_write_reqs[i], reqs[i]);
    EXPECT_EQ(real_throttled_chip_write_reqs[i], reqs[i]);
  }
}

TEST(throttle_unit_impl, correct_bypass_chip_read_req) {
  const int NUM_REQS = 128;

  ThrottleUnitTestContext context;
  Chip_Read_Req reqs[NUM_REQS];
  for (int i = 0; i < NUM_REQS; i++) {
    reqs[i] = RandomGen::rand_chip_read_req();
    context.chip_read_req_queue_ptr->write(reqs[i]);
  }
  context.throttle_ratio_queue_ptr->write(DEFAULT_THROTTLE_RATIO);
  RUN_METHOD(NUM_REQS, INVOKE_THROTTLE_UNIT_IMPL(context));
  std::vector<Chip_Read_Req> real_throttled_chip_read_reqs;
  drain_queue(context.throttled_chip_read_req_queue_ptr.get(),
              &real_throttled_chip_read_reqs);
  ASSERT_EQ(real_throttled_chip_read_reqs.size(), NUM_REQS);
  for (int i = 0; i < NUM_REQS; i++) {
    EXPECT_EQ(real_throttled_chip_read_reqs[i], reqs[i]);
  }
}

TEST(throttle_unit_impl, correct_throttle_chip_read_resp_and_chip_write_req) {
  test_correct_throttle_chip_read_resp_and_chip_write_req(0, 0);
  test_correct_throttle_chip_read_resp_and_chip_write_req(1, 8);
}
