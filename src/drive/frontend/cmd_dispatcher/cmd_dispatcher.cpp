#include "chip.h"
#include "cmd.h"
#include "cmd_dispatcher.hpp"
#include "staccel_kernel.h"

inline void read_req_handler(const Command &command, 
			     ST_Queue<Chip_Read_Req> *chip_read_req_queue,
			     ST_Queue<Chip_Read_Req> *chip_read_req_context
			     ) {
  Chip_Read_Req chip_read_req;
  chip_read_req.addr = (unsigned long long) command.index;
  chip_read_req_queue->write(chip_read_req);
  chip_read_req_context->write(chip_read_req);
}

//TODO: design the data input and output channel and data floorplan
inline void write_req_handler(const Command &command, 
			      const Host_Write_Data &host_write_data,
			      ST_Queue<Chip_Write_Req> *chip_write_req_queue
			      ) {
  Chip_Write_Req chip_write_req;
  chip_write_req.data = host_write_data.data;
  chip_write_req.addr = host_write_data.addr;
  chip_write_req_queue->write(chip_write_req);
}

inline void cmd_dispatcher_impl(ST_Queue<Command> *command_queue,
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
				) {
  Command command;
  Host_Write_Data host_write_data;
  if (command_queue -> read_nb(command)) {
    unsigned long long bank_id = ((unsigned long long) command.index) & 3;
    if (bank_id == 0) {
      if (command.is_read) {
        read_req_handler(command, chip_read_req_queue_0, chip_read_req_context_0);
      } else {
        if (host_write_data_queue -> read_nb(host_write_data)) {
          write_req_handler(command, host_write_data, chip_write_req_queue_0);
        }
      }        
    } else if (bank_id == 1) {
      if (command.is_read) {
        read_req_handler(command, chip_read_req_queue_1, chip_read_req_context_1);
      } else {
        if (host_write_data_queue -> read_nb(host_write_data)) {
          write_req_handler(command, host_write_data, chip_write_req_queue_1);
        }
      }
    } else if (bank_id == 2) {
      if (command.is_read) {
        read_req_handler(command, chip_read_req_queue_2, chip_read_req_context_2);
      } else {
        if (host_write_data_queue -> read_nb(host_write_data)) {
          write_req_handler(command, host_write_data, chip_write_req_queue_2);
        }
      }
    } else if (bank_id == 3) {
      if (command.is_read) {
        read_req_handler(command, chip_read_req_queue_3, chip_read_req_context_3);
      } else {
        if (host_write_data_queue -> read_nb(host_write_data)) {
          write_req_handler(command, host_write_data, chip_write_req_queue_3);
        }
      }
    }
  }
}

void cmd_dispatcher(ST_Queue<Command> *command_queue,
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
		    ) {
  while (1) {
#pragma HLS pipeline
    cmd_dispatcher_impl(command_queue, 
			host_write_data_queue,
			chip_read_req_queue_0,
			chip_read_req_context_0,
			chip_write_req_queue_0,
			chip_read_req_queue_1,
			chip_read_req_context_1,
			chip_write_req_queue_1,
			chip_read_req_queue_2,
			chip_read_req_context_2,
			chip_write_req_queue_2,
			chip_read_req_queue_3,
			chip_read_req_context_3,
			chip_write_req_queue_3
			);
  }
}
