#pragma once

#include "cmd.h"
#include "staccel_type.h"

void cmd_intrpr(ST_Queue<Command> *command_queue,
                ST_Queue<Unit_Command> *unit_command_queue, Command *command,
                Unit_Command *unit_command,
                unsigned int *num_of_unit_command_left);

void cmd_intrpr(ST_Queue<Command> *command_queue,
                ST_Queue<Unit_Command> *unit_command_queue, Command command,
                Unit_Command unit_command,
                unsigned int num_of_unit_command_left);
