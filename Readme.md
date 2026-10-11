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
Builtins (no args allowed): `exit`, `clean` (visible window),
`clear` (whole buffer incl. scrollback).