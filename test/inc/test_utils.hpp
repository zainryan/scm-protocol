#pragma once

#include "chip.h"
#include "cmd.h"
#include "cmd_splitter.hpp"
#include "staccel_type.h"
#include "test_params.hpp"
#include "time_marker.hpp"

#define RUN_METHOD(times, method) \
  for (int i = 0; i < times; i++) method

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

namespace RandomGen {
inline unsigned int rand_u_int() { return rand(); }

inline unsigned long long rand_u_long_long() {
  unsigned long long ret;
  ret = rand();
  ret <<= 32;
  ret |= rand();
  return ret;
}

inline Command rand_command() {
  Command command;
  int command_num = rand();
  bool command_is_read = (bool)(rand() % 2);
  command.index = (ap_uint<COMMAND_INDEX_SIZE_IN_BIT>)rand_u_long_long();
  command.num = (ap_uint<COMMAND_NUM_SIZE_IN_BIT>)command_num;
  command.is_read = command_is_read;
  return command;
}

inline SuperCommand rand_super_command() {
  SuperCommand super_command;
  for (int i = 0; i < NUM_OF_COMMAND; i++) {
    Command command = rand_command();

    long long command_content = 0;
    command_content |= command.index;
    command_content <<= COMMAND_NUM_SIZE_IN_BIT;
    command_content |= command.num;
    command_content <<= COMMAND_ISREAD_SIZE_IN_BIT;
    command_content |= command.is_read;

    super_command.data <<= COMMAND_SIZE_IN_BIT;
    super_command.data |= ((ap_uint<COMMAND_SIZE_IN_BIT>)command_content);
  }
  return super_command;
}

inline ap_uint<512> rand_ap_uint_512() {
  ap_uint<512> data;
  for (int i = 0; i < 512; i += 32) {
    data(i + 31, i) = rand();
  }
  return data;
}

inline Chip_Read_Req rand_chip_read_req() {
  Chip_Read_Req req;
  req.addr = rand_u_long_long();
  return req;
}

inline Chip_Read_Resp rand_chip_read_resp() {
  Chip_Read_Resp resp;
  resp.data = rand_ap_uint_512();
  return resp;
}

inline Chip_Write_Req rand_chip_write_req() {
  Chip_Write_Req req;
  req.addr = rand_u_long_long();
  req.data = rand_ap_uint_512();
  return req;
}

inline PCIS_Write_Req rand_pcis_write_req() {
  PCIS_Write_Req pcis_write_req;
  pcis_write_req.addr = rand();
  int int_size_in_bit = sizeof(int) * 8;
  for (int i = 0; i < PCIS_BUS_WIDTH; i += int_size_in_bit) {
    pcis_write_req.data(i + int_size_in_bit - 1, i) = rand();
  }
  return pcis_write_req;
}
}  // namespace RandomGen

bool operator==(const Command &a, const Command &b) {
  return (a.index == b.index) && (a.num == b.num) && (a.is_read == b.is_read);
}

bool operator==(const Poke_Info &a, const Poke_Info &b) {
  return (a.tag == b.tag) && (a.data == b.data);
}

bool operator==(const SuperCommand &a, const SuperCommand &b) {
  return a.data == b.data;
}

bool operator==(const Chip_Read_Resp &a, const Chip_Read_Resp &b) {
  return a.data == b.data;
}

bool operator==(const Chip_Read_Req &a, const Chip_Read_Req &b) {
  return a.addr == b.addr;
}

bool operator==(const Chip_Write_Req &a, const Chip_Write_Req &b) {
  return (a.addr == b.addr) && (a.data == b.data);
}

bool operator==(const Chip_Read_Req_With_Time &a,
                const Chip_Read_Req_With_Time &b) {
  return (a.raw == b.raw) && (a.timestamp == b.timestamp);
}

bool operator==(const Chip_Read_Resp_With_Time &a,
                const Chip_Read_Resp_With_Time &b) {
  return (a.raw == b.raw) && (a.timestamp == b.timestamp);
}

bool operator==(const Chip_Write_Req_With_Time &a,
                const Chip_Write_Req_With_Time &b) {
  return (a.raw == b.raw) && (a.timestamp == b.timestamp);
}
