#include "param_replicator.hpp"

void param_replicator_impl(ST_Queue<unsigned int> *throttle_ratio_queue,
                           ST_Queue<unsigned int> *throttle_ratio_0_queue,
                           ST_Queue<unsigned int> *throttle_ratio_1_queue,
                           ST_Queue<unsigned int> *throttle_ratio_2_queue,
                           ST_Queue<unsigned int> *throttle_ratio_3_queue,
                           ST_Queue<unsigned int> *delay_cycles_queue,
                           ST_Queue<unsigned int> *delay_cycles_0_queue,
                           ST_Queue<unsigned int> *delay_cycles_1_queue,
                           ST_Queue<unsigned int> *delay_cycles_2_queue,
                           ST_Queue<unsigned int> *delay_cycles_3_queue) {
  unsigned int throttle_ratio;
  if (throttle_ratio_queue->read_nb(throttle_ratio)) {
    throttle_ratio_0_queue->write(throttle_ratio);
    throttle_ratio_1_queue->write(throttle_ratio);
    throttle_ratio_2_queue->write(throttle_ratio);
    throttle_ratio_3_queue->write(throttle_ratio);
  }
  unsigned int delay_cycles;
  if (delay_cycles_queue->read_nb(delay_cycles)) {
    delay_cycles_0_queue->write(delay_cycles);
    delay_cycles_1_queue->write(delay_cycles);
    delay_cycles_2_queue->write(delay_cycles);
    delay_cycles_3_queue->write(delay_cycles);
  }
}

void param_replicator(ST_Queue<unsigned int> *throttle_ratio_queue,
                      ST_Queue<unsigned int> *throttle_ratio_0_queue,
                      ST_Queue<unsigned int> *throttle_ratio_1_queue,
                      ST_Queue<unsigned int> *throttle_ratio_2_queue,
                      ST_Queue<unsigned int> *throttle_ratio_3_queue,
                      ST_Queue<unsigned int> *delay_cycles_queue,
                      ST_Queue<unsigned int> *delay_cycles_0_queue,
                      ST_Queue<unsigned int> *delay_cycles_1_queue,
                      ST_Queue<unsigned int> *delay_cycles_2_queue,
                      ST_Queue<unsigned int> *delay_cycles_3_queue) {
  while (1) {
#pragma HLS pipeline
    param_replicator_impl(throttle_ratio_queue, throttle_ratio_0_queue,
                          throttle_ratio_1_queue, throttle_ratio_2_queue,
                          throttle_ratio_3_queue, delay_cycles_queue,
                          delay_cycles_0_queue, delay_cycles_1_queue,
                          delay_cycles_2_queue, delay_cycles_3_queue);
  }
}
