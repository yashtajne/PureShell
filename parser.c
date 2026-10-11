#include "parser.h"
#include "Core/Char.h"
#include "Core/Charseq.h"

/* Parse a single input line into a builtin command.
 * Does not modify the input. Trims leading/trailing whitespace,
 * matches the first word against exit/clean/clear, and reports
 * whether trailing arguments were present (builtins take none). */
ParsedCommand
parse(charseq_t line)
{
	ParsedCommand out;
	out.type = CMD_UNKNOWN;
	out.has_args = false;

	if ( !line )
	{
		out.type = CMD_EMPTY;
		return out;
	}

	/* skip leading whitespace */
	while ( isspace(*line) )
		line++;

	if ( *line == '\0' )
	{
		out.type = CMD_EMPTY;
		return out;
	}

	/* isolate first word */
	const char* end = line;
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
	else
		return out;

	/* anything past the first word (besides whitespace) is args */
	while ( isspace(*end) )
		end++;

	out.has_args = (*end != '\0');
	return out;
}
