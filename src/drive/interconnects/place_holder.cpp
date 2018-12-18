#include "place_holder.hpp"

void place_holder(ST_Queue<Command> *command_queue,
                  ST_Queue<unsigned short> *return_credit_num_queue,
                  ST_Queue<Chip_Read_Req> *chip_read_req_0_queue,
                  ST_Queue<Chip_Read_Resp> *chip_read_resp_0_queue,
                  ST_Queue<Chip_Write_Req> *chip_write_req_0_queue,
                  ST_Queue<Chip_Read_Req> *chip_read_req_1_queue,
                  ST_Queue<Chip_Read_Resp> *chip_read_resp_1_queue,
                  ST_Queue<Chip_Write_Req> *chip_write_req_1_queue,
                  ST_Queue<Chip_Read_Req> *chip_read_req_2_queue,
                  ST_Queue<Chip_Read_Resp> *chip_read_resp_2_queue,
                  ST_Queue<Chip_Write_Req> *chip_write_req_2_queue,
                  ST_Queue<Chip_Read_Req> *chip_read_req_3_queue,
                  ST_Queue<Chip_Read_Resp> *chip_read_resp_3_queue,
                  ST_Queue<Chip_Write_Req> *chip_write_req_3_queue,
                  ST_Queue<Chip_Read_Req> *throttled_chip_read_req_0_queue,
                  ST_Queue<Chip_Read_Resp> *throttled_chip_read_resp_0_queue,
                  ST_Queue<Chip_Write_Req> *throttled_chip_write_req_0_queue,
                  ST_Queue<Chip_Read_Req> *throttled_chip_read_req_1_queue,
                  ST_Queue<Chip_Read_Resp> *throttled_chip_read_resp_1_queue,
                  ST_Queue<Chip_Write_Req> *throttled_chip_write_req_1_queue,
                  ST_Queue<Chip_Read_Req> *throttled_chip_read_req_2_queue,
                  ST_Queue<Chip_Read_Resp> *throttled_chip_read_resp_2_queue,
                  ST_Queue<Chip_Write_Req> *throttled_chip_write_req_2_queue,
                  ST_Queue<Chip_Read_Req> *throttled_chip_read_req_3_queue,
                  ST_Queue<Chip_Read_Resp> *throttled_chip_read_resp_3_queue,
                  ST_Queue<Chip_Write_Req> *throttled_chip_write_req_3_queue) {
  Command dummy_command;
  command_queue->read(dummy_command);
  return_credit_num_queue->write(0);
  Chip_Read_Req dummy_chip_read_req;
  chip_read_req_0_queue->write(dummy_chip_read_req);
  chip_read_req_1_queue->write(dummy_chip_read_req);
  chip_read_req_2_queue->write(dummy_chip_read_req);
  chip_read_req_3_queue->write(dummy_chip_read_req);
  Chip_Read_Resp dummy_chip_read_resp;
  chip_read_resp_0_queue->write(dummy_chip_read_resp);
  chip_read_resp_1_queue->write(dummy_chip_read_resp);
  chip_read_resp_2_queue->write(dummy_chip_read_resp);
  chip_read_resp_3_queue->write(dummy_chip_read_resp);
  Chip_Write_Req dummy_chip_write_req;
  chip_write_req_0_queue->write(dummy_chip_write_req);
  chip_write_req_1_queue->write(dummy_chip_write_req);
  chip_write_req_2_queue->write(dummy_chip_write_req);
  chip_write_req_3_queue->write(dummy_chip_write_req);
  throttled_chip_read_req_0_queue->read(dummy_chip_read_req);
  throttled_chip_read_req_1_queue->read(dummy_chip_read_req);
  throttled_chip_read_req_2_queue->read(dummy_chip_read_req);
  throttled_chip_read_req_3_queue->read(dummy_chip_read_req);
  throttled_chip_read_resp_0_queue->read(dummy_chip_read_resp);
  throttled_chip_read_resp_1_queue->read(dummy_chip_read_resp);
  throttled_chip_read_resp_2_queue->read(dummy_chip_read_resp);
  throttled_chip_read_resp_3_queue->read(dummy_chip_read_resp);
  throttled_chip_write_req_0_queue->read(dummy_chip_write_req);
  throttled_chip_write_req_1_queue->read(dummy_chip_write_req);
  throttled_chip_write_req_2_queue->read(dummy_chip_write_req);
  throttled_chip_write_req_3_queue->read(dummy_chip_write_req);
}
