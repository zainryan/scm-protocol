#pragma once

#include "ap_int.h"

// A bunch of Command structs sent from host using MMIO.
struct SuperCommand {
  // The raw data.
  ap_uint<512> data;
};

struct Command {
  // The index to the drive sub-block (64B).
  ap_uint<50> index;
  // The number of sub-block would being accessed.
  ap_uint<15> num;
  // Indicate it's a read IO or write IO.
  bool is_read;
};

// command with num == 1
struct Unit_Command {
  // The index to the drive sub-block (64B).
  ap_uint<50> index;
  // Indicate it's a read IO or write IO.
  bool is_read;
};
