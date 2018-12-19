#include "pcis_handler.hpp"

inline void pcis_handler_impl(ST_Queue<PCIS_Write_Req> *pcis_write_req_queue,
                              ST_Queue<SuperCommand> *super_command_queue) {
  PCIS_Write_Req pcis_write_req;
  if (pcis_write_req_queue->read_nb(pcis_write_req)) {
    SuperCommand super_command;
    super_command.data = pcis_write_req.data;
    super_command_queue->write(super_command);
  }
}

void pcis_handler(ST_Queue<PCIS_Write_Req> *pcis_write_req_queue,
                  ST_Queue<SuperCommand> *super_command_queue) {
  while (1) {
#pragma HLS pipeline
    pcis_handler_impl(pcis_write_req_queue, super_command_queue);
  }
}
