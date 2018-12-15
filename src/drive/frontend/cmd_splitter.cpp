#include "cmd.h"
#include "cmd_splitter.hpp"
#include "staccel_kernel.h"

inline void cmd_splitter_impl(ST_Queue<SuperCommand> *super_command_queue,
    ST_Queue<Command> *command_queue) {
  SuperCommand super_command;
  if (super_command_queue->read_nb(super_command)) {
    Command command;
    for (int i = 0; i < SUPERCOMMAND_SIZE_IN_BIT; i += COMMAND_SIZE_IN_BIT) {
#pragma HLS unroll
      command.index = 
        super_command.data(i + COMMAND_SIZE_IN_BIT - 1, 
            i + COMMAND_NUM_SIZE_IN_BIT + COMMAND_ISREAD_SIZE_IN_BIT);
      command.num = super_command.data(i + COMMAND_NUM_SIZE_IN_BIT + COMMAND_ISREAD_SIZE_IN_BIT - 1,
          i + COMMAND_ISREAD_SIZE_IN_BIT);
      command.is_read = super_command.data(i + COMMAND_ISREAD_SIZE_IN_BIT - 1, i);
      command_queue->write(command);
    }
  }
}
void cmd_splitter(ST_Queue<SuperCommand> *super_command_queue,
		  ST_Queue<Command> *command_queue) {
  while (1) {
#pragma HLS pipeline
    cmd_splitter_impl(super_command_queue, command_queue);
  }
}
