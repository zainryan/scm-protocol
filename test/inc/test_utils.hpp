#pragma once

#include "test_params.hpp"

#define RUN_METHOD(times, method) for(int i = 0; i < times; i++) method

template <typename T> 
void drain_queue(ST_Queue<T> *queue, std::vector<T> *vec) {
  unsigned long long read_times = 0;
  while (read_times < DRAIN_QUEUE_READ_TIMES) {
    T data;
    if (queue->read_nb(data)) {
      vec->push_back(data); 
    }
    read_times++;
  }

}
