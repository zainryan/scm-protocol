#include "time_marker.hpp"

void time_marker_2(
    ST_Queue<Chip_Read_Req> *chip_read_req_queue,
    ST_Queue<Chip_Read_Resp> *chip_read_resp_queue,
    ST_Queue<Chip_Write_Req> *chip_write_req_queue,
    ST_Queue<Chip_Read_Req_With_Time> *chip_read_req_with_time_queue,
    ST_Queue<Chip_Read_Resp_With_Time> *chip_read_resp_with_time_queue,
    ST_Queue<Chip_Write_Req_With_Time> *chip_write_req_with_time_queue) {
  time_marker(chip_read_req_queue, chip_read_resp_queue, chip_write_req_queue,
              chip_read_req_with_time_queue, chip_read_resp_with_time_queue,
              chip_write_req_with_time_queue);
}
