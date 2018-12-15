#pragma once

#include "cmd.h"
#include <staccel_kernel.h>

void pcis_handler_impl(ST_Queue<PCIS_Write_Req> *pcis_write_req_queue,
                       ST_Queue<SuperCommand> *super_command_queue);
void pcis_handler(ST_Queue<PCIS_Write_Req> *pcis_write_req_queue,
                  ST_Queue<SuperCommand> *super_command_queue);
