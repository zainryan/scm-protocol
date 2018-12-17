#pragma once

#include "time_marker.hpp"

#define DEFAULT_DELAY_CYCLES (200)

#ifdef COMPILE_UNIT_TESTS
bool reset_delay_unit_impl = false;
#endif

inline void delay_unit_impl(
    ST_Queue<unsigned int> *delay_cycles_queue,
    ST_Queue<Chip_Read_Req_With_Time> *chip_read_req_with_time_queue,
    ST_Queue<Chip_Read_Resp_With_Time> *chip_read_resp_with_time_queue,
    ST_Queue<Chip_Write_Req_With_Time> *chip_write_req_with_time_queue,
    ST_Queue<Chip_Read_Req> *delayed_chip_read_req_queue,
    ST_Queue<Chip_Read_Resp> *delayed_chip_read_resp_queue,
    ST_Queue<Chip_Write_Req> *delayed_chip_write_req_queue) {
  static unsigned long long timestamp = 0;
  static unsigned int delay_cycles = DEFAULT_DELAY_CYCLES;
  static bool valid_chip_read_req_with_time = false;
  static bool valid_chip_read_resp_with_time = false;
  static bool valid_chip_write_req_with_time = false;
  static Chip_Read_Req_With_Time data_chip_read_req_with_time;
  static Chip_Read_Resp_With_Time data_chip_read_resp_with_time;
  static Chip_Write_Req_With_Time data_chip_write_req_with_time;

#ifdef COMPILE_UNIT_TESTS
  if (reset_delay_unit_impl) {
    reset_delay_unit_impl = 0;
    timestamp = 0;
    delay_cycles = DEFAULT_DELAY_CYCLES;
    valid_chip_read_req_with_time = false;
    valid_chip_read_resp_with_time = false;
    valid_chip_write_req_with_time = false;
  }
#endif

  unsigned int tmp_delay_cycles;
  if (delay_cycles_queue->read_nb(tmp_delay_cycles)) {
    delay_cycles = tmp_delay_cycles;
  }

  if (valid_chip_read_req_with_time ||
      (valid_chip_read_req_with_time = chip_read_req_with_time_queue->read_nb(
           data_chip_read_req_with_time))) {
    if (timestamp >= delay_cycles + data_chip_read_req_with_time.timestamp) {
      if (delayed_chip_read_req_queue->write_nb(
              data_chip_read_req_with_time.raw)) {
        valid_chip_read_req_with_time = false;
      }
    }
  }

  if (valid_chip_read_resp_with_time ||
      (valid_chip_read_resp_with_time = chip_read_resp_with_time_queue->read_nb(
           data_chip_read_resp_with_time))) {
    if (timestamp >= delay_cycles + data_chip_read_resp_with_time.timestamp) {
      if (delayed_chip_read_resp_queue->write_nb(
              data_chip_read_resp_with_time.raw)) {
        valid_chip_read_resp_with_time = false;
      }
    }
  }

  if (valid_chip_write_req_with_time ||
      (valid_chip_write_req_with_time = chip_write_req_with_time_queue->read_nb(
           data_chip_write_req_with_time))) {
    if (timestamp >= delay_cycles + data_chip_write_req_with_time.timestamp) {
      if (delayed_chip_write_req_queue->write_nb(
              data_chip_write_req_with_time.raw)) {
        valid_chip_write_req_with_time = false;
      }
    }
  }

  timestamp++;
}
