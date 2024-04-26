cls
@echo off
csc "%1"
"%~n1.exe"
del "%~n1.exe"
