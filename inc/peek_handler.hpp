#pragma once

#include "staccel_kernel.h"
#include "tag.hpp"

#ifdef COMPILE_UNIT_TESTS
extern bool reset_peek_handler_impl;
#endif

void peek_handler_impl(ST_Queue<unsigned short> *return_credit_num_queue,
                       ST_Queue<unsigned int> *peek_req_queue,
                       ST_Queue<unsigned int> *peek_resp_queue);

void peek_handler(ST_Queue<unsigned short> *return_credit_num_queue,
                  ST_Queue<unsigned int> *peek_req_queue,
                  ST_Queue<unsigned int> *peek_resp_queue);
