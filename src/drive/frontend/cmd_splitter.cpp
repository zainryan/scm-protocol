#include "cmd.h"
#include "staccel_kernel.h"

void cmd_splitter(ST_Queue<SuperCommand> super_command_queue,
		  ST_Queue<Command> command_queue) {
  while (1) {
#pragma HLS pipeline
    SuperCommand super_command;
    if (super_command_queue.read_nb(super_command)) {
      Command command;
      // Add your logic.
      command_queue.write(command);
    }
  }
}
