#pragma once

#include "staccel_type.h"

void param_replicator_impl(ST_Queue<unsigned int> *throttle_ratio_queue,
                           ST_Queue<unsigned int> *throttle_ratio_0_queue,
                           ST_Queue<unsigned int> *throttle_ratio_1_queue,
                           ST_Queue<unsigned int> *throttle_ratio_2_queue,
                           ST_Queue<unsigned int> *throttle_ratio_3_queue,
                           ST_Queue<unsigned int> *delay_cycles_queue,
                           ST_Queue<unsigned int> *delay_cycles_0_queue,
                           ST_Queue<unsigned int> *delay_cycles_1_queue,
                           ST_Queue<unsigned int> *delay_cycles_2_queue,
                           ST_Queue<unsigned int> *delay_cycles_3_queue
                           );

void param_replicator(ST_Queue<unsigned int> *throttle_ratio_queue,
                      ST_Queue<unsigned int> *throttle_ratio_0_queue,
                      ST_Queue<unsigned int> *throttle_ratio_1_queue,
                      ST_Queue<unsigned int> *throttle_ratio_2_queue,
                      ST_Queue<unsigned int> *throttle_ratio_3_queue,
                      ST_Queue<unsigned int> *delay_cycles_queue,
                      ST_Queue<unsigned int> *delay_cycles_0_queue,
                      ST_Queue<unsigned int> *delay_cycles_1_queue,
                      ST_Queue<unsigned int> *delay_cycles_2_queue,
                      ST_Queue<unsigned int> *delay_cycles_3_queue);
