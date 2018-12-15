#pragma once
#include "staccel_type.h"
void cmd_splitter(ST_Queue<SuperCommand> &super_command_queue, ST_Queue<Command> &command_queue);
void cmd_splitter_impl(ST_Queue<SuperCommand> &super_command_queue, ST_Queue<Command> &command_queue);
