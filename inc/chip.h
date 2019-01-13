#pragma once

#include <ap_int.h>

#define DEFAULT_THROTTLE_RATIO (4)
#define NUM_OF_CHIP_BANKS (4)
#define LOG2_NUM_OF_CHIP_BANKS (2)

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

struct Host_Write_Data {
  ap_uint<512> data;
};
