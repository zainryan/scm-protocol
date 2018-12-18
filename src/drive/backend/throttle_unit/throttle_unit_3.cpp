#include "throttle_unit.hpp"

void throttle_unit_3(ST_Queue<unsigned int> *throttle_ratio_queue,
                     ST_Queue<Chip_Read_Req> *chip_read_req_queue,
                     ST_Queue<Chip_Read_Resp> *chip_read_resp_queue,
                     ST_Queue<Chip_Write_Req> *chip_write_req_queue,
                     ST_Queue<Chip_Read_Req> *throttled_chip_read_req_queue,
                     ST_Queue<Chip_Read_Resp> *throttled_chip_read_resp_queue,
                     ST_Queue<Chip_Write_Req> *throttled_chip_write_req_queue) {
  bool valid_chip_read_req = false;
  bool valid_chip_read_resp = false;
  bool valid_chip_write_req = false;
  bool valid_throttle_ratio_queue = false;
  Chip_Read_Req data_chip_read_req;
  Chip_Read_Resp data_chip_read_resp;
  Chip_Write_Req data_chip_write_req;
  unsigned int throttle_ratio = DEFAULT_THROTTLE_RATIO;
  unsigned int state_chip_read_resp = 0;
  unsigned int state_chip_write_req = 0;

  while (1) {
#pragma HLS pipeline
    throttle_unit_impl(
        &valid_chip_read_req, &valid_chip_read_resp, &valid_chip_write_req,
        &valid_throttle_ratio_queue, &data_chip_read_req, &data_chip_read_resp,
        &data_chip_write_req, &throttle_ratio, &state_chip_read_resp,
        &state_chip_write_req, throttle_ratio_queue, chip_read_req_queue,
        chip_read_resp_queue, chip_write_req_queue,
        throttled_chip_read_req_queue, throttled_chip_read_resp_queue,
        throttled_chip_write_req_queue);
  }
}
