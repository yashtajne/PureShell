#include "Pure.h"
#include "Std/IO.h"
#include "Std/Self.h"

#include "parser.h"
#include "handle.h"

#define INPUT_BUFFER_SIZE 4096

static void
print_prompt(void)
{
	_write((byte_t*)cstr("PS "));
	if ( Self.CurrentDirectory )
		_writecharseq(Self.CurrentDirectory);
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
		print_prompt();

		{
			size_t n = _readline(input, sizeof(input));
			if ( n == 0 )
				exit(0);
		}

		handle_command(parse((charseq_t)input));
	}

	return 0;
}
