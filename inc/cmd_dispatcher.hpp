#pragma once 

#include "chip.h"
#include "staccel_type.h"

#define RD_REQ_BUF_DEPTH 32 // this should be the same depth with the chip read req queue

//TODO: design the data floorplan
struct Host_Write_Data {
  unsigned long long addr;
  ap_uint<512> data;
};

//TODO: design the data floorplan
struct Chip_Write_Data {
  ap_uint<512> data;
};

inline void read_req_handler (const Command &command, 
    ST_Queue<Chip_Read_Req> *chip_read_req_queue,
    ST_Queue<Chip_Read_Req> *chip_read_req_context
    ) {
  Chip_Read_Req chip_read_req;
  chip_read_req.addr = (unsigned long long) command.index;
  chip_read_req_queue -> write(chip_read_req);
  chip_read_req_context -> write(chip_read_req);
}

//TODO: design the data input and output channel and data floorplan
inline void write_req_handler (const Command &command, 
    const Host_Write_Data &host_write_data,
    ST_Queue<Chip_Write_Req> *chip_write_req_queue
    ) {
  Chip_Write_Req chip_write_req;
  Chip_Write_Data chip_write_data;
  chip_write_req.data = host_write_data.data;
  chip_write_req.addr = host_write_data.addr;
  chip_write_req_queue -> write(chip_write_req);
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
    unsigned long long bankId = ((unsigned long long) command.index) % 4;
    if (bankId == 0) {
      if (command.is_read) {
        read_req_handler(command, chip_read_req_queue_0, chip_read_req_context_0);
      }
      else {
        // TODO: write logic
        if (host_write_data_queue -> read_nb(host_write_data)) {
          write_req_handler(command, host_write_data, chip_write_req_queue_0);
        }
      }        
    }
    else if (bankId == 1) {
      if (command.is_read) {
        read_req_handler(command, chip_read_req_queue_1, chip_read_req_context_1);
      }
      else {
        // write logic
        if (host_write_data_queue -> read_nb(host_write_data)) {
          write_req_handler(command, host_write_data, chip_write_req_queue_1);
        }
      }
    }
    else if (bankId == 2) {
      if (command.is_read) {
        read_req_handler(command, chip_read_req_queue_2, chip_read_req_context_2);
      }
      else {
        // write logic
        if (host_write_data_queue -> read_nb(host_write_data)) {
          write_req_handler(command, host_write_data, chip_write_req_queue_2);
        }
      }
    }
    else if (bankId == 3) {
      if (command.is_read) {
        read_req_handler(command, chip_read_req_queue_2, chip_read_req_context_2);
      }
      else {
        // write logic
        if (host_write_data_queue -> read_nb(host_write_data)) {
          write_req_handler(command, host_write_data, chip_write_req_queue_3);
        }
      }
    }
  }
}

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
