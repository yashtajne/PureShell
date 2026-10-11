#ifndef SHELL_HANDLE_H
#define SHELL_HANDLE_H

#include "parser.h"

void do_cd     (ParsedCommand cmd);
void do_launch (ParsedCommand cmd);

void handle_command (ParsedCommand cmd);

#endif // SHELL_HANDLE_H
