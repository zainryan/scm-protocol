#include <cstdlib>
#include <memory>
#include <vector>

#include "gtest/gtest.h"
#include "test_params.hpp"
#include "test_utils.hpp"
#include "time_marker.hpp"

#define INVOKE_TIME_MARKER_IMPL(context)                           \
  time_marker_impl(context.chip_read_req_queue.get(),              \
    context.chip_read_resp_queue.get(),                            \
    context.chip_write_req_queue.get(),                            \
    context.chip_read_req_with_time_queue.get(),                   \
    context.chip_read_resp_with_time_queue.get(),                  \
    context.chip_write_req_with_time_queue.get())

struct TimeMarkerContext {
  std::unique_ptr<ST_Queue<Chip_Read_Req>> chip_read_req_queue;
  std::unique_ptr<ST_Queue<Chip_Read_Resp>> chip_read_resp_queue;
  std::unique_ptr<ST_Queue<Chip_Write_Req>> chip_write_req_queue;
  std::unique_ptr<ST_Queue<Chip_Read_Req_With_Time>> chip_read_req_with_time_queue;
  std::unique_ptr<ST_Queue<Chip_Read_Resp_With_Time>> chip_read_resp_with_time_queue;
  std::unique_ptr<ST_Queue<Chip_Write_Req_With_Time>> chip_write_req_with_time_queue;

  TimeMarkerContext() {
    chip_read_req_queue.reset(new ST_Queue<Chip_Read_Req>(128));
    chip_read_resp_queue.reset(new ST_Queue<Chip_Read_Resp>(128));
    chip_write_req_queue.reset(new ST_Queue<Chip_Write_Req>(128));
    chip_read_req_with_time_queue.reset(new ST_Queue<Chip_Read_Req_With_Time>(128));
    chip_read_resp_with_time_queue.reset(new ST_Queue<Chip_Read_Resp_With_Time>(128));
    chip_write_req_with_time_queue.reset(new ST_Queue<Chip_Write_Req_With_Time>(128));
  }
};

inline unsigned long long rand_u_long_long() {
  unsigned long long ret;
  ret = rand();
  ret <<= 32;
  ret |= rand();
  return ret;
}

inline ap_uint<512> rand_ap_uint_512() {
  ap_uint<512> data;
  for (int i = 0; i < 512; i += 32) {
    data(i + 31, i) = rand();
  }
  return data;
}

inline Chip_Read_Req rand_chip_read_req() {
  Chip_Read_Req req;
  req.addr = rand_u_long_long();
  return req;
}

inline Chip_Read_Resp rand_chip_read_resp() {
  Chip_Read_Resp resp;
  resp.data = rand_ap_uint_512();
  return resp;
}

inline Chip_Write_Req rand_chip_write_req() {
  Chip_Write_Req req;
  req.addr = rand_u_long_long();
  req.data = rand_ap_uint_512();
  return req;
}

TEST(time_marker_impl, correct) {
  TimeMarkerContext context;
  Chip_Read_Req expected_chip_read_reqs[4];
  Chip_Read_Resp expected_chip_read_resps[4];
  Chip_Write_Req expected_chip_write_reqs[4];

  for (int i = 0; i < 4; i++) {
    expected_chip_read_reqs[i] = rand_chip_read_req();
    expected_chip_read_resps[i] = rand_chip_read_resp();
    expected_chip_write_reqs[i] = rand_chip_write_req();
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
    EXPECT_EQ(real_chip_read_req_with_times[i].raw.addr, expected_chip_read_reqs[i].addr);
    EXPECT_EQ(real_chip_read_resp_with_times[i].raw.data, expected_chip_read_resps[i].data);
    EXPECT_EQ(real_chip_write_req_with_times[i].raw.addr, expected_chip_write_reqs[i].addr);
    EXPECT_EQ(real_chip_write_req_with_times[i].raw.data, expected_chip_write_reqs[i].data);
  }

  RUN_METHOD(10, INVOKE_TIME_MARKER_IMPL(context));

  for (int i = 0; i < 4; i++) {
    expected_chip_read_reqs[i] = rand_chip_read_req();
    expected_chip_read_resps[i] = rand_chip_read_resp();
    expected_chip_write_reqs[i] = rand_chip_write_req();
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
    EXPECT_EQ(real_chip_read_req_with_times[i].raw.addr, expected_chip_read_reqs[i].addr);
    EXPECT_EQ(real_chip_read_resp_with_times[i].raw.data, expected_chip_read_resps[i].data);
    EXPECT_EQ(real_chip_write_req_with_times[i].raw.addr, expected_chip_write_reqs[i].addr);
    EXPECT_EQ(real_chip_write_req_with_times[i].raw.data, expected_chip_write_reqs[i].data);
  }
}
