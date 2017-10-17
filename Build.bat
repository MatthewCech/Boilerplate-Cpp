@echo off
rem This is just a one-click file to run the vs2017 build script - Cleans then builds it again.
rem This will not work well with any of the files in use. It should announce that when cleaning.

echo -- [ CLEANING ] --
cd Build
call clean.bat

echo.
echo.
echo -- [ BUILDING ] --
cd Build
echo Building...
call build_vs2017.bat

echo.
echo.
echo -- [ EXITING ] --
timeout 30
