#pragma once

#include "staccel_type.h"

#define COMMAND_INDEX_SIZE_IN_BIT 50
#define COMMAND_NUM_SIZE_IN_BIT 13
#define COMMAND_ISREAD_SIZE_IN_BIT 1
#define COMMAND_SIZE_IN_BIT 64
#define SUPERCOMMAND_SIZE_IN_BIT 512
#define NUM_OF_COMMAND (SUPERCOMMAND_SIZE_IN_BIT / COMMAND_SIZE_IN_BIT)

void cmd_splitter(ST_Queue<SuperCommand> *super_command_queue, ST_Queue<Command> *command_queue);
void cmd_splitter_impl(ST_Queue<SuperCommand> *super_command_queue, ST_Queue<Command> *command_queue);
