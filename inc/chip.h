#pragma once

#include <ap_int.h>

#define DEFAULT_THROTTLE_RATIO (4)
#define NUM_OF_CHIP_BANKS (4)  // Must be the power of 2
#define LOG2_NUM_OF_CHIP_BANKS (2)
#define UNIT_CHUCK_SIZE_IN_BYTE (64)

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

struct Chip_Read_Resp_With_Addr {
  unsigned long long addr;
  ap_uint<512> data;
};
