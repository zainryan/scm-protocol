#pragma once

#include "chip.h"
#include "staccel_type.h"

void read_resp_mux(
    ST_Queue<Chip_Read_Req> *read_req_context_0,
    ST_Queue<Chip_Read_Resp> *chip_read_resp_queue_0,
    ST_Queue<Chip_Read_Req> *read_req_context_1,
    ST_Queue<Chip_Read_Resp> *chip_read_resp_queue_1,
    ST_Queue<Chip_Read_Req> *read_req_context_2,
    ST_Queue<Chip_Read_Resp> *chip_read_resp_queue_2,
    ST_Queue<Chip_Read_Req> *read_req_context_3,
    ST_Queue<Chip_Read_Resp> *chip_read_resp_queue_3,
    ST_Queue<Chip_Read_Resp_With_Addr> *chip_read_resp_with_addr_queue,
    unsigned char write_lease);

void read_resp_mux_impl(
    ST_Queue<Chip_Read_Req> *read_req_context_0,
    ST_Queue<Chip_Read_Resp> *chip_read_resp_queue_0,
    ST_Queue<Chip_Read_Req> *read_req_context_1,
    ST_Queue<Chip_Read_Resp> *chip_read_resp_queue_1,
    ST_Queue<Chip_Read_Req> *read_req_context_2,
    ST_Queue<Chip_Read_Resp> *chip_read_resp_queue_2,
    ST_Queue<Chip_Read_Req> *read_req_context_3,
    ST_Queue<Chip_Read_Resp> *chip_read_resp_queue_3,
    ST_Queue<Chip_Read_Resp_With_Addr> *chip_read_resp_with_addr_queue,
    unsigned char *write_lease);
