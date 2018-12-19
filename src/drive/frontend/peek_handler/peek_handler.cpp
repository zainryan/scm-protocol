#include "peek_handler.hpp"

inline void peek_handler_impl(unsigned short *returned_credits,
                              ST_Queue<unsigned short> *return_credit_num_queue,
                              ST_Queue<unsigned int> *peek_req_queue,
                              ST_Queue<unsigned int> *peek_resp_queue) {
  unsigned short return_credit_num;
  if (return_credit_num_queue->read_nb(return_credit_num)) {
    *returned_credits += return_credit_num;
  }

  unsigned short state = 0;
  unsigned int peek_req_tag;
  if (peek_req_queue->read_nb(peek_req_tag)) {
    if (peek_req_tag == Tag::RETURNED_CREDITS_TAG) {
      state = 1;
    }
  }

  if (state) {
    if (state == 1) {
      peek_resp_queue->write(*returned_credits);
      // Clear returned_credits after it is pulled by the host,
      // which ensures the credit "consistency".
      *returned_credits = 0;
    } else {
      // Add more conditions in the future.
      peek_resp_queue->write(0);
    }
  }
}

void peek_handler(ST_Queue<unsigned short> *return_credit_num_queue,
                  ST_Queue<unsigned int> *peek_req_queue,
                  ST_Queue<unsigned int> *peek_resp_queue) {
  unsigned short returned_credits = 0;
  while (1) {
#pragma HLS pipeline
    peek_handler_impl(&returned_credits, return_credit_num_queue,
                      peek_req_queue, peek_resp_queue);
  }
}
