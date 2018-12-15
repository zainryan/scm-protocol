#pragma once

#include <ap_int.h>

#define THROTTLE_RATIO (4)
#define LOG2_THROTTLE_RATIO (2)

struct Chip_Read_Req {
  unsigned long long addr;
};

struct Chip_Read_Resp {
  ap_uint<512> data;
};

struct Chip_Write_Req {
  unsigned long long addr;
  ap_uint<512> data;
};
