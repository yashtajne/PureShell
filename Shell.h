#ifndef PureShell_h
#define PureShell_h

#include "Lang/parser.h"

void do_exit  (ParsedCommand cmd);
void do_clean (ParsedCommand cmd);
void do_clear (ParsedCommand cmd);

void do_cd     (ParsedCommand cmd);
void do_launch (ParsedCommand cmd);

void handle_command (ParsedCommand cmd);

#endif // PureShell_h