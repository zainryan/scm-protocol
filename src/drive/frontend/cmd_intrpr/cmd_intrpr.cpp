
#include "cmd_intrpr.hpp"
#include "chip.h"
#include "cmd.h"
#include "staccel_kernel.h"

inline void cmd_intrpr_impl(ST_Queue<Command> *command_queue,
                            ST_Queue<Unit_Command> *unit_command_queue,
                            Command *command, Unit_Command *unit_command,
                            unsigned int *num_of_unit_command_left) {
  if (*num_of_unit_command_left > 0) {
    (*num_of_unit_command_left)--;
    unit_command->index += 64;
    unit_command_queue->write(*unit_command);

  } else if (*num_of_unit_command_left == 0 &&
             command_queue->read_nb(*command)) {
    unit_command->index = command->index;
    unit_command->num = 1;
    unit_command->is_read = command->is_read;
    if (command->num > 1) {
      (*num_of_unit_command_left) = (unsigned int)(command->num) - 1;
    }
    unit_command_queue->write(*unit_command);
  }
}

void cmd_intrpr(ST_Queue<Command> *command_queue,
                ST_Queue<Unit_Command> *unit_command_queue, Command command,
                Unit_Command unit_command,
                unsigned int num_of_unit_command_left = 0) {
#pragma HLS pipeline
  while (1) {
    cmd_intrpr_impl(command_queue, unit_command_queue, &command, &unit_command,
                    &num_of_unit_command_left);
  }
}
