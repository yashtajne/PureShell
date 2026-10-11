#include "builtin.h"
#include "Pure.h"
#include "Std/IO.h"
#include "Std/Self.h"

void
do_exit(ParsedCommand cmd)
{
	if ( cmd.arg_count > 0 )
	{
		_write((byte_t*)cstr("exit: takes no arguments\n"));
		return;
	}

	exit(0);
}

void
do_clean(ParsedCommand cmd)
{
	if ( cmd.arg_count > 0 )
	{
		_write((byte_t*)cstr("clean: takes no arguments\n"));
		return;
	}

	_write((byte_t*)cstr("\x1b[2J\x1b[H"));
}

void
do_clear(ParsedCommand cmd)
{
	if ( cmd.arg_count > 0 )
	{
		_write((byte_t*)cstr("clear: takes no arguments\n"));
		return;
	}

	_write((byte_t*)cstr("\x1b[3J\x1b[2J\x1b[H"));
}
