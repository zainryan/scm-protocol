#pragma once

#include "chip.h"
#include "cmd.h"
#include "staccel_type.h"

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
                  ST_Queue<Chip_Write_Req> *throttled_chip_write_req_3_queue);
