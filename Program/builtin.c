#include "Shell.h"
#include "Pure.h"
#include "Std/IO.h"
#include "Std/Self.h"

void
do_exit(ParsedCommand cmd)
{
	_write( cstr(" Bye Bye ~ ") );
	exit(0);
}

void
do_clean(ParsedCommand cmd)
{
	_write( (byte_t*)cstr("\033[2J\033[H") );
}

void
do_clear(ParsedCommand cmd)
{
	_write( (byte_t*)cstr("\033[2J\033[3J\033[H") );
}
