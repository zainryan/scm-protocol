#pragma once

#include "chip.h"
#include "cmd.h"
#include "staccel_type.h"

#define RD_REQ_BUF_DEPTH (32)
#define UNIT_CHUCK_SIZE_IN_BYTE (64)

void cmd_dispatcher_impl(ST_Queue<Unit_Command> *unit_command_queue,
                         ST_Queue<Host_Write_Data> *host_write_data_queue,
                         ST_Queue<Chip_Read_Req> *chip_read_req_queue_0,
                         ST_Queue<Chip_Read_Req> *chip_read_req_context_0,
                         ST_Queue<Chip_Write_Req> *chip_write_req_queue_0,
                         ST_Queue<Chip_Read_Req> *chip_read_req_queue_1,
                         ST_Queue<Chip_Read_Req> *chip_read_req_context_1,
                         ST_Queue<Chip_Write_Req> *chip_write_req_queue_1,
                         ST_Queue<Chip_Read_Req> *chip_read_req_queue_2,
                         ST_Queue<Chip_Read_Req> *chip_read_req_context_2,
                         ST_Queue<Chip_Write_Req> *chip_write_req_queue_2,
                         ST_Queue<Chip_Read_Req> *chip_read_req_queue_3,
                         ST_Queue<Chip_Read_Req> *chip_read_req_context_3,
                         ST_Queue<Chip_Write_Req> *chip_write_req_queue_3);

void cmd_dispatcher(ST_Queue<Unit_Command> *unit_command_queue,
                    ST_Queue<Host_Write_Data> host_write_data_queue,
                    ST_Queue<Chip_Read_Req> *chip_read_req_queue_0,
                    ST_Queue<Chip_Read_Req> *chip_read_req_context_0,
                    ST_Queue<Chip_Write_Req> *chip_write_req_queue_0,
                    ST_Queue<Chip_Read_Req> *chip_read_req_queue_1,
                    ST_Queue<Chip_Read_Req> *chip_read_req_context_1,
                    ST_Queue<Chip_Write_Req> *chip_write_req_queue_1,
                    ST_Queue<Chip_Read_Req> *chip_read_req_queue_2,
                    ST_Queue<Chip_Read_Req> *chip_read_req_context_2,
                    ST_Queue<Chip_Write_Req> *chip_write_req_queue_2,
                    ST_Queue<Chip_Read_Req> *chip_read_req_queue_3,
                    ST_Queue<Chip_Read_Req> *chip_read_req_context_3,
                    ST_Queue<Chip_Write_Req> *chip_write_req_queue_3);
