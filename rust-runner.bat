cls
@echo off
rustc "%1" -o %~n1.exe
%~n1.exe
del %~n1.exe
