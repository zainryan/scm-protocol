#pragma once

#include "staccel_kernel.h"

#define THROTTLE_RATIO_TAG (0)
// NEXT TAG TO USE: 4

void poke_handler_impl(ST_Queue<Poke_Info> *poke_info_queue,
                       ST_Queue<unsigned int> *throttle_ratio_queue);

void poke_handler(ST_Queue<Poke_Info> *poke_info_queue,
                  ST_Queue<unsigned int> *throttle_ratio_queue);

