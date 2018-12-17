#include "chip.h"
#include "cmd.h"
#include "read_resp_collector.hpp"
#include "staccel_kernel.h"

inline void read_resp_collector (ST_Queue<Chip_Read_Req> *read_req_context_0, 
    ST_Queue<Chip_Read_Resp> *chip_read_resp_queue_0,
    ST_Queue<Chip_Read_Req> *read_req_context_1, 
    ST_Queue<Chip_Read_Resp> *chip_read_resp_queue_1,
    ST_Queue<Chip_Read_Req> *read_req_context_2, 
    ST_Queue<Chip_Read_Resp> *chip_read_resp_queue_2,
    ST_Queue<Chip_Read_Req> *read_req_context_3, 
    ST_Queue<Chip_Read_Resp> *chip_read_resp_queue_3,
    ST_Queue<Chip_Read_Resp_With_Addr> *chip_read_resp_with_addr_queue
    ) {
  while (1) { 
#pragma HLS pipeline
    read_resp_collector_impl(read_req_context_0, 
        chip_read_resp_queue_0,
        read_req_context_1, 
        chip_read_resp_queue_1
        read_req_context_2, 
        chip_read_resp_queue_2
        read_req_context_3, 
        chip_read_resp_queue_3,
        chip_read_resp_with_addr_queue
        );
  }
}
