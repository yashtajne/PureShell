#ifndef SHELL_BUILTIN_H
#define SHELL_BUILTIN_H

#include "parser.h"

void do_exit  (ParsedCommand cmd);
void do_clean (ParsedCommand cmd);
void do_clear (ParsedCommand cmd);

#endif // SHELL_BUILTIN_H
