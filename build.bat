@echo off
REM Build PureShell with clang + Pure CRT (no stdlib/libc).
setlocal
set PD=..\Pure
set KL=C:\Program Files (x86)\Windows Kits\10\Lib\10.0.26100.0\um\x64\kernel32.Lib
clang -O0 -std=c99 -fno-builtin-memcpy -fno-builtin-memset -ffreestanding -fno-stack-protector -nostdlib -nodefaultlibs -nostartfiles Shell.c Lang\parser.c Program\handle.c Program\builtin.c -I. -I%PD% -I%PD%\Interface -Wl,/entry:_start -Wl,/subsystem:console -o Shell.exe %PD%\.LIB\PureStd.lib %PD%\.LIB\PureCore.lib "%KL%"
