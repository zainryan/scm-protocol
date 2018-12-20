#include "time_marker.hpp"

void time_marker_0(
    ST_Queue<Chip_Read_Req> *chip_read_req_queue,
    ST_Queue<Chip_Read_Resp> *chip_read_resp_queue,
    ST_Queue<Chip_Write_Req> *chip_write_req_queue,
    ST_Queue<Chip_Read_Req_With_Time> *chip_read_req_with_time_queue,
    ST_Queue<Chip_Read_Resp_With_Time> *chip_read_resp_with_time_queue,
    ST_Queue<Chip_Write_Req_With_Time> *chip_write_req_with_time_queue) {
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

  while (1) {
#pragma HLS pipeline
    time_marker_impl(
        &timestamp, &valid_chip_read_req, &valid_chip_read_resp,
        &valid_chip_write_req, &data_chip_read_req, &data_chip_read_resp,
        &data_chip_write_req, &valid_timestamp_chip_read_req,
        &valid_timestamp_chip_read_resp, &valid_timestamp_chip_write_req,
        &data_timestamp_chip_read_req, &data_timestamp_chip_read_resp,
        &data_timestamp_chip_write_req, chip_read_req_queue,
        chip_read_resp_queue, chip_write_req_queue,
        chip_read_req_with_time_queue, chip_read_resp_with_time_queue,
        chip_write_req_with_time_queue);
  }
}
