#pragma once

#include "chip.h"
#include "staccel_kernel.h"

struct Chip_Read_Req_With_Time {
  Chip_Read_Req raw;
  unsigned long long timestamp;
};

struct Chip_Read_Resp_With_Time {
  Chip_Read_Resp raw;
  unsigned long long timestamp;
};

struct Chip_Write_Req_With_Time {
  Chip_Write_Req raw;
  unsigned long long timestamp;
};

inline void time_marker_impl(
    ST_Queue<Chip_Read_Req> *chip_read_req_queue,
    ST_Queue<Chip_Read_Resp> *chip_read_resp_queue,
    ST_Queue<Chip_Write_Req> *chip_write_req_queue,
    ST_Queue<Chip_Read_Req_With_Time> *chip_read_req_with_time_queue,
    ST_Queue<Chip_Read_Resp_With_Time> *chip_read_resp_with_time_queue,
    ST_Queue<Chip_Write_Req_With_Time> *chip_write_req_with_time_queue) {
  static unsigned long long timestamp = 0;
  static bool valid_chip_read_req = false;
  static bool valid_chip_read_resp = false;
  static bool valid_chip_write_req = false;
  static Chip_Read_Req data_chip_read_req;
  static Chip_Read_Resp data_chip_read_resp;
  static Chip_Write_Req data_chip_write_req;
  static bool valid_timestamp_chip_read_req = false;
  static bool valid_timestamp_chip_read_resp = false;
  static bool valid_timestamp_chip_write_req = false;
  static unsigned long long data_timestamp_chip_read_req;
  static unsigned long long data_timestamp_chip_read_resp;
  static unsigned long long data_timestamp_chip_write_req;

  if (valid_chip_read_req ||
      (valid_chip_read_req =
           chip_read_req_queue->read_nb(data_chip_read_req))) {
    if (!valid_timestamp_chip_read_req) {
      data_timestamp_chip_read_req = timestamp;
      valid_timestamp_chip_read_req = true;
    }
    Chip_Read_Req_With_Time chip_read_req_with_time;
    chip_read_req_with_time.raw = data_chip_read_req;
    chip_read_req_with_time.timestamp = timestamp;
    if (chip_read_req_with_time_queue->write_nb(chip_read_req_with_time)) {
      valid_timestamp_chip_read_req = valid_chip_read_req = false;
    }
  }

  if (valid_chip_read_resp ||
      (valid_chip_read_resp =
           chip_read_resp_queue->read_nb(data_chip_read_resp))) {
    if (!valid_timestamp_chip_read_resp) {
      data_timestamp_chip_read_resp = timestamp;
      valid_timestamp_chip_read_resp = true;
    }
    Chip_Read_Resp_With_Time chip_read_resp_with_time;
    chip_read_resp_with_time.raw = data_chip_read_resp;
    chip_read_resp_with_time.timestamp = timestamp;
    if (chip_read_resp_with_time_queue->write_nb(chip_read_resp_with_time)) {
      valid_timestamp_chip_read_resp = valid_chip_read_resp = false;
    }
  }

  if (valid_chip_write_req ||
      (valid_chip_write_req =
           chip_write_req_queue->read_nb(data_chip_write_req))) {
    if (!valid_timestamp_chip_write_req) {
      data_timestamp_chip_write_req = timestamp;
      valid_timestamp_chip_write_req = true;
    }
    Chip_Write_Req_With_Time chip_write_req_with_time;
    chip_write_req_with_time.raw = data_chip_write_req;
    chip_write_req_with_time.timestamp = timestamp;
    if (chip_write_req_with_time_queue->write_nb(chip_write_req_with_time)) {
      valid_timestamp_chip_write_req = valid_chip_write_req = false;
    }
  }

  timestamp++;
}
