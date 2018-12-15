#include "throttle_unit.hpp"

void throttle_unit_1(ST_Queue<Chip_Read_Req> *chip_read_req,
                     ST_Queue<Chip_Read_Resp> *chip_read_resp,
                     ST_Queue<Chip_Write_Req> *chip_write_req,
                     ST_Queue<Chip_Read_Req> *throttled_chip_read_req,
                     ST_Queue<Chip_Read_Resp> *throttled_chip_read_resp,
                     ST_Queue<Chip_Write_Req> *throttled_chip_write_req) {
  bool valid_chip_read_req = false;
  bool valid_chip_read_resp = false;
  bool valid_chip_write_req = false;
  Chip_Read_Req data_chip_read_req;
  Chip_Read_Resp data_chip_read_resp;
  Chip_Write_Req data_chip_write_req;
  ap_uint<LOG2_THROTTLE_RATIO + 1> state_chip_read_resp;
  ap_uint<LOG2_THROTTLE_RATIO + 1> state_chip_write_req;
  
  while (1) {
#pragma HLS pipeline
    throttle_unit_impl(&valid_chip_read_req, &valid_chip_read_resp,
                       &valid_chip_write_req, &data_chip_read_req,
                       &data_chip_read_resp, &data_chip_write_req,
                       &state_chip_read_resp, &state_chip_write_req,
                       chip_read_req, chip_read_resp, chip_write_req,
                       throttled_chip_read_req, throttled_chip_read_resp,
                       throttled_chip_write_req);
  }
}
