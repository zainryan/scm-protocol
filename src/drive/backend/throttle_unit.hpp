#pragma once

#include "chip.h"
#include "staccel_kernel.h"

inline void throttle_unit_impl(bool *valid_chip_read_req,
                               bool *valid_chip_read_resp,
                               bool *valid_chip_write_req,
                               Chip_Read_Req *data_chip_read_req,
                               Chip_Read_Resp *data_chip_read_resp,
                               Chip_Write_Req *data_chip_write_req,
                               ap_uint<LOG2_THROTTLE_RATIO + 1> *state_chip_read_resp,
                               ap_uint<LOG2_THROTTLE_RATIO + 1> *state_chip_write_req,
                               ST_Queue<Chip_Read_Req> *chip_read_req,
                               ST_Queue<Chip_Read_Resp> *chip_read_resp,
                               ST_Queue<Chip_Write_Req> *chip_write_req,
                               ST_Queue<Chip_Read_Req> *throttled_chip_read_req,
                               ST_Queue<Chip_Read_Resp> *throttled_chip_read_resp,
                               ST_Queue<Chip_Write_Req> *throttled_chip_write_req) {
  if (*valid_chip_read_req ||
      (*valid_chip_read_req = chip_read_req->read_nb(*data_chip_read_req))) {
    if (throttled_chip_read_req->write_nb(*data_chip_read_req)) {
      *valid_chip_read_req = false;
    }
  }

  if (*valid_chip_read_resp ||
      (*valid_chip_read_resp = chip_read_resp->read_nb(*data_chip_read_resp))) {
    (*state_chip_read_resp)++;
    if (*state_chip_read_resp >= THROTTLE_RATIO) {
      if (throttled_chip_read_resp->write_nb(*data_chip_read_resp)) {
        *valid_chip_read_resp = false;
        *state_chip_read_resp = 0;
      }
    }
  }

  if (*valid_chip_write_req ||
      (*valid_chip_write_req = chip_write_req->read_nb(*data_chip_write_req))) {
    (*state_chip_write_req)++;
    if (*state_chip_write_req >= THROTTLE_RATIO) {
      if (throttled_chip_write_req->write_nb(*data_chip_write_req)) {
        *valid_chip_write_req = false;
        *state_chip_write_req = 0;
      }
    }
  }
}