#include "Pure.h"
#include "Std/IO.h"
#include "Std/Self.h"
#include "Platform/Platform.def"

#include "parser.h"

#define INPUT_BUFFER_SIZE 4096
#define CWD_BUFFER_SIZE 260

static void
write_seq(const char* seq, uint64_t size)
{
	if ( size )
		_write((byte_t*)seq, size);
}

static void
print_prompt(void)
{
	char cwd[CWD_BUFFER_SIZE];
	DWORD len = GetCurrentDirectoryA((DWORD)sizeof(cwd), cwd);

	_write((byte_t*)cstr("PS "));
	if ( len > 0 && len < (DWORD)sizeof(cwd) )
		write_seq(cwd, len);
	else
		_write((byte_t*)cstr("?"));
	_write((byte_t*)cstr("> "));
}

int
main(void)
{
	static byte_t input[INPUT_BUFFER_SIZE];

	for ( ;; )
	{
		ParsedCommand cmd;

		print_prompt();

		{
			size_t n = _readline(input, sizeof(input));
			if ( n == 0 )
				exit(0);
		}

		cmd = parse((charseq_t)input);

		switch ( cmd.type )
		{
		case CMD_EMPTY:
			break;

		case CMD_EXIT:
			if ( cmd.has_args )
				_write((byte_t*)cstr("exit: takes no arguments\n"));
			else
				exit(0);
			break;

		case CMD_CLEAN:
			if ( cmd.has_args )
				_write((byte_t*)cstr("clean: takes no arguments\n"));
			else
				_write((byte_t*)cstr("\x1b[2J\x1b[H"));
			break;

		case CMD_CLEAR:
			if (cmd.has_args)
				_write((byte_t*)cstr("clear: takes no arguments\n"));
			else
				_write((byte_t*)cstr("\x1b[3J\x1b[2J\x1b[H"));
			break;

		case CMD_UNKNOWN:
		default:
			_write((byte_t*)cstr("unknown command\n"));
			break;
		}
	}

	return 0;
}
