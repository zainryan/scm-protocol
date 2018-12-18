#include <cstdlib>
#include <vector>

#include "gtest/gtest.h"
#include "poke_handler.hpp"
#include "test_params.hpp"
#include "test_utils.hpp"

TEST(poke_handler_impl, correct) {
  ST_Queue<Poke_Info> poke_info_queue(8);
  ST_Queue<unsigned int> throttle_ratio_queue(8);
  ST_Queue<unsigned int> delay_cycles_queue(8);

  Poke_Info info_0;
  info_0.tag = Tag::THROTTLE_RATIO_TAG;
  info_0.data = 1;
  poke_info_queue.write(info_0);
  Poke_Info info_1;
  info_1.tag = Tag::THROTTLE_RATIO_TAG;
  info_1.data = 2;
  poke_info_queue.write(info_1);
  Poke_Info info_2;
  info_2.tag = Tag::DELAY_CYCLES_TAG;
  info_2.data = 3;
  poke_info_queue.write(info_2);
  Poke_Info info_3;
  info_3.tag = Tag::NEXT_TAG_TO_USE;
  info_3.data = 3;
  poke_info_queue.write(info_3);
  Poke_Info info_4;
  info_4.tag = Tag::THROTTLE_RATIO_TAG;
  info_4.data = 4;
  poke_info_queue.write(info_4);
  Poke_Info info_5;
  info_5.tag = Tag::DELAY_CYCLES_TAG;
  info_5.data = 2;
  poke_info_queue.write(info_5);

  RUN_METHOD(6, poke_handler_impl(&poke_info_queue, &throttle_ratio_queue,
                                  &delay_cycles_queue));
  std::vector<unsigned int> real_throttle_ratios;
  std::vector<unsigned int> real_delay_cycles;
  drain_queue(&throttle_ratio_queue, &real_throttle_ratios);
  drain_queue(&delay_cycles_queue, &real_delay_cycles);

  ASSERT_EQ(real_throttle_ratios.size(), 3);
  EXPECT_EQ(real_throttle_ratios[0], info_0.data);
  EXPECT_EQ(real_throttle_ratios[1], info_1.data);
  EXPECT_EQ(real_throttle_ratios[2], info_4.data);

  ASSERT_EQ(real_delay_cycles.size(), 2);
  EXPECT_EQ(real_delay_cycles[0], info_2.data);
  EXPECT_EQ(real_delay_cycles[1], info_5.data);
}
