cls
@echo off
gcc "%1" -o %~n1.exe
"%~n1.exe"
del "%~n1.exe"
