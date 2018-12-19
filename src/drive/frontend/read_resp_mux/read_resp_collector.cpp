#include "chip.h"
#include "cmd.h"
#include "read_resp_mux.hpp"
#include "staccel_kernel.h"

#ifdef COMPILE_UNIT_TESTS
bool reset_read_resp_collector_impl = false;
#endif

inline void read_resp_handler(const Chip_Read_Req &chip_read_req,
			      const Chip_Read_Resp &chip_read_resp,
			      ST_Queue<Chip_Read_Resp_With_Addr> *chip_read_resp_with_addr_queue
			      ) {
  Chip_Read_Resp_With_Addr chip_read_resp_with_addr;
  chip_read_resp_with_addr.addr = chip_read_req.addr;
  chip_read_resp_with_addr.data = chip_read_resp.data;
  chip_read_resp_with_addr_queue->write(chip_read_resp_with_addr);
}

inline void read_resp_mux_impl(ST_Queue<Chip_Read_Req> *read_req_context_0, 
			       ST_Queue<Chip_Read_Resp> *chip_read_resp_queue_0,
			       ST_Queue<Chip_Read_Req> *read_req_context_1, 
			       ST_Queue<Chip_Read_Resp> *chip_read_resp_queue_1,
			       ST_Queue<Chip_Read_Req> *read_req_context_2, 
			       ST_Queue<Chip_Read_Resp> *chip_read_resp_queue_2,
			       ST_Queue<Chip_Read_Req> *read_req_context_3, 
			       ST_Queue<Chip_Read_Resp> *chip_read_resp_queue_3,
			       ST_Queue<Chip_Read_Resp_With_Addr> *chip_read_resp_with_addr_queue
			       ) {

#ifdef COMPILE_UNIT_TESTS
  if (reset_read_resp_mux_impl) {
    reset_read_resp_mux_impl = false;
    write_lease = 0;
  }
#endif

  static unsigned char write_lease = 0;

  Chip_Read_Resp chip_read_resp_0; 
  Chip_Read_Resp chip_read_resp_1; 
  Chip_Read_Resp chip_read_resp_2; 
  Chip_Read_Resp chip_read_resp_3; 

  Chip_Read_Req chip_read_req_0; 
  Chip_Read_Req chip_read_req_1; 
  Chip_Read_Req chip_read_req_2; 
  Chip_Read_Req chip_read_req_3; 

  if (write_lease == 0 && chip_read_resp_queue_0->read_nb(chip_read_resp_0)) {
    if (read_req_context_0->read_nb(chip_read_req_0)) {
      read_resp_handler(chip_read_req_0, chip_read_resp_0, chip_read_resp_with_addr_queue);
      write_lease = (write_lease + 1) & 3;
    }
  }

  if (write_lease == 1 && chip_read_resp_queue_1->read_nb(chip_read_resp_1)) {
    if (read_req_context_1->read_nb(chip_read_req_1)) {
      read_resp_handler(chip_read_req_1, chip_read_resp_1, chip_read_resp_with_addr_queue);
      write_lease = (write_lease + 1) & 3;
    }
  }

  if (write_lease == 2 && chip_read_resp_queue_2->read_nb(chip_read_resp_2)) {
    if (read_req_context_2->read_nb(chip_read_req_2)) {
      read_resp_handler(chip_read_req_2, chip_read_resp_2, chip_read_resp_with_addr_queue);
      write_lease = (write_lease + 1) & 3;
    }
  }

  if (write_lease == 3 && chip_read_resp_queue_3->read_nb(chip_read_resp_3)) {
    if (read_req_context_3->read_nb(chip_read_req_3)) {
      read_resp_handler(chip_read_req_3, chip_read_resp_3, chip_read_resp_with_addr_queue);
      write_lease = (write_lease + 1) & 3;
    }
  }
}

inline void read_resp_mux(ST_Queue<Chip_Read_Req> *read_req_context_0, 
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
    read_resp_mux_impl(read_req_context_0, 
		       chip_read_resp_queue_0,
		       read_req_context_1, 
		       chip_read_resp_queue_1,
		       read_req_context_2, 
		       chip_read_resp_queue_2,
		       read_req_context_3, 
		       chip_read_resp_queue_3,
		       chip_read_resp_with_addr_queue
		       );
  }
}
