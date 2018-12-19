#include <cstdlib>
#include <memory>
#include <vector>

#include "delay_unit.hpp"
#include "gtest/gtest.h"
#include "test_params.hpp"
#include "test_utils.hpp"

#define INVOKE_DELAY_UNIT_IMPL(context)                         \
  delay_unit_impl(&context.timestamp, &context.delay_cycles,    \
                  &context.valid_chip_read_req_with_time,       \
                  &context.valid_chip_read_resp_with_time,      \
                  &context.valid_chip_write_req_with_time,      \
                  &context.data_chip_read_req_with_time,        \
                  &context.data_chip_read_resp_with_time,       \
                  &context.data_chip_write_req_with_time,       \
                  context.delay_cycles_queue.get(),             \
                  context.chip_read_req_with_time_queue.get(),  \
                  context.chip_read_resp_with_time_queue.get(), \
                  context.chip_write_req_with_time_queue.get(), \
                  context.delayed_chip_read_req_queue.get(),    \
                  context.delayed_chip_read_resp_queue.get(),   \
                  context.delayed_chip_write_req_queue.get())

struct DelayUnitContext {
  unsigned long long timestamp = 0;
  unsigned int delay_cycles = DEFAULT_DELAY_CYCLES;
  bool valid_chip_read_req_with_time = false;
  bool valid_chip_read_resp_with_time = false;
  bool valid_chip_write_req_with_time = false;
  Chip_Read_Req_With_Time data_chip_read_req_with_time;
  Chip_Read_Resp_With_Time data_chip_read_resp_with_time;
  Chip_Write_Req_With_Time data_chip_write_req_with_time;
  std::unique_ptr<ST_Queue<unsigned int>> delay_cycles_queue;
  std::unique_ptr<ST_Queue<Chip_Read_Req_With_Time>>
      chip_read_req_with_time_queue;
  std::unique_ptr<ST_Queue<Chip_Read_Resp_With_Time>>
      chip_read_resp_with_time_queue;
  std::unique_ptr<ST_Queue<Chip_Write_Req_With_Time>>
      chip_write_req_with_time_queue;
  std::unique_ptr<ST_Queue<Chip_Read_Req>> delayed_chip_read_req_queue;
  std::unique_ptr<ST_Queue<Chip_Read_Resp>> delayed_chip_read_resp_queue;
  std::unique_ptr<ST_Queue<Chip_Write_Req>> delayed_chip_write_req_queue;

  Chip_Read_Req_With_Time input_chip_read_req_with_times[128];
  Chip_Read_Resp_With_Time input_chip_read_resp_with_times[128];
  Chip_Write_Req_With_Time input_chip_write_req_with_times[128];

  DelayUnitContext() {
    delay_cycles_queue.reset(new ST_Queue<unsigned int>(128));
    chip_read_req_with_time_queue.reset(
        new ST_Queue<Chip_Read_Req_With_Time>(128));
    chip_read_resp_with_time_queue.reset(
        new ST_Queue<Chip_Read_Resp_With_Time>(128));
    chip_write_req_with_time_queue.reset(
        new ST_Queue<Chip_Write_Req_With_Time>(128));
    delayed_chip_read_req_queue.reset(new ST_Queue<Chip_Read_Req>(128));
    delayed_chip_read_resp_queue.reset(new ST_Queue<Chip_Read_Resp>(128));
    delayed_chip_write_req_queue.reset(new ST_Queue<Chip_Write_Req>(128));
  }
};

void gen_delay_unit_context(DelayUnitContext *context) {
  context->input_chip_read_req_with_times[0].timestamp = 0;
  context->input_chip_read_req_with_times[1].timestamp = 100;
  context->input_chip_read_req_with_times[2].timestamp = 150;

  context->input_chip_read_resp_with_times[0].timestamp = 50;
  context->input_chip_read_resp_with_times[1].timestamp = 100;
  context->input_chip_read_resp_with_times[2].timestamp = 200;

  context->input_chip_write_req_with_times[0].timestamp = 100;
  context->input_chip_write_req_with_times[1].timestamp = 150;
  context->input_chip_write_req_with_times[2].timestamp = 250;

  for (int i = 0; i < 3; i++) {
    context->input_chip_read_req_with_times[i].raw =
        RandomGen::rand_chip_read_req();
    context->input_chip_read_resp_with_times[i].raw =
        RandomGen::rand_chip_read_resp();
    context->input_chip_write_req_with_times[i].raw =
        RandomGen::rand_chip_write_req();
    context->chip_read_req_with_time_queue->write(
        context->input_chip_read_req_with_times[i]);
    context->chip_read_resp_with_time_queue->write(
        context->input_chip_read_resp_with_times[i]);
    context->chip_write_req_with_time_queue->write(
        context->input_chip_write_req_with_times[i]);
  }
}

void test_delay_unit_impl(bool use_user_defined_delay_cycles,
                          unsigned int user_defined_delay_cycles) {
  DelayUnitContext context;
  gen_delay_unit_context(&context);
  std::vector<Chip_Read_Req> result_chip_read_reqs;
  std::vector<Chip_Read_Resp> result_chip_read_resps;
  std::vector<Chip_Write_Req> result_chip_write_reqs;

  if (use_user_defined_delay_cycles) {
    context.delay_cycles_queue->write(user_defined_delay_cycles);
  } else {
    user_defined_delay_cycles = DEFAULT_DELAY_CYCLES;
  }
  RUN_METHOD(user_defined_delay_cycles, INVOKE_DELAY_UNIT_IMPL(context));
  drain_queue(context.delayed_chip_read_resp_queue.get(),
              &result_chip_read_resps);
  ASSERT_EQ(result_chip_read_resps.size(), 0);
  drain_queue(context.delayed_chip_read_req_queue.get(),
              &result_chip_read_reqs);
  ASSERT_EQ(result_chip_read_reqs.size(), 0);
  drain_queue(context.delayed_chip_write_req_queue.get(),
              &result_chip_write_reqs);
  ASSERT_EQ(result_chip_write_reqs.size(), 0);

  RUN_METHOD(1, INVOKE_DELAY_UNIT_IMPL(context));
  drain_queue(context.delayed_chip_read_req_queue.get(),
              &result_chip_read_reqs);
  ASSERT_EQ(result_chip_read_reqs.size(), 1);
  result_chip_read_reqs.clear();

  RUN_METHOD(49, INVOKE_DELAY_UNIT_IMPL(context));
  drain_queue(context.delayed_chip_read_resp_queue.get(),
              &result_chip_read_resps);
  ASSERT_EQ(result_chip_read_resps.size(), 0);

  RUN_METHOD(1, INVOKE_DELAY_UNIT_IMPL(context));
  drain_queue(context.delayed_chip_read_resp_queue.get(),
              &result_chip_read_resps);
  ASSERT_EQ(result_chip_read_resps.size(), 1);
  result_chip_read_resps.clear();

  RUN_METHOD(49, INVOKE_DELAY_UNIT_IMPL(context));
  drain_queue(context.delayed_chip_read_resp_queue.get(),
              &result_chip_read_resps);
  ASSERT_EQ(result_chip_read_resps.size(), 0);
  drain_queue(context.delayed_chip_read_req_queue.get(),
              &result_chip_read_reqs);
  ASSERT_EQ(result_chip_read_reqs.size(), 0);
  drain_queue(context.delayed_chip_write_req_queue.get(),
              &result_chip_write_reqs);
  ASSERT_EQ(result_chip_write_reqs.size(), 0);

  RUN_METHOD(1, INVOKE_DELAY_UNIT_IMPL(context));
  drain_queue(context.delayed_chip_read_resp_queue.get(),
              &result_chip_read_resps);
  ASSERT_EQ(result_chip_read_resps.size(), 1);
  result_chip_read_resps.clear();
  drain_queue(context.delayed_chip_read_req_queue.get(),
              &result_chip_read_reqs);
  ASSERT_EQ(result_chip_read_reqs.size(), 1);
  result_chip_read_reqs.clear();
  drain_queue(context.delayed_chip_write_req_queue.get(),
              &result_chip_write_reqs);
  ASSERT_EQ(result_chip_write_reqs.size(), 1);
  result_chip_write_reqs.clear();

  RUN_METHOD(49, INVOKE_DELAY_UNIT_IMPL(context));
  drain_queue(context.delayed_chip_read_req_queue.get(),
              &result_chip_read_reqs);
  ASSERT_EQ(result_chip_read_reqs.size(), 0);
  drain_queue(context.delayed_chip_write_req_queue.get(),
              &result_chip_write_reqs);
  ASSERT_EQ(result_chip_write_reqs.size(), 0);

  RUN_METHOD(1, INVOKE_DELAY_UNIT_IMPL(context));
  drain_queue(context.delayed_chip_read_req_queue.get(),
              &result_chip_read_reqs);
  ASSERT_EQ(result_chip_read_reqs.size(), 1);
  result_chip_read_reqs.clear();
  drain_queue(context.delayed_chip_write_req_queue.get(),
              &result_chip_write_reqs);
  ASSERT_EQ(result_chip_write_reqs.size(), 1);
  result_chip_write_reqs.clear();

  RUN_METHOD(49, INVOKE_DELAY_UNIT_IMPL(context));
  drain_queue(context.delayed_chip_read_resp_queue.get(),
              &result_chip_read_resps);
  ASSERT_EQ(result_chip_read_resps.size(), 0);

  RUN_METHOD(1, INVOKE_DELAY_UNIT_IMPL(context));
  drain_queue(context.delayed_chip_read_resp_queue.get(),
              &result_chip_read_resps);
  ASSERT_EQ(result_chip_read_resps.size(), 1);
  result_chip_read_resps.clear();

  RUN_METHOD(49, INVOKE_DELAY_UNIT_IMPL(context));
  drain_queue(context.delayed_chip_write_req_queue.get(),
              &result_chip_write_reqs);
  ASSERT_EQ(result_chip_write_reqs.size(), 0);

  RUN_METHOD(1, INVOKE_DELAY_UNIT_IMPL(context));
  drain_queue(context.delayed_chip_write_req_queue.get(),
              &result_chip_write_reqs);
  ASSERT_EQ(result_chip_write_reqs.size(), 1);
  result_chip_write_reqs.clear();
}

TEST(delay_unit_impl, use_user_defined_delay_cycles) {
  test_delay_unit_impl(true, 10);
}

TEST(delay_unit_impl, use_default_delay_cycles) {
  test_delay_unit_impl(false, 0);
}
