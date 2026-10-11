#ifndef SHELL_PARSER_H
#define SHELL_PARSER_H

#include "Pure.h"

typedef enum
{
	CMD_EMPTY,
	CMD_EXIT,
	CMD_CLEAN,
	CMD_CLEAR,
	CMD_UNKNOWN
}
Command;

typedef struct
{
	Command type;
	boolean has_args;
}
ParsedCommand;

ParsedCommand parse(charseq_t line);

#endif // SHELL_PARSER_H
