#pragma once

struct Chip_Read_Resp_With_Addr {
  unsigned long long addr;
  ap_uint<512> data;
};

void read_resp_collector(
    ST_Queue<Chip_Read_Req> *read_req_context_0,
    ST_Queue<Chip_Read_Resp> *chip_read_resp_queue_0,
    ST_Queue<Chip_Read_Req> *read_req_context_1,
    ST_Queue<Chip_Read_Resp> *chip_read_resp_queue_1,
    ST_Queue<Chip_Read_Req> *read_req_context_2,
    ST_Queue<Chip_Read_Resp> *chip_read_resp_queue_2,
    ST_Queue<Chip_Read_Req> *read_req_context_3,
    ST_Queue<Chip_Read_Resp> *chip_read_resp_queue_3,
    ST_Queue<Chip_Read_Resp_With_Addr> *chip_read_resp_with_addr_queue);
