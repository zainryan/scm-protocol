#include "delay_unit.hpp"

void delay_unit_1(
    ST_Queue<unsigned int> *delay_cycles_queue,
    ST_Queue<Chip_Read_Req_With_Time> *chip_read_req_with_time_queue,
    ST_Queue<Chip_Read_Resp_With_Time> *chip_read_resp_with_time_queue,
    ST_Queue<Chip_Write_Req_With_Time> *chip_write_req_with_time_queue,
    ST_Queue<Chip_Read_Req> *delayed_chip_read_req_queue,
    ST_Queue<Chip_Read_Resp> *delayed_chip_read_resp_queue,
    ST_Queue<Chip_Write_Req> *delayed_chip_write_req_queue) {
  unsigned long long timestamp = 0;
  unsigned int delay_cycles = DEFAULT_DELAY_CYCLES;
  bool valid_chip_read_req_with_time = false;
  bool valid_chip_read_resp_with_time = false;
  bool valid_chip_write_req_with_time = false;
  Chip_Read_Req_With_Time data_chip_read_req_with_time;
  Chip_Read_Resp_With_Time data_chip_read_resp_with_time;
  Chip_Write_Req_With_Time data_chip_write_req_with_time;

  while (1) {
#pragma HLS pipeline
    delay_unit_impl(
        &timestamp, &delay_cycles, &valid_chip_read_req_with_time,
        &valid_chip_read_resp_with_time, &valid_chip_write_req_with_time,
        &data_chip_read_req_with_time, &data_chip_read_resp_with_time,
        &data_chip_write_req_with_time, delay_cycles_queue,
        chip_read_req_with_time_queue, chip_read_resp_with_time_queue,
        chip_write_req_with_time_queue, delayed_chip_read_req_queue,
        delayed_chip_read_resp_queue, delayed_chip_write_req_queue);
  }
}
