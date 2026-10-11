#include "Shell.h"
#include "Pure.h"
#include "Std/IO.h"
#include "Std/Self.h"
#include "Std/OS/Directory.h"
#include "Std/OS/Path.h"
#include "Std/OS/Process.h"
#include "Core/Char.h"
#include "Core/Memory.h"

#define SHELL_BUFFER_SIZE 4096

static char scratch[SHELL_BUFFER_SIZE];

void
do_cd(ParsedCommand cmd)
{
	/* bare `cd` prints the current directory */
	if ( cmd.arg_count == 0 )
	{
		if ( Self.CurrentDirectory )
			_writecharseq(Self.CurrentDirectory);
		_write((byte_t*)cstr("\n"));
		return;
	}

	if ( cmd.arg_count > 1 )
	{
		_write((byte_t*)cstr("cd: too many arguments\n"));
		return;
	}

	if ( cmd.arg.size >= sizeof(scratch) )
	{
		_write((byte_t*)cstr("cd: path too long\n"));
		return;
	}

	if ( memory_copy(cmd.arg.charseq, scratch, cmd.arg.size) != PURE_OK )
	{
		_write((byte_t*)cstr("cd: cannot change directory\n"));
		return;
	}
	scratch[cmd.arg.size] = '\0';

	setcurrent_directory(scratch);
	if ( Self.LastError == PURE_OK )
		return;

	if ( Self.LastError == PURE_ERROR_FILE_NOT_FOUND )
		_write((byte_t*)cstr("cd: no such directory: "));
	else if ( Self.LastError == PURE_ERROR_FILE_ACCESS_DENIED )
		_write((byte_t*)cstr("cd: access denied: "));
	else
		_write((byte_t*)cstr("cd: cannot change directory: "));

	_write((byte_t*)scratch, charseq_countbytes(scratch));
	_write((byte_t*)cstr("\n"));
}

void
do_launch(ParsedCommand cmd)
{
	char saved;
	uint64_t namelen;
	process_t* process;

	if ( cmd.text.size >= sizeof(scratch) )
	{
		_write((byte_t*)cstr("command line too long\n"));
		return;
	}

	if ( memory_copy( cmd.text.charseq, scratch, cmd.text.size ) != PURE_OK )
	{
		_write((byte_t*)cstr("cannot execute command\n"));
		return;
	}
	scratch[cmd.text.size] = '\0';

	/* isolate the program name (first word of the line) */
	namelen = 0;
	while ( scratch[namelen] != '\0' && !isspace(scratch[namelen]) )
		namelen++;

	/* absolute path: it must exist before launching */
	saved = scratch[namelen];
	scratch[namelen] = '\0';

	if ( pathname_isabsolute(scratch) && !pathname_exists(scratch) )
	{
		_write((byte_t*)scratch, charseq_countbytes(scratch));
		_write((byte_t*)cstr(": no such file\n"));
		return;
	}

	scratch[namelen] = saved;

	process = process_new(scratch);
	if ( !process )
	{
		scratch[namelen] = '\0';
		_write((byte_t*)scratch, charseq_countbytes(scratch));
		_write((byte_t*)cstr(": command not found\n"));
		return;
	}

	process_waitforcompletion(process);
	process_cleanup(process);
}

void
handle_command(ParsedCommand cmd)
{
	switch ( cmd.type )
	{
	case CMD_EMPTY:
		break;

	case CMD_EXIT:
		do_exit(cmd);
		break;

	case CMD_CLEAN:
		do_clean(cmd);
		break;

	case CMD_CLEAR:
		do_clear(cmd);
		break;

	case CMD_CD:
		do_cd(cmd);
		break;

	case CMD_UNKNOWN:
	default:
		do_launch(cmd);
		break;
	}
}
