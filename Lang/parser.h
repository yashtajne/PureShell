#ifndef SHELL_PARSER_H
#define SHELL_PARSER_H

#include "Pure.h"
#include "Core/String.h"

typedef enum
{
	CMD_EMPTY,
	CMD_EXIT,
	CMD_CLEAN,
	CMD_CLEAR,
	CMD_CD,
	CMD_UNKNOWN
}
Command;

typedef struct
{
	Command type;
	simplestring_t text; /* trimmed input line (views the input) */
	simplestring_t arg;  /* first argument, empty when none */
	uint64_t arg_count;  /* number of arguments after the command */
}
ParsedCommand;

ParsedCommand parse(charseq_t line);
ParsedCommand parse_segment(charseq_t* cursor);

#endif // SHELL_PARSER_H
