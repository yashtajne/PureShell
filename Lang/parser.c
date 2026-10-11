#include "parser.h"
#include "Core/Char.h"
#include "Core/Charseq.h"

/* Parse a single command (no `;` handling).
 * Trims the input in place. `text` views the trimmed command (for launching
 * programs verbatim); `arg` views the first argument and `arg_count`
 * is the total number of arguments after the command word. */
static ParsedCommand
parse_single(charseq_t line)
{
	ParsedCommand out;
	out.type = CMD_UNKNOWN;
	out.text.charseq = NULL;
	out.text.size = 0;
	out.arg.charseq = NULL;
	out.arg.size = 0;
	out.arg_count = 0;

	if ( !line )
	{
		out.type = CMD_EMPTY;
		return out;
	}

	charseq_trimleft(line);
	charseq_trimright(line);

	if ( *line == '\0' )
	{
		out.type = CMD_EMPTY;
		return out;
	}

	out.text.charseq = line;
	out.text.size = charseq_countbytes(line);

	/* isolate first word */
	char* end = line;
	while ( *end && !isspace(*end) )
		end++;

	/* copy first word into small stack buffer for comparison.
	 * Builtin names are short; anything longer is unknown. */
	char word[16];
	uint64_t len = (uint64_t)(end - line);
	if ( len >= sizeof(word) )
		return out;

	for ( uint64_t i = 0; i < len; i++ )
		word[i] = line[i];
	word[len] = '\0';

	if ( charseq_isequals(word, "exit") )
		out.type = CMD_EXIT;
	else if ( charseq_isequals(word, "clean") )
		out.type = CMD_CLEAN;
	else if ( charseq_isequals(word, "clear") )
		out.type = CMD_CLEAR;
	else if ( charseq_isequals(word, "cd") )
		out.type = CMD_CD;
	else
		return out;

	/* tokenize the arguments */
	char* p = end;
	for ( ;; )
	{
		while ( isspace(*p) )
			p++;

		if ( *p == '\0' )
			break;

		char* a = p;
		while ( *p && !isspace(*p) )
			p++;

		if ( out.arg_count == 0 )
		{
			out.arg.charseq = a;
			out.arg.size = (uint64_t)(p - a);
		}
		out.arg_count++;
	}

	return out;
}

/* Parse the next `;`-separated command and advance past it.
 * Empty segments are skipped. Always advances `cursor`, so
 * `while (*cursor) handle_command(parse_segment(&cursor))`
 * terminates. */
ParsedCommand
parse_segment(charseq_t* cursor)
{
	ParsedCommand out;
	out.type = CMD_EMPTY;
	out.text.charseq = NULL;
	out.text.size = 0;
	out.arg.charseq = NULL;
	out.arg.size = 0;
	out.arg_count = 0;

	if ( !cursor || !*cursor )
		return out;

	charseq_t p = *cursor;
	while ( *p == ';' || isspace(*p) )
		p++;

	if ( *p == '\0' )
	{
		*cursor = p;
		return out;
	}

	charseq_t end = p;
	while ( *end != '\0' && *end != ';' )
		end++;

	if ( *end == ';' )
	{
		*end = '\0';
		*cursor = end + 1;
	}
	else
	{
		*cursor = end;
	}

	return parse_single(p);
}

/* Parse the first command of a line. */
ParsedCommand
parse(charseq_t line)
{
	return parse_segment(&line);
}
