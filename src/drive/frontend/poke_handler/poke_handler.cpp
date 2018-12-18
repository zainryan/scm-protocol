#include "poke_handler.hpp"

inline void poke_handler_impl(ST_Queue<Poke_Info> *poke_info_queue,
                              ST_Queue<unsigned int> *throttle_ratio_queue,
                              ST_Queue<unsigned int> *delay_cycles_queue) {
  Poke_Info poke_info;
  if (poke_info_queue->read_nb(poke_info)) {
    unsigned short state = 0;
    if (poke_info.tag == Tag::THROTTLE_RATIO_TAG) {
      state = 1;
    } else if (poke_info.tag == Tag::DELAY_CYCLES_TAG) {
      state = 2;
    }

    if (state) {
      if (state == 1) {
        throttle_ratio_queue->write(poke_info.data);
      } else if (state == 2) {
        delay_cycles_queue->write(poke_info.data);
      } else {
        // Add more conditions in the future.
      }
    }
  }
}

void poke_handler(ST_Queue<Poke_Info> *poke_info_queue,
                  ST_Queue<unsigned int> *throttle_ratio_queue,
                  ST_Queue<unsigned int> *delay_cycles_queue) {
  while (1) {
#pragma HLS pipeline
    poke_handler_impl(poke_info_queue, throttle_ratio_queue,
                      delay_cycles_queue);
  }
}
