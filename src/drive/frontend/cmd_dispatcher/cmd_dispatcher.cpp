#include "cmd.h"
#include "cmd_dispatcher.hpp"
#include "staccel_kernel.h"

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
