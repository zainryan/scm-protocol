#include "cmd_splitter.hpp"
#include "delay_unit_0.hpp"
#include "delay_unit_1.hpp"
#include "delay_unit_2.hpp"
#include "delay_unit_3.hpp"
#include "param_replicator.hpp"
#include "pcis_handler.hpp"
#include "peek_handler.hpp"
#include "place_holder.hpp"
#include "poke_handler.hpp"
#include "staccel_itc.h"
#include "throttle_unit_0.hpp"
#include "throttle_unit_1.hpp"
#include "throttle_unit_2.hpp"
#include "throttle_unit_3.hpp"
#include "time_marker_0.hpp"
#include "time_marker_1.hpp"
#include "time_marker_2.hpp"
#include "time_marker_3.hpp"

void interconnects() {
  ST_Queue<SuperCommand> super_command_queue(128);
  ST_Queue<Command> command_queue(1024);
  ST_Queue<unsigned int> throttle_ratio_queue(8);
  ST_Queue<unsigned int> throttle_ratio_0_queue(8);
  ST_Queue<unsigned int> throttle_ratio_1_queue(8);
  ST_Queue<unsigned int> throttle_ratio_2_queue(8);
  ST_Queue<unsigned int> throttle_ratio_3_queue(8);
  ST_Queue<unsigned int> delay_cycles_queue(8);
  ST_Queue<unsigned int> delay_cycles_0_queue(8);
  ST_Queue<unsigned int> delay_cycles_1_queue(8);
  ST_Queue<unsigned int> delay_cycles_2_queue(8);
  ST_Queue<unsigned int> delay_cycles_3_queue(8);
  ST_Queue<unsigned short> return_credit_num_queue(8);
  ST_Queue<Chip_Read_Req> chip_read_req_0_queue(128);
  ST_Queue<Chip_Read_Resp> chip_read_resp_0_queue(128);
  ST_Queue<Chip_Write_Req> chip_write_req_0_queue(128);
  ST_Queue<Chip_Read_Req> chip_read_req_1_queue(128);
  ST_Queue<Chip_Read_Resp> chip_read_resp_1_queue(128);
  ST_Queue<Chip_Write_Req> chip_write_req_1_queue(128);
  ST_Queue<Chip_Read_Req> chip_read_req_2_queue(128);
  ST_Queue<Chip_Read_Resp> chip_read_resp_2_queue(128);
  ST_Queue<Chip_Write_Req> chip_write_req_2_queue(128);
  ST_Queue<Chip_Read_Req> chip_read_req_3_queue(128);
  ST_Queue<Chip_Read_Resp> chip_read_resp_3_queue(128);
  ST_Queue<Chip_Write_Req> chip_write_req_3_queue(128);
  ST_Queue<Chip_Read_Req_With_Time> chip_read_req_with_time_0_queue(128);
  ST_Queue<Chip_Read_Resp_With_Time> chip_read_resp_with_time_0_queue(128);
  ST_Queue<Chip_Write_Req_With_Time> chip_write_req_with_time_0_queue(128);
  ST_Queue<Chip_Read_Req_With_Time> chip_read_req_with_time_1_queue(128);
  ST_Queue<Chip_Read_Resp_With_Time> chip_read_resp_with_time_1_queue(128);
  ST_Queue<Chip_Write_Req_With_Time> chip_write_req_with_time_1_queue(128);
  ST_Queue<Chip_Read_Req_With_Time> chip_read_req_with_time_2_queue(128);
  ST_Queue<Chip_Read_Resp_With_Time> chip_read_resp_with_time_2_queue(128);
  ST_Queue<Chip_Write_Req_With_Time> chip_write_req_with_time_2_queue(128);
  ST_Queue<Chip_Read_Req_With_Time> chip_read_req_with_time_3_queue(128);
  ST_Queue<Chip_Read_Resp_With_Time> chip_read_resp_with_time_3_queue(128);
  ST_Queue<Chip_Write_Req_With_Time> chip_write_req_with_time_3_queue(128);
  ST_Queue<Chip_Read_Req> delayed_chip_read_req_0_queue(128);
  ST_Queue<Chip_Read_Resp> delayed_chip_read_resp_0_queue(128);
  ST_Queue<Chip_Write_Req> delayed_chip_write_req_0_queue(128);
  ST_Queue<Chip_Read_Req> delayed_chip_read_req_1_queue(128);
  ST_Queue<Chip_Read_Resp> delayed_chip_read_resp_1_queue(128);
  ST_Queue<Chip_Write_Req> delayed_chip_write_req_1_queue(128);
  ST_Queue<Chip_Read_Req> delayed_chip_read_req_2_queue(128);
  ST_Queue<Chip_Read_Resp> delayed_chip_read_resp_2_queue(128);
  ST_Queue<Chip_Write_Req> delayed_chip_write_req_2_queue(128);
  ST_Queue<Chip_Read_Req> delayed_chip_read_req_3_queue(128);
  ST_Queue<Chip_Read_Resp> delayed_chip_read_resp_3_queue(128);
  ST_Queue<Chip_Write_Req> delayed_chip_write_req_3_queue(128);
  ST_Queue<Chip_Read_Req> throttled_chip_read_req_0_queue(128);
  ST_Queue<Chip_Read_Resp> throttled_chip_read_resp_0_queue(128);
  ST_Queue<Chip_Write_Req> throttled_chip_write_req_0_queue(128);
  ST_Queue<Chip_Read_Req> throttled_chip_read_req_1_queue(128);
  ST_Queue<Chip_Read_Resp> throttled_chip_read_resp_1_queue(128);
  ST_Queue<Chip_Write_Req> throttled_chip_write_req_1_queue(128);
  ST_Queue<Chip_Read_Req> throttled_chip_read_req_2_queue(128);
  ST_Queue<Chip_Read_Resp> throttled_chip_read_resp_2_queue(128);
  ST_Queue<Chip_Write_Req> throttled_chip_write_req_2_queue(128);
  ST_Queue<Chip_Read_Req> throttled_chip_read_req_3_queue(128);
  ST_Queue<Chip_Read_Resp> throttled_chip_read_resp_3_queue(128);
  ST_Queue<Chip_Write_Req> throttled_chip_write_req_3_queue(128);

  pcis_handler(&pcis_write_req, &super_command_queue);
  cmd_splitter(&super_command_queue, &command_queue);
  poke_handler_impl(&poke, &throttle_ratio_queue, &delay_cycles_queue);
  peek_handler(&return_credit_num_queue, &peek_req, &peek_resp);
  param_replicator(&throttle_ratio_queue, &throttle_ratio_0_queue,
                   &throttle_ratio_1_queue, &throttle_ratio_2_queue,
                   &throttle_ratio_3_queue, &delay_cycles_queue,
                   &delay_cycles_0_queue, &delay_cycles_1_queue,
                   &delay_cycles_2_queue, &delay_cycles_3_queue);
  time_marker_0(&chip_read_req_0_queue, &chip_read_resp_0_queue,
                &chip_write_req_0_queue, &chip_read_req_with_time_0_queue,
                &chip_read_resp_with_time_0_queue,
                &chip_write_req_with_time_0_queue);
  time_marker_1(&chip_read_req_1_queue, &chip_read_resp_1_queue,
                &chip_write_req_1_queue, &chip_read_req_with_time_1_queue,
                &chip_read_resp_with_time_1_queue,
                &chip_write_req_with_time_1_queue);
  time_marker_2(&chip_read_req_2_queue, &chip_read_resp_2_queue,
                &chip_write_req_2_queue, &chip_read_req_with_time_2_queue,
                &chip_read_resp_with_time_2_queue,
                &chip_write_req_with_time_2_queue);
  time_marker_3(&chip_read_req_3_queue, &chip_read_resp_3_queue,
                &chip_write_req_3_queue, &chip_read_req_with_time_3_queue,
                &chip_read_resp_with_time_3_queue,
                &chip_write_req_with_time_3_queue);
  delay_unit_0(&delay_cycles_0_queue, &chip_read_req_with_time_0_queue,
               &chip_read_resp_with_time_0_queue,
               &chip_write_req_with_time_0_queue,
               &delayed_chip_read_req_0_queue, &delayed_chip_read_resp_0_queue,
               &delayed_chip_write_req_0_queue);
  delay_unit_1(&delay_cycles_1_queue, &chip_read_req_with_time_1_queue,
               &chip_read_resp_with_time_1_queue,
               &chip_write_req_with_time_1_queue,
               &delayed_chip_read_req_1_queue, &delayed_chip_read_resp_1_queue,
               &delayed_chip_write_req_1_queue);
  delay_unit_2(&delay_cycles_2_queue, &chip_read_req_with_time_2_queue,
               &chip_read_resp_with_time_2_queue,
               &chip_write_req_with_time_2_queue,
               &delayed_chip_read_req_2_queue, &delayed_chip_read_resp_2_queue,
               &delayed_chip_write_req_2_queue);
  delay_unit_3(&delay_cycles_3_queue, &chip_read_req_with_time_3_queue,
               &chip_read_resp_with_time_3_queue,
               &chip_write_req_with_time_3_queue,
               &delayed_chip_read_req_3_queue, &delayed_chip_read_resp_3_queue,
               &delayed_chip_write_req_3_queue);
  throttle_unit_0(
      &throttle_ratio_0_queue, &delayed_chip_read_req_0_queue,
      &delayed_chip_read_resp_0_queue, &delayed_chip_write_req_0_queue,
      &throttled_chip_read_req_0_queue, &throttled_chip_read_resp_0_queue,
      &throttled_chip_write_req_0_queue);
  throttle_unit_1(
      &throttle_ratio_1_queue, &delayed_chip_read_req_1_queue,
      &delayed_chip_read_resp_1_queue, &delayed_chip_write_req_1_queue,
      &throttled_chip_read_req_1_queue, &throttled_chip_read_resp_1_queue,
      &throttled_chip_write_req_1_queue);
  throttle_unit_2(
      &throttle_ratio_2_queue, &delayed_chip_read_req_2_queue,
      &delayed_chip_read_resp_2_queue, &delayed_chip_write_req_2_queue,
      &throttled_chip_read_req_2_queue, &throttled_chip_read_resp_2_queue,
      &throttled_chip_write_req_2_queue);
  throttle_unit_3(
      &throttle_ratio_3_queue, &delayed_chip_read_req_3_queue,
      &delayed_chip_read_resp_3_queue, &delayed_chip_write_req_3_queue,
      &throttled_chip_read_req_3_queue, &throttled_chip_read_resp_3_queue,
      &throttled_chip_write_req_3_queue);

  // The goal is to eliminate the place holder by implementing all the missing
  // logics.
  place_holder(
      &command_queue, &return_credit_num_queue, &chip_read_req_0_queue,
      &chip_read_resp_0_queue, &chip_write_req_0_queue, &chip_read_req_1_queue,
      &chip_read_resp_1_queue, &chip_write_req_1_queue, &chip_read_req_2_queue,
      &chip_read_resp_2_queue, &chip_write_req_2_queue, &chip_read_req_3_queue,
      &chip_read_resp_3_queue, &chip_write_req_3_queue,
      &throttled_chip_read_req_0_queue, &throttled_chip_read_resp_0_queue,
      &throttled_chip_write_req_0_queue, &throttled_chip_read_req_1_queue,
      &throttled_chip_read_resp_1_queue, &throttled_chip_write_req_1_queue,
      &throttled_chip_read_req_2_queue, &throttled_chip_read_resp_2_queue,
      &throttled_chip_write_req_2_queue, &throttled_chip_read_req_3_queue,
      &throttled_chip_read_resp_3_queue, &throttled_chip_write_req_3_queue);
}
