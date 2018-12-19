#include "delay_unit.hpp"

void delay_unit_2(
    ST_Queue<unsigned int> *delay_cycles_queue,
    ST_Queue<Chip_Read_Req_With_Time> *chip_read_req_with_time_queue,
    ST_Queue<Chip_Read_Resp_With_Time> *chip_read_resp_with_time_queue,
    ST_Queue<Chip_Write_Req_With_Time> *chip_write_req_with_time_queue,
    ST_Queue<Chip_Read_Req> *delayed_chip_read_req_queue,
    ST_Queue<Chip_Read_Resp> *delayed_chip_read_resp_queue,
    ST_Queue<Chip_Write_Req> *delayed_chip_write_req_queue) {
  delay_unit(delay_cycles_queue, chip_read_req_with_time_queue,
             chip_read_resp_with_time_queue, chip_write_req_with_time_queue,
             delayed_chip_read_req_queue, delayed_chip_read_resp_queue,
             delayed_chip_write_req_queue);
}
