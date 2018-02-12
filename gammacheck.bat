@echo off

rem setlocal enabledelayedexpansion - Allows using local for-loop variables
rem for %%f in (%~2\*) do - Loop all files in directory %~2 matching *
rem %%~pf%%~nf - Expanded path and filename without extension
rem fc /a first second > NUL && (set result=1) || (set result=0) - Set result to 0/1 file contents first == second
rem !var! - Local


if "%~1" == "" (
    echo Missing app argument.
    goto:eof
)
if "%~2" == "" (
    echo Missing test directory argument.
    goto:eof
)

setlocal enabledelayedexpansion
for %%f in (%~2\*.in) do (
    echo Test: %%~nf
    %1 < %%~pf%%~nf.in > temp.out   
    fc /a temp.out "%%~pf%%~nf.out" > NUL && (set result=1) || (set result=0)
    if !result! == 1 (
        echo [+] Correct
    ) else (
        echo [-] Wrong
    )
)

:finalize
del temp.out
goto:eof



