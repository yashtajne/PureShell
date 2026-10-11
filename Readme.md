# PureShell

-I..\Pure\Interface
-L..\Pure\.LIB

-nostdlib
-ffreestanding

-lkernel32
-lPureCore
-lPureStd

Build with clang (no stdlib/libc, Pure CRT only):

	build.bat

then run `Shell.exe`. Prompt is `PS <current directory>> `.
Builtins: `exit`, `clean` (visible window), `clear` (whole buffer
incl. scrollback) take no args. `cd [dir]` changes directory
(`..`, `.`, relative and absolute paths); bare `cd` prints it.
Anything else runs as a program with its args (`process_new`,
waits for completion); children inherit env and cwd. Absolute
paths are checked with `pathname_exists` first, everything else
goes through OS lookup.

Files: `Shell.c` (main loop), `parser.c`/`parser.h` (`parse()`),
`handle.c`/`handle.h` (`cd`, launch, dispatch), `builtin.c`/
`builtin.h` (`exit`, `clean`, `clear`).