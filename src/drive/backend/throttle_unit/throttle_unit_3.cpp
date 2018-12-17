#include "throttle_unit.hpp"

void throttle_unit_3(ST_Queue<unsigned int> *throttle_ratio_queue,
                     ST_Queue<Chip_Read_Req> *chip_read_req_queue,
                     ST_Queue<Chip_Read_Resp> *chip_read_resp_queue,
                     ST_Queue<Chip_Write_Req> *chip_write_req_queue,
                     ST_Queue<Chip_Read_Req> *throttled_chip_read_req_queue,
                     ST_Queue<Chip_Read_Resp> *throttled_chip_read_resp_queue,
                     ST_Queue<Chip_Write_Req> *throttled_chip_write_req_queue) {
  while (1) {
#pragma HLS pipeline
    throttle_unit_impl(
        throttle_ratio_queue, chip_read_req_queue, chip_read_resp_queue,
        chip_write_req_queue, throttled_chip_read_req_queue,
        throttled_chip_read_resp_queue, throttled_chip_write_req_queue);
  }
}
