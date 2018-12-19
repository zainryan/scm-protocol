#pragma once

#include "time_marker.hpp"

#define DEFAULT_DELAY_CYCLES (200)

inline void delay_unit_impl(
    unsigned long long *timestamp, unsigned int *delay_cycles,
    bool *valid_chip_read_req_with_time, bool *valid_chip_read_resp_with_time,
    bool *valid_chip_write_req_with_time,
    Chip_Read_Req_With_Time *data_chip_read_req_with_time,
    Chip_Read_Resp_With_Time *data_chip_read_resp_with_time,
    Chip_Write_Req_With_Time *data_chip_write_req_with_time,
    ST_Queue<unsigned int> *delay_cycles_queue,
    ST_Queue<Chip_Read_Req_With_Time> *chip_read_req_with_time_queue,
    ST_Queue<Chip_Read_Resp_With_Time> *chip_read_resp_with_time_queue,
    ST_Queue<Chip_Write_Req_With_Time> *chip_write_req_with_time_queue,
    ST_Queue<Chip_Read_Req> *delayed_chip_read_req_queue,
    ST_Queue<Chip_Read_Resp> *delayed_chip_read_resp_queue,
    ST_Queue<Chip_Write_Req> *delayed_chip_write_req_queue) {
  unsigned int tmp_delay_cycles;
  if (delay_cycles_queue->read_nb(tmp_delay_cycles)) {
    *delay_cycles = tmp_delay_cycles;
  }

  if (*valid_chip_read_req_with_time ||
      (*valid_chip_read_req_with_time = chip_read_req_with_time_queue->read_nb(
           *data_chip_read_req_with_time))) {
    if (*timestamp >= *delay_cycles + data_chip_read_req_with_time->timestamp) {
      if (delayed_chip_read_req_queue->write_nb(
              data_chip_read_req_with_time->raw)) {
        *valid_chip_read_req_with_time = false;
      }
    }
  }

  if (*valid_chip_read_resp_with_time ||
      (*valid_chip_read_resp_with_time =
           chip_read_resp_with_time_queue->read_nb(
               *data_chip_read_resp_with_time))) {
    if (*timestamp >=
        *delay_cycles + data_chip_read_resp_with_time->timestamp) {
      if (delayed_chip_read_resp_queue->write_nb(
              data_chip_read_resp_with_time->raw)) {
        *valid_chip_read_resp_with_time = false;
      }
    }
  }

  if (*valid_chip_write_req_with_time ||
      (*valid_chip_write_req_with_time =
           chip_write_req_with_time_queue->read_nb(
               *data_chip_write_req_with_time))) {
    if (*timestamp >=
        *delay_cycles + data_chip_write_req_with_time->timestamp) {
      if (delayed_chip_write_req_queue->write_nb(
              data_chip_write_req_with_time->raw)) {
        *valid_chip_write_req_with_time = false;
      }
    }
  }

  (*timestamp)++;
}

inline void delay_unit(
    ST_Queue<unsigned int> *delay_cycles_queue,
    ST_Queue<Chip_Read_Req_With_Time> *chip_read_req_with_time_queue,
    ST_Queue<Chip_Read_Resp_With_Time> *chip_read_resp_with_time_queue,
    ST_Queue<Chip_Write_Req_With_Time> *chip_write_req_with_time_queue,
    ST_Queue<Chip_Read_Req> *delayed_chip_read_req_queue,
    ST_Queue<Chip_Read_Resp> *delayed_chip_read_resp_queue,
    ST_Queue<Chip_Write_Req> *delayed_chip_write_req_queue) {
  unsigned long long timestamp = 0;
  unsigned int delay_cycles = DEFAULT_DELAY_CYCLES;
  bool valid_chip_read_req_with_time = false;
  bool valid_chip_read_resp_with_time = false;
  bool valid_chip_write_req_with_time = false;
  Chip_Read_Req_With_Time data_chip_read_req_with_time;
  Chip_Read_Resp_With_Time data_chip_read_resp_with_time;
  Chip_Write_Req_With_Time data_chip_write_req_with_time;

  while (1) {
#pragma HLS pipeline
    delay_unit_impl(
        &timestamp, &delay_cycles, &valid_chip_read_req_with_time,
        &valid_chip_read_resp_with_time, &valid_chip_write_req_with_time,
        &data_chip_read_req_with_time, &data_chip_read_resp_with_time,
        &data_chip_write_req_with_time, delay_cycles_queue,
        chip_read_req_with_time_queue, chip_read_resp_with_time_queue,
        chip_write_req_with_time_queue, delayed_chip_read_req_queue,
        delayed_chip_read_resp_queue, delayed_chip_write_req_queue);
  }
}
