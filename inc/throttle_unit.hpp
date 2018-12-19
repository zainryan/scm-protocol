#pragma once

#include "chip.h"
#include "staccel_kernel.h"

inline void throttle_unit_impl(
    ST_Queue<unsigned int> *throttle_ratio_queue,
    ST_Queue<Chip_Read_Req> *chip_read_req_queue,
    ST_Queue<Chip_Read_Resp> *chip_read_resp_queue,
    ST_Queue<Chip_Write_Req> *chip_write_req_queue,
    ST_Queue<Chip_Read_Req> *throttled_chip_read_req_queue,
    ST_Queue<Chip_Read_Resp> *throttled_chip_read_resp_queue,
    ST_Queue<Chip_Write_Req> *throttled_chip_write_req_queue) {
  static bool valid_chip_read_req = false;
  static bool valid_chip_read_resp = false;
  static bool valid_chip_write_req = false;
  static bool valid_throttle_ratio_queue = false;
  static Chip_Read_Req data_chip_read_req;
  static Chip_Read_Resp data_chip_read_resp;
  static Chip_Write_Req data_chip_write_req;
  static unsigned int throttle_ratio = DEFAULT_THROTTLE_RATIO;
  static unsigned int state_chip_read_resp = 0;
  static unsigned int state_chip_write_req = 0;

  unsigned int tmp_throttle_ratio;
  if (throttle_ratio_queue->read_nb(tmp_throttle_ratio)) {
    throttle_ratio = tmp_throttle_ratio;
  }

  if (valid_chip_read_req ||
      (valid_chip_read_req =
           chip_read_req_queue->read_nb(data_chip_read_req))) {
    if (throttled_chip_read_req_queue->write_nb(data_chip_read_req)) {
      valid_chip_read_req = false;
    }
  }

  if (valid_chip_read_resp ||
      (valid_chip_read_resp =
           chip_read_resp_queue->read_nb(data_chip_read_resp))) {
    state_chip_read_resp++;
    if (state_chip_read_resp >= throttle_ratio) {
      if (throttled_chip_read_resp_queue->write_nb(data_chip_read_resp)) {
        valid_chip_read_resp = false;
        state_chip_read_resp = 0;
      }
    }
  }

  if (valid_chip_write_req ||
      (valid_chip_write_req =
           chip_write_req_queue->read_nb(data_chip_write_req))) {
    state_chip_write_req++;
    if (state_chip_write_req >= throttle_ratio) {
      if (throttled_chip_write_req_queue->write_nb(data_chip_write_req)) {
        valid_chip_write_req = false;
        state_chip_write_req = 0;
      }
    }
  }
}
