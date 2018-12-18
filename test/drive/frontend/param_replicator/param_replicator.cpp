#include <cstdlib>
#include <memory>
#include <vector>

#include "gtest/gtest.h"
#include "param_replicator.hpp"
#include "test_params.hpp"
#include "test_utils.hpp"

TEST(param_replicator_impl, correct) {
  const int NUM_ENTRIES = 8;

  ST_Queue<unsigned int> throttle_ratio_queue(NUM_ENTRIES);
  ST_Queue<unsigned int> throttle_ratio_0_queue(NUM_ENTRIES);
  ST_Queue<unsigned int> throttle_ratio_1_queue(NUM_ENTRIES);
  ST_Queue<unsigned int> throttle_ratio_2_queue(NUM_ENTRIES);
  ST_Queue<unsigned int> throttle_ratio_3_queue(NUM_ENTRIES);
  ST_Queue<unsigned int> delay_cycles_queue(NUM_ENTRIES);
  ST_Queue<unsigned int> delay_cycles_0_queue(NUM_ENTRIES);
  ST_Queue<unsigned int> delay_cycles_1_queue(NUM_ENTRIES);
  ST_Queue<unsigned int> delay_cycles_2_queue(NUM_ENTRIES);
  ST_Queue<unsigned int> delay_cycles_3_queue(NUM_ENTRIES);

  unsigned int expected_throttle_ratios[NUM_ENTRIES];
  unsigned int expected_delay_cycles[NUM_ENTRIES];

  for (int i = 0; i < NUM_ENTRIES; i++) {
    expected_throttle_ratios[i] = RandomGen::rand_u_int();
    expected_delay_cycles[i] = RandomGen::rand_u_int();
    throttle_ratio_queue.write(expected_throttle_ratios[i]);
    delay_cycles_queue.write(expected_delay_cycles[i]);
  }

  RUN_METHOD(NUM_ENTRIES, param_replicator_impl(
                              &throttle_ratio_queue, &throttle_ratio_0_queue,
                              &throttle_ratio_1_queue, &throttle_ratio_2_queue,
                              &throttle_ratio_3_queue, &delay_cycles_queue,
                              &delay_cycles_0_queue, &delay_cycles_1_queue,
                              &delay_cycles_2_queue, &delay_cycles_3_queue));

  std::vector<unsigned int> real_throttle_ratios[4];
  std::vector<unsigned int> real_delay_cycles[4];

  drain_queue(&throttle_ratio_0_queue, &real_throttle_ratios[0]);
  drain_queue(&throttle_ratio_1_queue, &real_throttle_ratios[1]);
  drain_queue(&throttle_ratio_2_queue, &real_throttle_ratios[2]);
  drain_queue(&throttle_ratio_3_queue, &real_throttle_ratios[3]);
  drain_queue(&delay_cycles_0_queue, &real_delay_cycles[0]);
  drain_queue(&delay_cycles_1_queue, &real_delay_cycles[1]);
  drain_queue(&delay_cycles_2_queue, &real_delay_cycles[2]);
  drain_queue(&delay_cycles_3_queue, &real_delay_cycles[3]);

  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(real_throttle_ratios[i].size(), NUM_ENTRIES);
    ASSERT_EQ(real_delay_cycles[i].size(), NUM_ENTRIES);
    for (int j = 0; j < NUM_ENTRIES; j++) {
      EXPECT_EQ(real_throttle_ratios[i][j], expected_throttle_ratios[j]);
      EXPECT_EQ(real_delay_cycles[i][j], expected_delay_cycles[j]);
    }
  }
}
