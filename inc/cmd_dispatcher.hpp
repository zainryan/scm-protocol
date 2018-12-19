#pragma once 

#include "chip.h"
#include "staccel_type.h"

#define RD_REQ_BUF_DEPTH 32 // this should be the same depth with the chip read req queue

//TODO(@zainryan): design the data floorplan
struct Host_Write_Data {
  unsigned long long addr;
  ap_uint<512> data;
};

void cmd_dispatcher_impl(ST_Queue<Command> *command_queue,
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
			 ST_Queue<Chip_Write_Req> *chip_write_req_queue_3
			 );

void cmd_dispatcher (ST_Queue<Command> *command_queue,
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
		     ST_Queue<Chip_Write_Req> *chip_write_req_queue_3
		     );
