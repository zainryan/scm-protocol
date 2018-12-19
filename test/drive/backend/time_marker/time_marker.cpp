#include <cstdlib>
#include <memory>
#include <vector>

#include "gtest/gtest.h"
#include "test_params.hpp"
#include "test_utils.hpp"
#include "time_marker.hpp"

#define INVOKE_TIME_MARKER_IMPL(context)                                     \
  time_marker_impl(                                                          \
      &context.timestamp, &context.valid_chip_read_req,                      \
      &context.valid_chip_read_resp, &context.valid_chip_write_req,          \
      &context.data_chip_read_req, &context.data_chip_read_resp,             \
      &context.data_chip_write_req, &context.valid_timestamp_chip_read_req,  \
      &context.valid_timestamp_chip_read_resp,                               \
      &context.valid_timestamp_chip_write_req,                               \
      &context.data_timestamp_chip_read_req,                                 \
      &context.data_timestamp_chip_read_resp,                                \
      &context.data_timestamp_chip_write_req,                                \
      context.chip_read_req_queue.get(), context.chip_read_resp_queue.get(), \
      context.chip_write_req_queue.get(),                                    \
      context.chip_read_req_with_time_queue.get(),                           \
      context.chip_read_resp_with_time_queue.get(),                          \
      context.chip_write_req_with_time_queue.get())

struct TimeMarkerContext {
  unsigned long long timestamp = 0;
  bool valid_chip_read_req = false;
  bool valid_chip_read_resp = false;
  bool valid_chip_write_req = false;
  Chip_Read_Req data_chip_read_req;
  Chip_Read_Resp data_chip_read_resp;
  Chip_Write_Req data_chip_write_req;
  bool valid_timestamp_chip_read_req = false;
  bool valid_timestamp_chip_read_resp = false;
  bool valid_timestamp_chip_write_req = false;
  unsigned long long data_timestamp_chip_read_req;
  unsigned long long data_timestamp_chip_read_resp;
  unsigned long long data_timestamp_chip_write_req;
  std::unique_ptr<ST_Queue<Chip_Read_Req>> chip_read_req_queue;
  std::unique_ptr<ST_Queue<Chip_Read_Resp>> chip_read_resp_queue;
  std::unique_ptr<ST_Queue<Chip_Write_Req>> chip_write_req_queue;
  std::unique_ptr<ST_Queue<Chip_Read_Req_With_Time>>
      chip_read_req_with_time_queue;
  std::unique_ptr<ST_Queue<Chip_Read_Resp_With_Time>>
      chip_read_resp_with_time_queue;
  std::unique_ptr<ST_Queue<Chip_Write_Req_With_Time>>
      chip_write_req_with_time_queue;

  TimeMarkerContext() {
    chip_read_req_queue.reset(new ST_Queue<Chip_Read_Req>(128));
    chip_read_resp_queue.reset(new ST_Queue<Chip_Read_Resp>(128));
    chip_write_req_queue.reset(new ST_Queue<Chip_Write_Req>(128));
    chip_read_req_with_time_queue.reset(
        new ST_Queue<Chip_Read_Req_With_Time>(128));
    chip_read_resp_with_time_queue.reset(
        new ST_Queue<Chip_Read_Resp_With_Time>(128));
    chip_write_req_with_time_queue.reset(
        new ST_Queue<Chip_Write_Req_With_Time>(128));
  }
};

TEST(time_marker_impl, correct) {
  TimeMarkerContext context;
  Chip_Read_Req expected_chip_read_reqs[4];
  Chip_Read_Resp expected_chip_read_resps[4];
  Chip_Write_Req expected_chip_write_reqs[4];

  for (int i = 0; i < 4; i++) {
    expected_chip_read_reqs[i] = RandomGen::rand_chip_read_req();
    expected_chip_read_resps[i] = RandomGen::rand_chip_read_resp();
    expected_chip_write_reqs[i] = RandomGen::rand_chip_write_req();
    context.chip_read_req_queue->write(expected_chip_read_reqs[i]);
    context.chip_read_resp_queue->write(expected_chip_read_resps[i]);
    context.chip_write_req_queue->write(expected_chip_write_reqs[i]);
  }
  RUN_METHOD(4, INVOKE_TIME_MARKER_IMPL(context));

  std::vector<Chip_Read_Req_With_Time> real_chip_read_req_with_times;
  std::vector<Chip_Read_Resp_With_Time> real_chip_read_resp_with_times;
  std::vector<Chip_Write_Req_With_Time> real_chip_write_req_with_times;
  drain_queue(context.chip_read_req_with_time_queue.get(),
              &real_chip_read_req_with_times);
  drain_queue(context.chip_read_resp_with_time_queue.get(),
              &real_chip_read_resp_with_times);
  drain_queue(context.chip_write_req_with_time_queue.get(),
              &real_chip_write_req_with_times);
  ASSERT_EQ(real_chip_read_req_with_times.size(), 4);
  ASSERT_EQ(real_chip_read_resp_with_times.size(), 4);
  ASSERT_EQ(real_chip_write_req_with_times.size(), 4);
  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(real_chip_read_req_with_times[i].timestamp, i);
    EXPECT_EQ(real_chip_read_resp_with_times[i].timestamp, i);
    EXPECT_EQ(real_chip_write_req_with_times[i].timestamp, i);
    EXPECT_EQ(real_chip_read_req_with_times[i].raw, expected_chip_read_reqs[i]);
    EXPECT_EQ(real_chip_read_resp_with_times[i].raw,
              expected_chip_read_resps[i]);
    EXPECT_EQ(real_chip_write_req_with_times[i].raw,
              expected_chip_write_reqs[i]);
    EXPECT_EQ(real_chip_write_req_with_times[i].raw,
              expected_chip_write_reqs[i]);
  }

  RUN_METHOD(10, INVOKE_TIME_MARKER_IMPL(context));

  for (int i = 0; i < 4; i++) {
    expected_chip_read_reqs[i] = RandomGen::rand_chip_read_req();
    expected_chip_read_resps[i] = RandomGen::rand_chip_read_resp();
    expected_chip_write_reqs[i] = RandomGen::rand_chip_write_req();
    context.chip_read_req_queue->write(expected_chip_read_reqs[i]);
    context.chip_read_resp_queue->write(expected_chip_read_resps[i]);
    context.chip_write_req_queue->write(expected_chip_write_reqs[i]);
  }
  RUN_METHOD(4, INVOKE_TIME_MARKER_IMPL(context));
  real_chip_read_req_with_times.clear();
  real_chip_read_resp_with_times.clear();
  real_chip_write_req_with_times.clear();
  drain_queue(context.chip_read_req_with_time_queue.get(),
              &real_chip_read_req_with_times);
  drain_queue(context.chip_read_resp_with_time_queue.get(),
              &real_chip_read_resp_with_times);
  drain_queue(context.chip_write_req_with_time_queue.get(),
              &real_chip_write_req_with_times);
  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(real_chip_read_req_with_times[i].timestamp, 14 + i);
    EXPECT_EQ(real_chip_read_resp_with_times[i].timestamp, 14 + i);
    EXPECT_EQ(real_chip_write_req_with_times[i].timestamp, 14 + i);
    EXPECT_EQ(real_chip_read_req_with_times[i].raw, expected_chip_read_reqs[i]);
    EXPECT_EQ(real_chip_read_resp_with_times[i].raw,
              expected_chip_read_resps[i]);
    EXPECT_EQ(real_chip_write_req_with_times[i].raw,
              expected_chip_write_reqs[i]);
    EXPECT_EQ(real_chip_write_req_with_times[i].raw,
              expected_chip_write_reqs[i]);
  }
}
