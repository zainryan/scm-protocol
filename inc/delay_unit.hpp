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

void delay_unit_0(
    ST_Queue<unsigned int> *delay_cycles_queue,
    ST_Queue<Chip_Read_Req_With_Time> *chip_read_req_with_time_queue,
    ST_Queue<Chip_Read_Resp_With_Time> *chip_read_resp_with_time_queue,
    ST_Queue<Chip_Write_Req_With_Time> *chip_write_req_with_time_queue,
    ST_Queue<Chip_Read_Req> *delayed_chip_read_req_queue,
    ST_Queue<Chip_Read_Resp> *delayed_chip_read_resp_queue,
    ST_Queue<Chip_Write_Req> *delayed_chip_write_req_queue);

void delay_unit_1(
    ST_Queue<unsigned int> *delay_cycles_queue,
    ST_Queue<Chip_Read_Req_With_Time> *chip_read_req_with_time_queue,
    ST_Queue<Chip_Read_Resp_With_Time> *chip_read_resp_with_time_queue,
    ST_Queue<Chip_Write_Req_With_Time> *chip_write_req_with_time_queue,
    ST_Queue<Chip_Read_Req> *delayed_chip_read_req_queue,
    ST_Queue<Chip_Read_Resp> *delayed_chip_read_resp_queue,
    ST_Queue<Chip_Write_Req> *delayed_chip_write_req_queue);

void delay_unit_2(
    ST_Queue<unsigned int> *delay_cycles_queue,
    ST_Queue<Chip_Read_Req_With_Time> *chip_read_req_with_time_queue,
    ST_Queue<Chip_Read_Resp_With_Time> *chip_read_resp_with_time_queue,
    ST_Queue<Chip_Write_Req_With_Time> *chip_write_req_with_time_queue,
    ST_Queue<Chip_Read_Req> *delayed_chip_read_req_queue,
    ST_Queue<Chip_Read_Resp> *delayed_chip_read_resp_queue,
    ST_Queue<Chip_Write_Req> *delayed_chip_write_req_queue);

void delay_unit_3(
    ST_Queue<unsigned int> *delay_cycles_queue,
    ST_Queue<Chip_Read_Req_With_Time> *chip_read_req_with_time_queue,
    ST_Queue<Chip_Read_Resp_With_Time> *chip_read_resp_with_time_queue,
    ST_Queue<Chip_Write_Req_With_Time> *chip_write_req_with_time_queue,
    ST_Queue<Chip_Read_Req> *delayed_chip_read_req_queue,
    ST_Queue<Chip_Read_Resp> *delayed_chip_read_resp_queue,
    ST_Queue<Chip_Write_Req> *delayed_chip_write_req_queue);
