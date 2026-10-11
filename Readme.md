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
goes through OS lookup. Separate commands with `;` to run several
per line (`cd ..; Test/Hello.exe`).

Files: `Shell.c`/`Shell.h` (main loop, shared decls),
`Lang/` (input parsing: `parse()`, `parse_segment()`),
`Program/` (command handling: builtins, `cd`, launch).