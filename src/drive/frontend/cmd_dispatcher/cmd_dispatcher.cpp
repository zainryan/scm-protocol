#include "cmd_dispatcher.hpp"
#include "chip.h"
#include "cmd.h"
#include "staccel_kernel.h"

inline void read_cmd_handler(const Unit_Command &unit_command,
                             ST_Queue<Chip_Read_Req> *chip_read_req_queue,
                             ST_Queue<Chip_Read_Req> *chip_read_req_context) {
  Chip_Read_Req chip_read_req;
  chip_read_req.addr =
      ((unsigned long long)unit_command.index) * UNIT_CHUCK_SIZE_IN_BYTE;
  chip_read_req_queue->write(chip_read_req);
  chip_read_req_context->write(chip_read_req);
}

inline void write_cmd_handler(const Unit_Command &unit_command,
                              const Host_Write_Data &host_write_data,
                              ST_Queue<Chip_Write_Req> *chip_write_req_queue) {
  Chip_Write_Req chip_write_req;
  chip_write_req.data = host_write_data.data;
  chip_write_req.addr =
      ((unsigned long long)unit_command.index) * UNIT_CHUCK_SIZE_IN_BYTE;
  chip_write_req_queue->write(chip_write_req);
}

inline void cmd_dispatcher_impl(
    ST_Queue<Unit_Command> *unit_command_queue,
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
    ST_Queue<Chip_Write_Req> *chip_write_req_queue_3) {
  Unit_Command unit_command;
  Host_Write_Data host_write_data;
  if (unit_command_queue->read_nb(unit_command)) {
    unsigned long long bank_id =
        ((unsigned long long)unit_command.index) & (NUM_OF_CHIP_BANKS - 1);
    if (bank_id == 0) {
      if (unit_command.is_read) {
        read_cmd_handler(unit_command, chip_read_req_queue_0,
                         chip_read_req_context_0);
      } else {
        if (host_write_data_queue->read_nb(host_write_data)) {
          write_cmd_handler(unit_command, host_write_data,
                            chip_write_req_queue_0);
        }
      }
    } else if (bank_id == 1) {
      if (unit_command.is_read) {
        read_cmd_handler(unit_command, chip_read_req_queue_1,
                         chip_read_req_context_1);
      } else {
        if (host_write_data_queue->read_nb(host_write_data)) {
          write_cmd_handler(unit_command, host_write_data,
                            chip_write_req_queue_1);
        }
      }
    } else if (bank_id == 2) {
      if (unit_command.is_read) {
        read_cmd_handler(unit_command, chip_read_req_queue_2,
                         chip_read_req_context_2);
      } else {
        if (host_write_data_queue->read_nb(host_write_data)) {
          write_cmd_handler(unit_command, host_write_data,
                            chip_write_req_queue_2);
        }
      }
    } else if (bank_id == 3) {
      if (unit_command.is_read) {
        read_cmd_handler(unit_command, chip_read_req_queue_3,
                         chip_read_req_context_3);
      } else {
        if (host_write_data_queue->read_nb(host_write_data)) {
          write_cmd_handler(unit_command, host_write_data,
                            chip_write_req_queue_3);
        }
      }
    }
  }
}

void cmd_dispatcher(ST_Queue<Unit_Command> *unit_command_queue,
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
                    ST_Queue<Chip_Write_Req> *chip_write_req_queue_3) {
  while (1) {
#pragma HLS pipeline
    cmd_dispatcher_impl(
        unit_command_queue, host_write_data_queue, chip_read_req_queue_0,
        chip_read_req_context_0, chip_write_req_queue_0, chip_read_req_queue_1,
        chip_read_req_context_1, chip_write_req_queue_1, chip_read_req_queue_2,
        chip_read_req_context_2, chip_write_req_queue_2, chip_read_req_queue_3,
        chip_read_req_context_3, chip_write_req_queue_3);
  }
}
